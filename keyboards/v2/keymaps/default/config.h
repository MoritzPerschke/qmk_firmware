#pragma once

#define SOFT_SERIAL_PIN GP1
#define MASTER_LEFT
#define SPLIT_POINTING_ENABLE

// https://github.com/siderakb/pmw3360-pcb/blob/main/firmware/qmk/pmw3360_rp2040/info.json
// https://cdn.discordapp.com/attachments/1114846164907479139/1319383503267434546/Dactyl_Wiring.png?ex=67929624&is=679144a4&hm=6c93f193418ef5bcca5a433b0bf0fa8531384d25ff862bf3e85eb4aa7b195b6b&
// QMK uses hardware SPI, can't redefine these pins

#define POINTING_DEVICE_RIGHT
#define PMW33XX_CS_PIN GP21
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN GP20

#define PMW33XX_LIFTOFF_DISTANCE 0x03
#define PMW33XX_CPI 400

#define POINTING_DEVICE_ROTATION_90
#define POINTING_DEVICE_INVERT_X
#define ROTATIONAL_TRANSFORM_ANGLE 45

#define MOUSEKEY_MOVE_DELTA 6
#define MOUSEKEY_DELAY 11

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_TIME 500 // default 650
#define AUTO_MOUSE_DELAY 500 //default 200
#define AUTO_MOUSE_THRESHOLD 10 // default 10

// #define SCROLL_DIVISOR 25.0
