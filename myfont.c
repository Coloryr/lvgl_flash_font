#include "lvgl.h"
#include "main.h"
#include "myfont.h"
#include "misc/lv_utils.h"

#include "font_load.h"
#include "font_config.h"

#if USE_TF == 0

#include "font_write.h"
#include "font_read.h"

#endif

#define FONT_16_FILE "0:/font/16.font"
#define FONT_24_FILE "0:/font/24.font"
#define FONT_32_FILE "0:/font/32.font"

my_font_data font_16;
my_font_data font_24;
my_font_data font_32;

uint8_t glyph16[2 * 16 * 3];
uint8_t glyph24[3 * 24 * 3];
uint8_t glyph32[4 * 32 * 3];
/*
 * cleaar = 1,rewrite all font
 */
void load_font(uint8_t clear) {
#if USE_TF == 0
    uint8_t temp[20];
    uint32_t pos = FONT_ADDR;
    font_len_cov cov;

    init_fp();

    //TODO flash read
    flash_read(temp, SAVE_ADDR, 20);
    if (temp[0] != SAVE_BIT || clear == 1) {
        font_16.length = write_font(pos, SAVE_ADDR, FONT_16_FILE);
    } else {
        cov.u8[0] = temp[1];
        cov.u8[1] = temp[2];
        cov.u8[2] = temp[3];
        cov.u8[3] = temp[4];
        font_16.length = cov.u32;
    }

    pos = FONT_ADDR + font_16.length;

    if (temp[5] != SAVE_BIT || clear == 1) {
        font_24.length = write_font(pos, SAVE_ADDR + 5, FONT_24_FILE);
    } else {
        cov.u8[0] = temp[6];
        cov.u8[1] = temp[7];
        cov.u8[2] = temp[8];
        cov.u8[3] = temp[9];
        font_24.length = cov.u32;
    }

    pos = FONT_ADDR + font_16.length + font_24.length;

    if (temp[10] != SAVE_BIT || clear == 1) {
        font_32.length = write_font(pos, SAVE_ADDR + 10, FONT_32_FILE);
    } else {
        cov.u8[0] = temp[11];
        cov.u8[1] = temp[12];
        cov.u8[2] = temp[13];
        cov.u8[3] = temp[14];
        font_32.length = cov.u32;
    }

    font_16.file_local = FONT_ADDR;
    font_24.file_local = FONT_ADDR + font_16.length;
    font_32.file_local = FONT_ADDR + font_16.length + font_24.length;

#else

    font_16.file_name = FONT_16_FILE;
    font_24.file_name = FONT_24_FILE;
    font_32.file_name = FONT_32_FILE;

    f_open(&font_16.fp.fp, FONT_16_FILE, FA_READ);
    f_open(&font_24.fp.fp, FONT_24_FILE, FA_READ);
    f_open(&font_32.fp.fp, FONT_32_FILE, FA_READ);

#endif

    font_16.glyph_bmp = glyph16;
    font_24.glyph_bmp = glyph24;
    font_32.glyph_bmp = glyph32;

    font_load(&font_16);
    font_load(&font_24);
    font_load(&font_32);
}

