// Copyright 2022 Matthew Dews (@matthew-dews)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layer {
    _QWERTY,
    _LOWER,
    _RAISE,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4  , KC_5   , KC_UP,       KC_6   , KC_7  , KC_8   , KC_9   , KC_0   , KC_LBRC, KC_RBRC,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R  , KC_T   , KC_DOWN,     KC_Y   , KC_U  , KC_I   , KC_O   , KC_P   , KC_QUOT, KC_BSLS,
        KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F  , KC_G   , KC_UP,       KC_H   , KC_J  , KC_K   , KC_L   , KC_SCLN, KC_LSFT, _______,
        KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V  , KC_B   , KC_DOWN,     KC_N   , KC_M  , KC_COMM, KC_DOT , KC_SLSH, KC_LCTL, _______,
                          KC_LBRC, KC_RBRC, KC_DEL, KC_SPC , KC_TAB,      KC_PLUS, KC_EQL, KC_ENT , _______, _______,
                                                    KC_HOME, KC_BSPC,     KC_END , KC_DEL
    )
    // [_LOWER] = LAYOUT(
    //     KC_GRV  , KC_1   , KC_2   , KC_3   , KC_4  , KC_5   , KC_UP,                       KC_6   , KC_7  , KC_8   , KC_9   , KC_0   , KC_LBRC, KC_RBRC,
    //     KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R  , KC_T   , KC_DOWN,                     KC_Y   , KC_U  , KC_I   , KC_O   , KC_P   , KC_QUOT, KC_BSLS,
    //     KC_LSFT , KC_A   , KC_S   , KC_D   , KC_F  , KC_G   , KC_UP,                       KC_H   , KC_J  , KC_K   , KC_L   , KC_SCLN, KC_LSFT, _______,
    //     KC_LCTL , KC_Z   , KC_X   , KC_C   , KC_V  , KC_B   , KC_DOWN,                     KC_N   , KC_M  , KC_COMM, KC_DOT , KC_SLSH, KC_LCTL, _______,
    //     _______, _______, KC_LBRC, KC_RBRC, KC_DEL , KC_SPC , KC_TAB,                      KC_PLUS, KC_EQL, KC_ENT , _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, KC_HOME, KC_BSPC                      KC_END , KC_DEL, _______, _______, _______, _______, _______,
    // )
    // [_RAISE] = LAYOUT(
    //     KC_GRV  , KC_1   , KC_2   , KC_3   , KC_4  , KC_5   , KC_UP,                       KC_6   , KC_7  , KC_8   , KC_9   , KC_0   , KC_LBRC, KC_RBRC,
    //     KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R  , KC_T   , KC_DOWN,                     KC_Y   , KC_U  , KC_I   , KC_O   , KC_P   , KC_QUOT, KC_BSLS,
    //     KC_LSFT , KC_A   , KC_S   , KC_D   , KC_F  , KC_G   , KC_UP,                       KC_H   , KC_J  , KC_K   , KC_L   , KC_SCLN, KC_LSFT, _______,
    //     KC_LCTL , KC_Z   , KC_X   , KC_C   , KC_V  , KC_B   , KC_DOWN,                     KC_N   , KC_M  , KC_COMM, KC_DOT , KC_SLSH, KC_LCTL, _______,
    //     _______, _______, KC_LBRC, KC_RBRC, KC_DEL , KC_SPC , KC_TAB,                      KC_PLUS, KC_EQL, KC_ENT , _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, KC_HOME, KC_BSPC                      KC_END , KC_DEL, _______, _______, _______, _______, _______,
    // )
};
