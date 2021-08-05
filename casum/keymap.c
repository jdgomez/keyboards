

#include QMK_KEYBOARD_H
#include "keymap_us_international.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Custom keycodes for layer keys
// Dual function escape with left command


enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MACRO1,
};

enum {
    TD_SCLN,
    TD_QUOT,
    TD_CAPLOCK,
    TD_MINS,
    TD_EXCL,
    TD_QUEST,
    TD_ANGL,
    TD_COMM,
    TD_PAR,
    TD_AMB,
    TD_BRACK,
    TD_KEYS,
    TD_SLASHES,
    TD_ARB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
    KC_TAB,TD(TD_QUOT),TD(TD_COMM),TD(TD_ARB),KC_P,KC_Y,                          KC_F,    KC_G,    KC_C,    KC_R,    KC_L,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
TD(TD_CAPLOCK), KC_A,   KC_O,    KC_E,    KC_U,    KC_I,                          KC_D,    KC_H,    KC_T,    KC_N,   KC_S,   TD(TD_QUEST),
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LCTL_T(KC_LGUI),TD(TD_SCLN),KC_Q,   KC_J,    KC_K,    KC_X,                       KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,   TD(TD_EXCL),
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LALT, LOWER, KC_SPC,        ALGR_T(KC_ENT), RAISE, KC_ESC
                                      //|--------------------------|  |--------------------------|
  ),

  [_LOWER] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  XXXXXXX,XXXXXXX, KC_UP, XXXXXXX,  XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT, XXXXXXX, KC_LEFT,KC_DOWN , KC_RGHT, XXXXXXX,                       XXXXXXX ,XXXXXXX, KC_CIRC, KC_TILD, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),LCTL(KC_Y),XXXXXXX,              XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LALT, KC_TRNS, KC_SPC,     ALGR_T(KC_ENT), RAISE, KC_ESC
                                      //|--------------------------|  |--------------------------|
  ),

  [_RAISE] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_DLR,    KC_7,    KC_8,    KC_9,  KC_ASTR, KC_PSLS,                       XXXXXXX,TD(TD_MINS), TD(TD_ANGL),  KC_EQUAL, XXXXXXX, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    LCTL(RALT(KC_5)),KC_4,KC_5, KC_6,    KC_PLUS, KC_MINS,                      TD(TD_SLASHES),TD(TD_AMB), TD(TD_PAR),  TD(TD_KEYS), TD(TD_BRACK), KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_0,     KC_1,     KC_2,    KC_3,  KC_EQUAL, KC_PERC,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_DOT, LOWER, KC_SPC,       ALGR_T(KC_ENT), KC_TRNS, KC_ESC
                                      //|--------------------------|  |--------------------------|
  ),

  [_ADJUST] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,                     XXXXXXX, XXXXXXX,   LCTL(LALT(KC_DEL)),   XXXXXXX,   XXXXXXX,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_F6,    KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,                       MACRO1, XXXXXXX,XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_F11,  KC_F12, XXXXXXX, XXXXXXX, KC_PWR, KC_SLEP,                       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LALT, KC_TRNS, KC_SPC,     ALGR_T(KC_ENT), KC_TRNS, KC_ESC 
                                      //|--------------------------|  |--------------------------|
  )
};


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for ;, twice for :
    [TD_SCLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN)),
    [TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT)),
    [TD_CAPLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_MINS] = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, LSFT(KC_MINUS)),
    [TD_SLASHES] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_BSLASH),
    [TD_QUEST] = ACTION_TAP_DANCE_DOUBLE(KC_QUES, RALT(KC_SLSH)),
    //[TD_EXCL] = ACTION_TAP_DANCE_DOUBLE(KC_EXLM, LSFT(KC_GRV)),
    [TD_EXCL] = ACTION_TAP_DANCE_DOUBLE(KC_EXLM, RALT(KC_1)),
    [TD_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_DOT),
    [TD_PAR] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TD_ANGL] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_COMM), LSFT(KC_DOT)),
    [TD_AMB] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_7), LSFT(KC_BSLS)),
    [TD_BRACK] = ACTION_TAP_DANCE_DOUBLE(KC_LBRACKET, KC_RBRACKET),
    [TD_KEYS] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE),
    [TD_ARB] = ACTION_TAP_DANCE_DOUBLE(KC_AT, KC_HASH),

};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

void rgb_matrix_indicators_user(void) {
  #ifdef RGB_MATRIX_ENABLE
  switch (biton32(layer_state)) {
    case _RAISE:
        for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
            rgb_matrix_set_color(i, 255, 0, 0);
        }
        break;

    case _LOWER:
        for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
            rgb_matrix_set_color(i, 0, 0, 255);
        }
        break;

    default:
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
                rgb_matrix_set_color(i, 0, 255, 0);
            }
        }
        break;
  }
  #endif
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
   // render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
   // render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
   // render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
   // render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 1500000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
    // set_timelog();
  }

  switch (keycode) {
    case LOWER:
        if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_LOWER);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        }
        return false;
    case RAISE:
        if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_RAISE);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        }
        return false;
    case ADJUST:
        if (record->event.pressed) {
            layer_on(_ADJUST);
        } else {
            layer_off(_ADJUST);
        }
        return false;
    case MACRO1:
        if (record->event.pressed) {
            SEND_STRING("guillefrc@gmail.com");
        } else {
            
        }
        return false;
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
            eeconfig_update_rgb_matrix_default();
            rgb_matrix_enable();
        }
      #endif
        break;
  }
  return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif

