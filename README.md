# Lvgl flash font
let lvgl font read in `extend flash` or `tf card` and use less memory;

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

## Make a font
1. Install nodejs
2. Prepare `.fft`
3. Run in Cmd
```
npx lv_font_conv --font .\xxx.ttf -r 0x00-0xFFFF --size 16 --format bin --no-compress --bpp 2 -o fz16_no.font
```
