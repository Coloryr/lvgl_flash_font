#include "font_read.h"
#include "myfont.h"
#include "fatfs.h"
#include "lvgl.h"
#include "font_config.h"

my_font_data *get_font_data(lv_font_t *font);

font_load_fp *start_read(my_font_data *font_data);

void read(font_load_fp *fp, void *data, uint16_t size);

void stop_read(font_load_fp *fp);

void error(const char *data);

void set_pos(font_load_fp *, uint32_t);

void add_pos(font_load_fp *, uint32_t);

font_load_api_ font_load_api = {
        .get_font_data = get_font_data,
        .start_read = start_read,
        .read = read,
        .stop_read = stop_read,
        .error = error,
        .set_pos = set_pos,
        .add_pos = add_pos
};

#if USE_TF == 0
#define WORK_LENGTH 16

font_load_fp font_fp[WORK_LENGTH];

void set_pos(font_load_fp *fp, uint32_t pos) {
    fp->pos = pos;
}

void add_pos(font_load_fp *fp, uint32_t pos) {
    fp->pos += pos;
}

font_load_fp *start_read(my_font_data *font_data) {
    for (int i = 0; i < WORK_LENGTH; i++) {
        if (font_fp[i].use == 0) {
            font_fp[i].use = 1;
            font_fp[i].local = font_data->file_local;
            font_fp[i].pos = 0;
            return &font_fp[i];
        }
    }
    while (1);
}

void stop_read(font_load_fp *fp) {
    fp->use = 0;
    fp->pos = 0;
    fp->local = 0;
}

void read(font_load_fp *fp, void *data, uint16_t size) {
    //TODO flash_read
    flash_read(data, fp->local + fp->pos, size);
    fp->pos += size;
}

#else

void set_pos(font_load_fp* fp,uint32_t pos) {
    if (f_tell(&fp->fp) == pos)
        return;
    f_lseek(&fp->fp, pos);
}

void add_pos(font_load_fp* fp,uint32_t pos) {
    FIL fil = fp->fp;
    f_lseek(&fil, f_tell(&fil) + pos);
}

font_load_fp* start_read(my_font_data* font_data){
    return &font_data->fp;
}

void stop_read(font_load_fp* fp) {

}

void read(font_load_fp* fp, void * data, uint16_t size) {
    UINT size1;
    f_read(&fp->fp, data, size, &size1);
}

#endif

my_font_data *get_font_data(lv_font_t *font) {
    if (font == &font_16.font)
        return &font_16;
    else if (font == &font_24.font)
        return &font_24;
    else if (font == &font_32.font)
        return &font_32;

    return NULL;
}

void init_fp() {
#if USE_TF == 0
    for (int i = 0; i < WORK_LENGTH; i++) {
        font_fp[i].use = 0;
        font_fp[i].pos = 0;
        font_fp[i].local = 0;
    }
#endif
}

void error(const char *data) {
    lv_label_set_text(info_label, data);
}
