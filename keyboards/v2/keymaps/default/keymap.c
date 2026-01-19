#include <stdint.h>
#include "config.h"
#include QMK_KEYBOARD_H

#if __has_include("keymap.h")
#include "keymap.h"
#endif

enum custom_layer {
    DEFAULT,
    NAV,
    SYM,
    FUNC,
    MOUSE,
    WASD,
    WASD_AUX,
    LEAGUE,
    LEAGUE_AUX,
};

void pointing_device_init_user(void) {
    set_auto_mouse_layer(MOUSE);
    set_auto_mouse_enable(true);
}

enum custom_keycodes {
    SCROLL = SAFE_RANGE,
    TG_SCRL,
};

bool set_scrolling = false;
bool toggle_scrolling = false;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 25.0
#define SCROLL_DIVISOR_V 25.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (toggle_scrolling ^ set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += -(float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// Function to handle key events and enable/disable drag scrolling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SCROLL:
            if (record->event.pressed == true) {
                set_scrolling = true;
            } else {
                set_scrolling = false;
            }
            return false;
        case TG_SCRL:
            if (record->event.pressed == true) {
                toggle_scrolling = !toggle_scrolling;
            }
            return false;
        default:
            break;
    }
    return true;
}

// Function to handle layer changes and disable drag scrolling when not in AUTO_MOUSE_DEFAULT_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    // Disable set_scrolling if the current layer is not the AUTO_MOUSE_DEFAULT_LAYER
    if (get_highest_layer(state) != AUTO_MOUSE_DEFAULT_LAYER) {
        set_scrolling = false;
        // uncomment if scrolling should reset on mouse layer release
        // toggle_scrolling = false;
    }
    return state;
}
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [DEFAULT] = LAYOUT(
        QK_GESC, KC_Q,    KC_W,   KC_E,    KC_R,             KC_T,                            /**/    KC_Y,    KC_U,    KC_I,     KC_O,   KC_P,         LT(MOUSE, KC_BSLS),
        KC_LSFT, KC_A,    KC_S,   KC_D,    KC_F,             KC_G,                            /**/    KC_H,    KC_J,    KC_K,     KC_L,   KC_SEMICOLON, KC_RSFT,
        KC_LCTL, KC_Z,    KC_X,   KC_C,    KC_V,             KC_B,                            /**/    KC_N,    KC_M,    KC_COMMA, KC_DOT, KC_SLASH,     KC_RCTL,
                                  LT(MOUSE, KC_DEL),  LT(NAV, KC_ENT),  LT(FUNC, KC_TAB),     /**/    KC_BSPC, LT(SYM, KC_SPC),  KC_QUOT,
		                      	  KC_LGUI, KC_LALT
    ),

    [NAV] = LAYOUT(
        KC_TRNS, KC_ESC,  KC_PGUP, KC_UP,   KC_PGDN,  KC_TRNS,    /**/    KC_PAST, KC_7,     KC_8,    KC_9,   KC_MINS, KC_NUM,
        KC_LPRN, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,    /**/     KC_PSLS, KC_4,     KC_5,    KC_6,   KC_PPLS, KC_RPRN,
        KC_LCBR, KC_LT,   KC_GT,   KC_LBRC, KC_RBRC,  KC_TRNS,    /**/    KC_PEQL, KC_1,     KC_2,    KC_3,   KC_0,    KC_RCBR,
                                   KC_TRNS, KC_TRNS,  KC_TRNS,    /**/    KC_TRNS, KC_PDOT,  KC_COMM,
		                      	   KC_TRNS, KC_TRNS
    ),

    [SYM] = LAYOUT(
         KC_TRNS, KC_EXLM, KC_AT,   KC_HASH,      KC_DLR,  KC_PERCENT,    /**/   KC_CIRC, KC_AMPR, KC_ASTR,   KC_UNDS, KC_EQUAL, KC_TRNS,
         KC_TRNS, KC_MINS, KC_LBRC, KC_LCBR,      KC_LPRN, KC_LT,         /**/   KC_GT,   KC_RPRN, KC_RCBR,   KC_RBRC,  KC_PLUS,  KC_TRNS,
         KC_TRNS, KC_CAPS, KC_GRV,  C(S(KC_TAB)), C(S(KC_T)), CW_TOGG,    /**/   KC_TRNS, C(KC_T), C(KC_TAB), KC_TRNS,  KC_TRNS,  C(KC_W),
                                    KC_TRNS,      KC_TRNS, KC_TRNS,       /**/   KC_TRNS, KC_TRNS, KC_TRNS,
		                      	                  KC_TRNS, KC_TRNS
    ),

    [FUNC] = LAYOUT(
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      /**/    KC_MUTE, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,
        KC_TRNS, TG(WASD), TG(LEAGUE), KC_TRNS, KC_TRNS, KC_TRNS,  /**/    KC_VOLU, KC_F4, KC_F5, KC_F6, KC_F11, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      /**/    KC_VOLD, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,      /**/    KC_MPRV, KC_MPLY, KC_MNXT,
		                      	   KC_TRNS, KC_TRNS
    ),

    [MOUSE] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_TRNS,   SCROLL,  TG_SCRL, KC_TRNS, KC_TRNS, KC_TRNS,
        MS_WHLU, MS_WHLD, MS_BTN3, MS_BTN2, MS_BTN1, KC_TRNS,    /**/    TG(MOUSE), MS_BTN1, MS_BTN2, MS_BTN3, MS_WHLD, MS_WHLU,
        KC_TRNS, KC_TRNS, KC_TRNS, TG_SCRL, SCROLL,  KC_TRNS,    /**/    KC_TRNS,   MS_BTN4, MS_BTN3, MS_BTN5, KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_TRNS,   KC_TRNS, KC_TRNS,
		                      	   KC_TRNS, KC_TRNS
    ),

    [WASD] = LAYOUT(
        KC_T, KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,       /**/    KC_T,        KC_Y,    KC_U,    KC_I,     KC_O,   KC_P,
        KC_G, KC_LSFT, KC_A,    KC_S,   KC_D,    KC_F,       /**/    KC_G,        KC_H,    KC_J,    KC_K,     KC_L,   KC_SEMICOLON,
        KC_B, KC_LCTL, KC_Z,    KC_X,   KC_C,    KC_V,       /**/    KC_B,        KC_N,    KC_M,    KC_COMMA, KC_DOT, KC_SLASH,
                  LT(WASD_AUX, KC_ESC), KC_SPC,  KC_RCTL,    /**/    TG(WASD), KC_SPC,  KC_QUOT,
		                    	KC_LGUI, KC_LALT
    ),

    [WASD_AUX] = LAYOUT(
        QK_GESC, KC_Q,    KC_W,   KC_E,    KC_R,   KC_T,       /**/    KC_Y,    KC_U,    KC_I,     KC_O,   KC_P,         KC_BSLS,
        KC_LSFT, KC_A,    KC_S,   KC_D,    KC_F,   KC_G,       /**/    KC_H,    KC_J,    KC_K,     KC_L,   KC_SEMICOLON, KC_RSFT,
        KC_LCTL, KC_Z,    KC_X,   KC_C,    KC_V,   KC_B,       /**/    KC_N,    KC_M,    KC_COMMA, KC_DOT, KC_SLASH,     KC_RCTL,
                                  KC_DEL,  KC_ENT, KC_TAB,     /**/    KC_BSPC, KC_SPC,  KC_QUOT,
		                      	  KC_LGUI, KC_LALT
    ),

    [LEAGUE] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4,   KC_5,    /**/    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R,   KC_T,    /**/    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_B,   KC_A, KC_S, KC_D, KC_F,   KC_G,    /**/    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  MO(LEAGUE_AUX), KC_SPC, KC_TAB,  /**/    TG(LEAGUE), KC_TRNS, KC_TRNS,
		                    KC_TRNS, KC_TRNS
    ),

    [LEAGUE_AUX] = LAYOUT(
        KC_TRNS, KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,      /**/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TAB, C(KC_Q), C(KC_W), C(KC_E), C(KC_R), KC_T,       /**/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_P,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_G,       /**/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_TRNS, KC_TRNS, KC_TRNS,
		                          KC_TRNS, KC_TRNS
    )

};

