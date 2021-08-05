
#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// #define SSD1306OLED
#undef USE_I2C
#undef SSD1306OLED

#define USE_SERIAL_PD2

// #define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
//#define RETRO_TAPPING
#define IGNORE_MOD_TAP_INTERRUPT

#define OLED_FONT_H "keyboards/crkbd/keymaps/casum/glcdfont.c"
#define OLED_FONT_WIDTH 5
// #define OLED_FONT_HEIGHT 7

#ifdef RGB_MATRIX_ENABLE

#endif
