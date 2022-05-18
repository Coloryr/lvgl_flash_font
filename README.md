# Lvgl flash font
let lvgl font read in `flash` or `extend flash` or `tf card` and use less memory;

## Usage
1. copy all code to your project
2. fix all mark `TODO` funtion
3. init it
```c
#include "myfont.h"

void init(void)
{
    load_font(0);
}
```
4. switch font
```c
#include "myfont.h"

void show_init(void)
{
    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(label1, &font_16.font, 0);
}
```