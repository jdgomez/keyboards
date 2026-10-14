/*
 *
 * Copyright (c) 2023 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 *
 * Basado en app/boards/shields/nice_view/widgets/peripheral_status.c de ZMK v0.3.0.
 * Cambio: en lugar de la imagen fija (globo/montaña) muestra a Magikarp chapoteando,
 * que evoluciona a Gyarados tras CONFIG_NICE_VIEW_MAGIKARP_EVOLVE_PRESSES pulsaciones
 * en esta mitad. El contador vive en RAM: se reinicia al dormir o reiniciar.
 *
 */

#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/activity.h>
#include <zmk/battery.h>
#include <zmk/display.h>
#include <zmk/events/activity_state_changed.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/split/bluetooth/peripheral.h>
#include <zmk/events/split_peripheral_status_changed.h>
#include <zmk/usb.h>
#include <zmk/ble.h>

#include "peripheral_status.h"

LV_IMG_DECLARE(magikarp_0);
LV_IMG_DECLARE(magikarp_1);
LV_IMG_DECLARE(gyarados);

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct peripheral_status_state {
    bool connected;
};

static void draw_top(lv_obj_t *widget, lv_color_t cbuf[], const struct status_state *state) {
    lv_obj_t *canvas = lv_obj_get_child(widget, 0);

    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &lv_font_montserrat_16, LV_TEXT_ALIGN_RIGHT);
    lv_draw_rect_dsc_t rect_black_dsc;
    init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);

    // Fill background
    lv_canvas_draw_rect(canvas, 0, 0, CANVAS_SIZE, CANVAS_SIZE, &rect_black_dsc);

    // Draw battery
    draw_battery(canvas, state);

    // Draw output status
    lv_canvas_draw_text(canvas, 0, 0, CANVAS_SIZE, &label_dsc,
                        state->connected ? LV_SYMBOL_WIFI : LV_SYMBOL_CLOSE);

    // Rotate canvas
    rotate_canvas(canvas, cbuf);
}

static void set_battery_status(struct zmk_widget_status *widget,
                               struct battery_status_state state) {
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    widget->state.charging = state.usb_present;
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */

    widget->state.battery = state.level;

    draw_top(widget->obj, widget->cbuf, &widget->state);
}

static void battery_status_update_cb(struct battery_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_battery_status(widget, state); }
}

static struct battery_status_state battery_status_get_state(const zmk_event_t *eh) {
    return (struct battery_status_state){
        .level = zmk_battery_state_of_charge(),
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
        .usb_present = zmk_usb_is_powered(),
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_battery_status, struct battery_status_state,
                            battery_status_update_cb, battery_status_get_state)

ZMK_SUBSCRIPTION(widget_battery_status, zmk_battery_state_changed);
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(widget_battery_status, zmk_usb_conn_state_changed);
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */

static struct peripheral_status_state get_state(const zmk_event_t *_eh) {
    return (struct peripheral_status_state){.connected = zmk_split_bt_peripheral_is_connected()};
}

static void set_connection_status(struct zmk_widget_status *widget,
                                  struct peripheral_status_state state) {
    widget->state.connected = state.connected;

    draw_top(widget->obj, widget->cbuf, &widget->state);
}

static void output_status_update_cb(struct peripheral_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_connection_status(widget, state); }
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_peripheral_status, struct peripheral_status_state,
                            output_status_update_cb, get_state)
ZMK_SUBSCRIPTION(widget_peripheral_status, zmk_split_peripheral_status_changed);

// ── Magikarp ─────────────────────────────────────────────────────────────────

struct art_state {
    bool evolved;
    bool active;
};

// Solo se modifica en art_get_state, que el event manager llama de uno en uno.
static uint32_t art_presses;

// Solo se usan desde la cola de trabajo de la pantalla (hilo de LVGL).
static lv_obj_t *art_img;
static lv_timer_t *art_timer;
static bool art_evolved;
static bool art_frame;

static void art_timer_cb(lv_timer_t *timer) {
    art_frame = !art_frame;
    lv_img_set_src(art_img, art_frame ? &magikarp_1 : &magikarp_0);
}

static void art_update_cb(struct art_state state) {
    if (art_evolved) {
        return;
    }

    if (state.evolved) {
        art_evolved = true;
        lv_timer_del(art_timer);
        art_timer = NULL;
        lv_img_set_src(art_img, &gyarados);
        return;
    }

    // Animar solo mientras hay actividad, para no despertar la CPU en reposo.
    if (state.active) {
        lv_timer_resume(art_timer);
    } else {
        lv_timer_pause(art_timer);
        art_frame = false;
        lv_img_set_src(art_img, &magikarp_0);
    }
}

static struct art_state art_get_state(const zmk_event_t *eh) {
    const struct zmk_position_state_changed *ev =
        eh != NULL ? as_zmk_position_state_changed(eh) : NULL;

    if (ev != NULL && ev->state && art_presses < CONFIG_NICE_VIEW_MAGIKARP_EVOLVE_PRESSES) {
        art_presses++;
    }

    return (struct art_state){
        .evolved = art_presses >= CONFIG_NICE_VIEW_MAGIKARP_EVOLVE_PRESSES,
        .active = zmk_activity_get_state() == ZMK_ACTIVITY_ACTIVE,
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_art, struct art_state, art_update_cb, art_get_state)
ZMK_SUBSCRIPTION(widget_art, zmk_position_state_changed);
ZMK_SUBSCRIPTION(widget_art, zmk_activity_state_changed);

int zmk_widget_status_init(struct zmk_widget_status *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 160, 68);
    lv_obj_t *top = lv_canvas_create(widget->obj);
    lv_obj_align(top, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_canvas_set_buffer(top, widget->cbuf, CANVAS_SIZE, CANVAS_SIZE, LV_IMG_CF_TRUE_COLOR);

    art_img = lv_img_create(widget->obj);
    lv_img_set_src(art_img, &magikarp_0);
    lv_obj_align(art_img, LV_ALIGN_TOP_LEFT, 0, 0);
    art_timer = lv_timer_create(art_timer_cb, CONFIG_NICE_VIEW_MAGIKARP_FRAME_MS, NULL);

    sys_slist_append(&widgets, &widget->node);
    widget_battery_status_init();
    widget_peripheral_status_init();
    widget_art_init();

    return 0;
}

lv_obj_t *zmk_widget_status_obj(struct zmk_widget_status *widget) { return widget->obj; }
