#ifndef LVGL_FONT_LOAD_H
#define LVGL_FONT_LOAD_H

#include "lvgl.h"
#include "font_config.h"

#include "fatfs.h"

typedef struct font_header_bin {
    uint32_t version;
    uint16_t tables_count;
    uint16_t font_size;
    uint16_t ascent;
    int16_t descent;
    uint16_t typo_ascent;
    int16_t typo_descent;
    uint16_t typo_line_gap;
    int16_t min_y;
    int16_t max_y;
    uint16_t default_advance_width;
    uint16_t kerning_scale;
    uint8_t index_to_loc_format;
    uint8_t glyph_id_format;
    uint8_t advance_width_format;
    uint8_t bits_per_pixel;
    uint8_t xy_bits;
    uint8_t wh_bits;
    uint8_t advance_width_bits;
    uint8_t compression_id;
    uint8_t subpixels_mode;
    uint8_t padding;
    int16_t underline_position;
    uint16_t underline_thickness;
} font_header_bin_t;

typedef struct {
    lv_font_t font;
    uint32_t length;
    lv_font_fmt_txt_glyph_cache_t cache;
    lv_font_fmt_txt_dsc_t dsc;
    uint32_t glyph_start;
    font_header_bin_t header_bin;
    uint32_t loca_count;
    uint32_t loca_start;
    uint32_t glyph_length;
    uint8_t *glyph_bmp;
#if USE_TF == 0
    uint32_t file_local;
#else
    const char* file_name;
    font_load_fp fp;
#endif
} my_font_data;

void font_load(my_font_data *font);

#endif //LVGL_FONT_LOAD_H
