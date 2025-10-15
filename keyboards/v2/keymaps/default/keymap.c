#include <stdint.h>
#include "config.h"
#include QMK_KEYBOARD_H

#if __has_include("keymap.h")
#include "keymap.h"
#endif

enum custom_layer {
    BASE,
    NAV,
    SYM,
    FUNC,
    MOUSE,
};

void pointing_device_init_user(void) {
    set_auto_mouse_layer(MOUSE);
    set_auto_mouse_enable(true);
}

// https://docs.qmk.fm/features/pointing_device#drag-scroll-or-mouse-scroll
enum custom_keycodes {
    SCROLL = SAFE_RANGE,
};
bool set_scrolling = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SCROLL && record->event.pressed) {
        set_scrolling = true;
    }
    return true;
}
// https://docs.qmk.fm/features/pointing_device#advanced-drag-scroll
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;

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
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        QK_GESC, KC_Q,    KC_W,   KC_E,    KC_R,             KC_T,                            /**/    KC_Y,    KC_U,    KC_I,     KC_O,   KC_P,         KC_BSLS,
        KC_LSFT, KC_A,    KC_S,   KC_D,    KC_F,             KC_G,                            /**/    KC_H,    KC_J,    KC_K,     KC_L,   KC_SEMICOLON, KC_RSFT,
        KC_LCTL, KC_Z,    KC_X,   KC_C,    KC_V,             KC_B,                            /**/    KC_N,    KC_M,    KC_COMMA, KC_DOT, KC_SLASH,     KC_RCTL,
                                  LT(MOUSE, KC_DEL),  LT(NAV, KC_ENT),  LT(FUNC, KC_TAB),     /**/    KC_BSPC, LT(SYM, KC_SPC),  KC_QUOT,
		                      	  KC_LGUI, KC_LALT
    ),

    [NAV] = LAYOUT(
        KC_TRNS, KC_ESC,  KC_PGUP, KC_UP,   KC_PGDN, KC_TRNS,    /**/    KC_PAST, KC_P7,    KC_P8,   KC_P9,   KC_MINS, KC_NUM,
        KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,    /**/    KC_PSLS, KC_P4,    KC_P5,   KC_P6,   KC_PPLS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_PEQL, KC_P1,    KC_P2,   KC_P3,   KC_P0,   KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_TRNS, KC_PCMM,  KC_PDOT,
		                      	   KC_TRNS, KC_TRNS
    ),

    [SYM] = LAYOUT(
         KC_TRNS, KC_EXLM, KC_AT,   KC_HASH,      KC_DLR,  KC_PERCENT,    /**/   KC_CIRC, KC_AMPR, KC_ASTR,   KC_UNDS, KC_EQUAL, KC_TRNS,
         KC_TRNS, KC_MINS, KC_LBRC, KC_LCBR,      KC_LPRN, KC_LT,         /**/   KC_GT,   KC_RPRN, KC_RCBR,   KC_RBRC,  KC_PLUS,  KC_TRNS,
         KC_TRNS, KC_CAPS, KC_GRV,  C(S(KC_TAB)), KC_TRNS, CW_TOGG,       /**/   KC_TRNS, KC_TRNS, C(KC_TAB), KC_TRNS,  KC_TRNS,  KC_TRNS,
                                    KC_TRNS,      KC_TRNS, KC_TRNS,       /**/   KC_TRNS, KC_TRNS, KC_TRNS,
		                      	                  KC_TRNS, KC_TRNS
    ),

    [FUNC] = LAYOUT(
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_MUTE, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_VOLU, KC_F4, KC_F5, KC_F6, KC_F11, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_VOLD, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_MPRV, KC_MPLY, KC_MNXT,
		                      	   KC_TRNS, KC_TRNS
    ),

    [MOUSE] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_TRNS, MS_BTN4, MS_BTN5, KC_TRNS, MS_WHLU, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_TRNS, MS_BTN1, MS_BTN2, MS_BTN3, MS_WHLD, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_TRNS, SCROLL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,    /**/    KC_TRNS, KC_TRNS, KC_TRNS,
		                      	   KC_TRNS, KC_TRNS
    )

};

