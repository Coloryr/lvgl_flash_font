#ifndef LVGL_MYFONT_H
#define LVGL_MYFONT_H

#include "font/lv_font.h"
#include "font_load.h"

#ifdef __cplusplus
extern "C" {
#endif

void load_font(uint8_t clear);

#ifdef __cplusplus
}
#endif

extern my_font_data font_16;
extern my_font_data font_24;
extern my_font_data font_32;

#endif //LVGL_MYFONT_H
