// Copyright 2024 Tomasz Janas (@tjanas94)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _LEFT_TAP,
    _RIGHT_TAP,
    _NAV,
    _NUM,
    _PAR,
    _SYM,
    _FUNC,
    _ONE_SHOT_HACK
};

#define KC_GUIA LT(_RIGHT_TAP, KC_A)
#define KC_ALTR LT(_RIGHT_TAP, KC_R)
#define KC_CTLS LT(_RIGHT_TAP, KC_S)
#define KC_SHFT LT(_RIGHT_TAP, KC_T)
#define KC_HYPG LT(_RIGHT_TAP, KC_G)
#define KC_HYPM LT(_LEFT_TAP, KC_M)
#define KC_SFTN LT(_LEFT_TAP, KC_N)
#define KC_CTLE LT(_LEFT_TAP, KC_E)
#define KC_ALTI LT(_LEFT_TAP, KC_I)
#define KC_GUIO LT(_LEFT_TAP, KC_O)
#define KC_ALTX LT(_RIGHT_TAP, KC_X)
#define KC_ALTD LT(_LEFT_TAP, KC_DOT)

#define KC_LSPC LT(_NAV, KC_SPC)
#define KC_LBSP LT(_NUM, KC_BSPC)
#define KC_OSFT LT(_ONE_SHOT_HACK, 0)
#define KC_LENT LT(_SYM, KC_ENT)
#define KC_FUNC MO(_FUNC)

#define KC_BACK LALT(KC_LEFT)
#define KC_FRWD LALT(KC_RGHT)
#define KC_UNDO LCTL(KC_Z)
#define KC_CUT  LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_SEL LCTL(KC_A)
#define KC_PAST LCTL(KC_V)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_ALTX:
        case KC_ALTD:
            return 150;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_GUIA:
        case KC_ALTR:
        case KC_CTLS:
        case KC_SHFT:
        case KC_HYPG:
        case KC_HYPM:
        case KC_SFTN:
        case KC_CTLE:
        case KC_ALTI:
        case KC_GUIO:
        case KC_LSPC:
            return false;
        default:
            return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool is_double_tap = false;
    static uint16_t double_tap_timer = 0;

    if (is_double_tap && timer_elapsed(double_tap_timer) > TAPPING_TERM) {
        is_double_tap = false;
    }

    switch (keycode) {
        case KC_GUIA:
            if (record->tap.count == 0) {
                if (record->event.pressed) {
                    register_mods(MOD_BIT(KC_LGUI));
                } else {
                    unregister_mods(MOD_BIT(KC_LGUI));
                }
            }

            return true;

        case KC_ALTR:
        case KC_ALTI:
            if (record->tap.count == 0) {
                if (record->event.pressed) {
                    register_mods(MOD_BIT(KC_LALT));
                } else {
                    unregister_mods(MOD_BIT(KC_LALT));
                }
            }

            return true;

        case KC_CTLS:
            if (record->tap.count == 0) {
                if (record->event.pressed) {
                    register_mods(MOD_BIT(KC_LCTL));
                } else {
                    unregister_mods(MOD_BIT(KC_LCTL));
                }
            }

            return true;

        case KC_SHFT:
            if (record->tap.count == 0) {
                if (record->event.pressed) {
                    register_mods(MOD_BIT(KC_LSFT));
                } else {
                    unregister_mods(MOD_BIT(KC_LSFT));
                }
            }

            return true;

        case KC_HYPG:
        case KC_HYPM:
            if (record->tap.count == 0) {
                if (record->event.pressed) {
                    register_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
                } else {
                    unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
                }
            }

            return true;

        case KC_SFTN:
            if (record->tap.count == 0) {
                if (record->event.pressed) {
                    register_mods(MOD_BIT(KC_RSFT));
                } else {
                    unregister_mods(MOD_BIT(KC_RSFT));
                }
            }

            return true;

        case KC_CTLE:
            if (record->tap.count == 0) {
                if (record->event.pressed) {
                    register_mods(MOD_BIT(KC_RCTL));
                } else {
                    unregister_mods(MOD_BIT(KC_RCTL));
                }
            }

            return true;

        case KC_GUIO:
            if (record->tap.count == 0) {
                if (record->event.pressed) {
                    register_mods(MOD_BIT(KC_RGUI));
                } else {
                    unregister_mods(MOD_BIT(KC_RGUI));
                }
            }

            return true;

        case KC_ALTX:
        case KC_ALTD:
            if (record->tap.count == 0) {
                if (record->event.pressed) {
                    register_mods(MOD_BIT(KC_RALT));
                } else {
                    unregister_mods(MOD_BIT(KC_RALT));
                }
            }

            return true;

        case KC_OSFT:
            if (record->event.pressed) {
                if (record->tap.count > 0) {
                    if (is_double_tap) {
                        is_double_tap = false;
                        clear_oneshot_mods();
                        caps_word_toggle();
                    } else {
                        is_double_tap = true;
                        double_tap_timer = timer_read();
                        set_oneshot_mods(MOD_BIT(KC_LSFT));
                    }
                } else {
                    clear_oneshot_mods();
                    layer_on(_PAR);
                }
            } else {
                if (record->tap.count > 0) {
                    // do nothing for tap release
                } else {
                    layer_off(_PAR);
                }
            }

            return false;
    }

    return true;
}

enum combos {
    ESC_COMBO,
    TAB_COMBO,
    EQL_COMBO,
    TAP_EQL_COMBO,
    MINS_COMBO,
    TAP_MINS_COMBO,
    LPRN_COMBO,
    RPRN_COMBO,
    LBRC_COMBO,
    RBRC_COMBO
};

const uint16_t PROGMEM esc_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM eql_combo[] = {KC_ALTX, KC_C, COMBO_END};
const uint16_t PROGMEM tap_eql_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM mins_combo[] = {KC_COMM, KC_ALTD, COMBO_END};
const uint16_t PROGMEM tap_mins_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM lprn_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM rprn_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM lbrc_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM rbrc_combo[] = {KC_U, KC_Y, COMBO_END};

combo_t key_combos[] = {
    [ESC_COMBO] = COMBO(esc_combo, KC_ESC),
    [TAB_COMBO] = COMBO(tab_combo, KC_TAB),
    [EQL_COMBO] = COMBO(eql_combo, KC_EQL),
    [TAP_EQL_COMBO] = COMBO(tap_eql_combo, KC_EQL),
    [MINS_COMBO] = COMBO(mins_combo, KC_MINS),
    [TAP_MINS_COMBO] = COMBO(tap_mins_combo, KC_MINS),
    [LPRN_COMBO] = COMBO(lprn_combo, KC_LPRN),
    [RPRN_COMBO] = COMBO(rprn_combo, KC_RPRN),
    [LBRC_COMBO] = COMBO(lbrc_combo, KC_LBRC),
    [RBRC_COMBO] = COMBO(rbrc_combo, KC_RBRC)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_2(
        KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,       KC_J,       KC_L,       KC_U,       KC_Y,       KC_QUOT,
        KC_GUIA,    KC_ALTR,    KC_CTLS,    KC_SHFT,    KC_HYPG,    KC_HYPM,    KC_SFTN,    KC_CTLE,    KC_ALTI,    KC_GUIO,
        KC_Z,       KC_ALTX,    KC_C,       KC_D,       KC_V,       KC_K,       KC_H,       KC_COMM,    KC_ALTD,    KC_SLSH,
                                            KC_OSFT,    KC_LSPC,    KC_LBSP,    KC_LENT
    ),

    [_LEFT_TAP] = LAYOUT_split_3x5_2(
        KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_A,       KC_R,       KC_S,       KC_T,       KC_G,       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                            KC_TRNS,    KC_SPC,     KC_TRNS,    KC_TRNS
    ),

    [_RIGHT_TAP] = LAYOUT_split_3x5_2(
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_J,       KC_L,       KC_U,       KC_Y,       KC_QUOT,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_M,       KC_N,       KC_E,       KC_I,       KC_O,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH,
                                            KC_TRNS,    KC_TRNS,    KC_BSPC,    KC_TRNS
    ),

    [_NAV] = LAYOUT_split_3x5_2(
        KC_NO,      KC_BACK,    KC_FRWD,    KC_NO,      KC_NO,      KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     KC_CAPS,
        KC_LGUI,    KC_LALT,    KC_LCTL,    KC_LSFT,    KC_NO,      KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_INS,
        KC_UNDO,    KC_CUT,     KC_COPY,    KC_SEL,     KC_PAST,    KC_H,       KC_J,       KC_K,       KC_L,       KC_APP,
                                            KC_NO,      KC_NO,      KC_BSPC,    KC_DEL
    ),

    [_NUM] = LAYOUT_split_3x5_2(
        KC_UNDS,    KC_9,       KC_8,       KC_7,       KC_EQL,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_MINS,    KC_6,       KC_5,       KC_4,       KC_ASTR,    KC_NO,      KC_LSFT,    KC_LCTL,    KC_LALT,    KC_LGUI,
        KC_PLUS,    KC_3,       KC_2,       KC_1,       KC_SLSH,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                            KC_DOT,     KC_0,       KC_NO,      KC_NO
    ),

    [_PAR] = LAYOUT_split_3x5_2(
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_COMM,    KC_COLN,    KC_SCLN,    KC_DQUO,
        KC_LGUI,    KC_LALT,    KC_LCTL,    KC_LSFT,    KC_NO,      KC_NO,      KC_LPRN,    KC_LCBR,    KC_RCBR,    KC_RPRN,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_LT,      KC_LBRC,    KC_RBRC,    KC_GT,
                                            KC_NO,      KC_NO,      KC_NO,      KC_FUNC
    ),

    [_SYM] = LAYOUT_split_3x5_2(
        KC_UNDS,    KC_BSLS,    KC_PIPE,    KC_AMPR,    KC_EQL,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_TILD,    KC_CIRC,    KC_PERC,    KC_DLR,     KC_ASTR,    KC_NO,      KC_LSFT,    KC_LCTL,    KC_LALT,    KC_LGUI,
        KC_GRV,     KC_HASH,    KC_AT,      KC_EXLM,    KC_SLSH,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                            KC_FUNC,    KC_NO,      KC_NO,      KC_NO
    ),

    [_FUNC] = LAYOUT_split_3x5_2(
        KC_F12,     KC_F9,      KC_F8,      KC_F7,      KC_SCRL,    KC_NO,      KC_MSTP,    KC_MPLY,    KC_MUTE,    KC_NO,
        KC_F11,     KC_F6,      KC_F5,      KC_F4,      KC_PSCR,    KC_BRIU,    KC_LSFT,    KC_LCTL,    KC_LALT,    KC_LGUI,
        KC_F10,     KC_F3,      KC_F2,      KC_F1,      KC_PAUS,    KC_BRID,    KC_MPRV,    KC_VOLD,    KC_VOLU,    KC_MNXT,
                                            KC_NO,      KC_NO,      KC_NO,      KC_NO
    )
};
