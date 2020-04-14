#ifndef BSP_LVGL_USER_H
#define BSP_LVGL_USER_H "BSP_LVGL_USER_H"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_freertos_hooks.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"


#include "tftspi.h"
#include "fontx.h"
#include "bmpfile.h"
#include "decode_image.h"
#include "tft.h"
#include "lvgl.h"

#if CONFIG_BSP_ESP_SD_ENABLE
#include "bsp_sd_card.h"
#endif 

#define LVGLUserDebug 0
// if(LVGLUserDebug)printf("[LVGLUserDebug]\n");
#define LVGLUserDelayDebug 20


//设置显示缓冲区,如下代码
extern lv_disp_buf_t disp_buf;      //定义变量disp_buf
extern lv_color_t buf[CONFIG_WIDTH * 10];   //声明缓冲区大小


void lvgl_user_init(void);
void lvgl_text(void);

void demo_create(void);
#endif //BSP_LVGL_USER_H