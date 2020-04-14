#ifndef BSP_WATCH_H
#define BSP_WATCH_H "BSP_WATCH_H"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"

#include "tftspi.h"
#include "fontx.h"
#include "bmpfile.h"
#include "decode_image.h"
#include "tft.h"

#if CONFIG_BSP_ESP_SD_ENABLE
#include "bsp_sd_card.h"
#endif 

#define WATCHDebug 0
// if(WATCHDebug)printf("[WATCHDebug]\n");
#define WATCHDelayDebug 20
void watch_background(void);
void watch_pointer(void);
void watch_print_time(float *hour_pointer,float *minute_pointer,float *second_pointer);
#endif //BSP_WATCH_H