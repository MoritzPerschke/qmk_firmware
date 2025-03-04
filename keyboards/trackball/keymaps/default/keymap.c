#include <stdint.h>
#include "config.h"
#include QMK_KEYBOARD_H

#if __has_include("keymap.h")
#    include "keymap.h"
#endif


enum custom_layer {
    MOUSE,
    ALT,
    MOUSE_ALT
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [MOUSE] = LAYOUT(
        KC_BTN1, LT(ALT, KC_BTN2), KC_BTN3, KC_BTN4, TG(ALT)
    ),
    [ALT] = LAYOUT(
        KC_BTN1, LT(MOUSE_ALT, KC_BTN2), KC_BTN4, KC_BTN5, TG(ALT)
    ),
    [MOUSE_ALT] = LAYOUT(
        KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, TG(ALT)
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
    if (IS_LAYER_ON(ALT)) {
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
