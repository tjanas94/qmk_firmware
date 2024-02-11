// Copyright 2024 Tomasz Janas (@tjanas94)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _NUM,
    _PAR,
    _SYM,
    _FUNC
};

#define KC_GUIA LGUI_T(KC_A)
#define KC_ALTR LALT_T(KC_R)
#define KC_SHFS LSFT_T(KC_S)
#define KC_CTRT LCTL_T(KC_T)
#define KC_CTRN RCTL_T(KC_N)
#define KC_SHFE RSFT_T(KC_E)
#define KC_ALTI LALT_T(KC_I)
#define KC_GUIO RGUI_T(KC_O)
#define KC_ALTX RALT_T(KC_X)
#define KC_ALTD RALT_T(KC_DOT)

#define KC_1SPC LT(1,KC_SPC)
#define KC_2ESC LT(2,KC_ESC)
#define KC_3TAB LT(3,KC_TAB)
#define KC_4ENT LT(4,KC_ENT)
#define KC_5MO MO(5)

#define KC_BACK LALT(KC_LEFT)
#define KC_FRWD LALT(KC_RGHT)
#define KC_UNDO LCTL(KC_Z)
#define KC_CUT  LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_SEL LCTL(KC_A)
#define KC_PAST LCTL(KC_V)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_GUIA:
        case KC_ALTR:
        case KC_SHFS:
        case KC_CTRT:
        case KC_CTRN:
        case KC_SHFE:
        case KC_ALTI:
        case KC_GUIO:
            return 200;
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_2(
        KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_QUOT,
        KC_GUIA,    KC_ALTR,    KC_SHFS,    KC_CTRT,    KC_G,       KC_M,       KC_CTRN,    KC_SHFE,    KC_ALTI,    KC_GUIO,
        KC_Z,       KC_ALTX,    KC_C,       KC_D,       KC_V,       KC_K,       KC_H,       KC_COMM,    KC_ALTD,    KC_SLSH,
                                            KC_3TAB,    KC_1SPC,    KC_2ESC,    KC_4ENT
    ),

    [_NAV] = LAYOUT_split_3x5_2(
        KC_NO,      KC_BACK,    KC_FRWD,    KC_NO,      KC_NO,      KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     KC_CAPS,
        KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    CW_TOGG,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_INS,
        KC_UNDO,    KC_CUT,     KC_COPY,    KC_SEL,     KC_PAST,    KC_H,       KC_J,       KC_K,       KC_L,       KC_APP,
                                            KC_NO,      KC_NO,      KC_BSPC,    KC_DEL
    ),

    [_NUM] = LAYOUT_split_3x5_2(
        KC_UNDS,    KC_9,       KC_8,       KC_7,       KC_EQL,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_MINS,    KC_6,       KC_5,       KC_4,       KC_ASTR,    KC_NO,      KC_LCTL,    KC_LSFT,    KC_LALT,    KC_LGUI,
        KC_PLUS,    KC_3,       KC_2,       KC_1,       KC_SLSH,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                            KC_DOT,     KC_0,       KC_NO,      KC_NO
    ),

    [_PAR] = LAYOUT_split_3x5_2(
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_COMM,    KC_COLN,    KC_SCLN,    KC_DQUO,
        KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    KC_NO,      KC_NO,      KC_LPRN,    KC_LCBR,    KC_LBRC,    KC_LT,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_RPRN,    KC_RCBR,    KC_RBRC,    KC_GT,
                                            KC_NO,      KC_NO,      KC_NO,      KC_5MO
    ),

    [_SYM] = LAYOUT_split_3x5_2(
        KC_UNDS,    KC_BSLS,    KC_PIPE,    KC_AMPR,    KC_EQL,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_TILD,    KC_CIRC,    KC_PERC,    KC_DLR,     KC_ASTR,    KC_NO,      KC_LCTL,    KC_LSFT,    KC_LALT,    KC_LGUI,
        KC_GRV,     KC_HASH,    KC_AT,      KC_EXLM,    KC_SLSH,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                            KC_5MO,     KC_NO,      KC_NO,      KC_NO
    ),

    [_FUNC] = LAYOUT_split_3x5_2(
        KC_F12,     KC_F9,      KC_F8,      KC_F7,      KC_SCRL,    KC_NO,      KC_MSTP,    KC_MPLY,    KC_MUTE,    KC_NO,
        KC_F11,     KC_F6,      KC_F5,      KC_F4,      KC_PSCR,    KC_BRIU,    KC_LCTL,    KC_LSFT,    KC_LALT,    KC_LGUI,
        KC_F10,     KC_F3,      KC_F2,      KC_F1,      KC_PAUS,    KC_BRID,    KC_MPRV,    KC_VOLD,    KC_VOLU,    KC_MNXT,
                                            KC_NO,      KC_NO,      KC_NO,      KC_NO
    )
};
