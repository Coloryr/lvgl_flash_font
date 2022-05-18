#ifndef LVGL_FONT_WRITE_H
#define LVGL_FONT_WRITE_H

#include "main.h"
#include "font_config.h"

#if USE_TF == 0

//the lvgl font start addr
#define FONT_ADDR 0x1000

//font bit save addr
#define SAVE_ADDR 0x100
#define SAVE_BIT 0xA5
//read and write buff size
#define TEMP_L 0x8000

uint32_t write_font(uint32_t pos, uint32_t addr, const char *path);

#endif

#endif //LVGL_FONT_WRITE_H
