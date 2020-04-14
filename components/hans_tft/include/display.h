#ifndef MAIN_DISPLAY_H_
#define MAIN_DISPLAY_H_ "MAIN_DISPLAY_H_"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"
#include "esp_heap_caps.h"

#include "tftspi.h"
#include "fontx.h"
#include "bmpfile.h"
#include "decode_image.h"
#include "tft.h"

#if CONFIG_BSP_ESP_SD_ENABLE
#include "bsp_sd_card.h"
#endif 
#define DISPLAYDebug 1
// if(DISPLAYDebug)printf("[DISPLAYDebug]\n");

TickType_t FillTest(TFT_t * dev, int width, int height);
TickType_t ColorBarTest(TFT_t * dev, int width, int height);
TickType_t ArrowTest(TFT_t * dev, FontxFile *fx, uint16_t model, int width, int height);
TickType_t DirectionTest(TFT_t * dev, FontxFile *fx, int width, int height);
TickType_t HorizontalTest(TFT_t * dev, FontxFile *fx, int width, int height);
TickType_t VerticalTest(TFT_t * dev, FontxFile *fx, int width, int height);
TickType_t LineTest(TFT_t * dev, int width, int height);
TickType_t CircleTest(TFT_t * dev, int width, int height);
TickType_t RectAngleTest(TFT_t * dev, int width, int height);
TickType_t TriangleTest(TFT_t * dev, int width, int height);
TickType_t RoundRectTest(TFT_t * dev, int width, int height);
TickType_t FillRectTest(TFT_t * dev, int width, int height);
TickType_t ColorTest(TFT_t * dev, int width, int height);
TickType_t ScrollTest(TFT_t * dev, FontxFile *fx, int width, int height);
void ScrollReset(TFT_t * dev);
TickType_t BMPTest(TFT_t * dev, char * file, int width, int height);
TickType_t JPEGTest(TFT_t * dev, char * file, int width, int height);
void TFT_TEXT(void *pvParameters);

#endif /* MAIN_DISPLAY_H_ */