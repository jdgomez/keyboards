#include QMK_KEYBOARD_H
#include "keymap_us_international.h"

enum layers {
    _BASE,
    _NAV,
    _SYM,
    _MEDIA,
};

enum {
    TD_S,   // ;  / :
    TD_Q,   // '  / "
    TD_M,   // -  / _
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       LT(_MEDIA,KC_TAB), TD(TD_S), KC_COMM, KC_DOT,  KC_P,    KC_Y,                KC_F,    KC_G,    KC_C,    KC_R,    KC_L,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       LCTL_T(KC_ESC),    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                KC_D,    KC_H,    KC_T,    KC_N,    KC_S,  TD(TD_M),
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT,        TD(TD_Q),   KC_Q,    KC_J,    KC_K,    KC_X,                KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,  RSFT_T(KC_SLSH),
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, MO(_NAV), KC_SPC,  KC_ENT,   MO(_SYM), KC_RALT
    ),

    [_NAV] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,  XXXXXXX, KC_P7,   KC_P8,   KC_P9,   XXXXXXX,                    XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL, XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PDOT,                    XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PCMM,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, _______, KC_SPC,   KC_ENT,  MO(_MEDIA), KC_RALT
    ),

    [_SYM] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,  S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                    S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL, XXXXXXX, S(KC_SLSH), S(KC_9), S(KC_0), XXXXXXX,                KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX,                   S(KC_MINS), S(KC_EQL), S(KC_LBRC), S(KC_RBRC), S(KC_BSLS), S(KC_GRV),
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, MO(_MEDIA), KC_SPC, KC_ENT, _______, KC_RALT
    ),

    [_MEDIA] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                     KC_PPLS, KC_7,    KC_8,    KC_9,    KC_PMNS, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, LCTL(LSFT(LGUI(KC_4))), LSFT(LGUI(KC_4)), KC_VOLD, KC_PAST, KC_4,    KC_5,    KC_6,    KC_PSLS, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_0,    KC_1,    KC_2,    KC_3,    KC_COMM, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, _______, KC_SPC,   KC_ENT,   _______, KC_RALT
    ),
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_S] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN)),  // ; / :
    [TD_Q] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT)),  // ' / "
    [TD_M] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, LSFT(KC_MINS)),  // - / _

};

// ── RGB ──────────────────────────────────────────────────────────────────────
// Fuerza color fijo en cada arranque, sin tocar EEPROM: evita que las dos
// mitades diverjan si la sincronización RGBLIGHT_SPLIT falla o si alguna
// mitad tiene guardado un estado distinto (bug de LED izquierdo en blanco,
// 2026-09-20).
void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_RED);
}
