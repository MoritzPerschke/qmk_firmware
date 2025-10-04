#include <stdint.h>
#include "config.h"
#include QMK_KEYBOARD_H

#if __has_include("keymap.h")
#    include "keymap.h"
#endif


enum custom_layer {
    BASE,
    MOUSE,
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        KC_GRV,  KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,     KC_O,   KC_P,         KC_BSLS,
        KC_LSFT, KC_A,    KC_S,   KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,     KC_L,   KC_SEMICOLON, KC_RSFT,
        KC_LCTL, KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMMA, KC_DOT, KC_SLASH,     KC_RCTL,
                 KC_DEL,  KC_ENT, KC_TAB, KC_LCTL, KC_LALT,    KC_BSPC, KC_SPC,  KC_QUOT
    ),
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

// https://docs.qmk.fm/features/pointing_device#advanced-drag-scroll
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if SCROLL layer is active
    if (IS_LAYER_ON(MOUSE)) {
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR;
        scroll_accumulated_v -= (float)mouse_report.y / SCROLL_DIVISOR;

        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report; // Pass the modified report to QMK for further processing
}
