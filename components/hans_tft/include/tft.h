#ifndef MAIN_TFT_H_
#define MAIN_TFT_H_

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


#define	INTERVAL		400
#define WAIT	vTaskDelay(INTERVAL)

// You have to set these CONFIG value using menuconfig.
#if 0
#define CONFIG_WIDTH  240
#define CONFIG_HEIGHT 320
#define CONFIG_CS_GPIO 5
#define CONFIG_DC_GPIO 26
#define CONFIG_RESET_GPIO 2
#define CONFIG_BL_GPIO 2
#endif

void SPIFFS_Directory(char * path);
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

#endif /* MAIN_TFT_H_ */