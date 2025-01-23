#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif


enum custom_layer {
    MOUSE,
    ALT
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [MOUSE] = LAYOUT(
        KC_BTN1, LT(ALT, KC_BTN2), KC_BTN3, KC_WH_U, KC_WH_D
    ),
    [ALT] = LAYOUT(
        KC_BTN1, KC_BTN2, KC_ACL0, KC_ACL1, KC_ACL2
    )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

