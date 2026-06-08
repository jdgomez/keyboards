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
    TD_A,   // @  / #
    TD_J,   // SPC / ENT
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
                                            KC_LGUI, MO(_NAV), KC_SPC,  TD(TD_J), MO(_SYM), KC_RALT
    ),

    [_NAV] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_C,    KC_V,    KC_UP,   XXXXXXX, XXXXXXX, KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,  KC_LCTL, KC_LSFT, KC_LALT, KC_ALGR, XXXXXXX,                      KC_X,  KC_LEFT, KC_DOWN,  KC_RGHT, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_BRMD, KC_BRMU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_Z,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, _______, KC_SPC,   TD(TD_J), MO(_MEDIA), KC_RALT
    ),

    [_SYM] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,  KC_EXLM, TD(TD_A), KC_LPRN, KC_RPRN, XXXXXXX,                    KC_LABK, KC_RABK, KC_ASTR, KC_HASH, KC_EQL,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL, XXXXXXX, KC_QUES,  KC_LCBR, KC_RCBR, XXXXXXX,                    KC_DLR,  KC_AMPR, KC_PIPE, KC_SLSH, KC_BSLS, KC_GRV,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT, XXXXXXX, XXXXXXX,  KC_LBRC, KC_RBRC, XXXXXXX,                    KC_CIRC, KC_PLUS, KC_PMNS, XXXXXXX, XXXXXXX, KC_TILD,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, MO(_MEDIA), KC_SPC, TD(TD_J), _______, KC_RALT
    ),

    [_MEDIA] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                     KC_PPLS, KC_7,    KC_8,    KC_9,    KC_PMNS, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,                     KC_PAST, KC_4,    KC_5,    KC_6,    KC_PSLS, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_0,    KC_1,    KC_2,    KC_3,    KC_COMM, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, _______, KC_SPC,   TD(TD_J), _______, KC_RALT
    ),
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_S] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN)),  // ; / :
    [TD_Q] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT)),  // ' / "
    [TD_M] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, LSFT(KC_MINS)),  // - / _
    [TD_A] = ACTION_TAP_DANCE_DOUBLE(KC_AT,   KC_HASH),         // @ / #
    [TD_J] = ACTION_TAP_DANCE_DOUBLE(KC_SPC,  KC_ENT),          // SPC / ENT
};
