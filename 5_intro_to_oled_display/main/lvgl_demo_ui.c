/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "lvgl.h"
#include "esp_log.h"


static const char *LVGL_TAG = "LVGL_LOG_DS";

void example_lvgl_demo_ui(lv_display_t *disp)
{
    lv_obj_t *scr = lv_display_get_screen_active(disp);
    lv_obj_t *label = lv_label_create(scr);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR); /* Circular scroll */
    lv_label_set_text(label, "Hello Espressif, Hello LVGL.");
    /* Size of the screen (if you use rotation 90 or 270, please use lv_display_get_vertical_resolution) */
    lv_obj_set_width(label, lv_display_get_horizontal_resolution(disp));
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
}

void example_lvgl_custom_ui(lv_display_t *disp)
{
    static uint8_t my_custom_image_data[1024] = {
        [0 ... 127] = 0xFF,   
        [128 ... 255] = 0x00, 
        [256 ... 383] = 0xFF, 
        [384 ... 511] = 0x00, 
        [512 ... 639] = 0xFF, 
        [640 ... 767] = 0x00, 
        [768 ... 895] = 0xFF, 
        [896 ... 1023] = 0x00
    };
    static const lv_image_dsc_t my_custom_image_dsc = {
        // Set the metadata
        .header.w = 128,                     // Image width
        .header.h = 64,                      // Image height
        .header.cf = LV_COLOR_FORMAT_A1,     // Color format: 1-bit Indexed (monochrome)
        
        // Point to the data
        .data = my_custom_image_data,
        .data_size = 1024,                   // Data size: 128 * 64 / 8
    };

    lv_obj_t *scr = lv_display_get_screen_active(disp);
    lv_obj_t *img = lv_img_create(scr);
    lv_img_set_src(img, &my_custom_image_dsc);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void lv_log_esp32_print_cb(lv_log_level_t level, const char * buf) {
    
    ESP_LOGI(LVGL_TAG, "LVGL log level: %d, log message: %s", level, buf);
}