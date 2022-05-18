#ifndef LVGL_FONT_CONFIG_H
#define LVGL_FONT_CONFIG_H

#define USE_TF 0

#include "main.h"
#include "fatfs.h"

typedef struct {
#if USE_TF == 0
    uint32_t local;
    uint32_t pos;
    uint8_t use;
#else
    FIL fp;
#endif
} font_load_fp;

typedef union {
    uint32_t u32;
    uint8_t u8[4];
} font_len_cov;

#endif //LVGL_FONT_CONFIG_H
