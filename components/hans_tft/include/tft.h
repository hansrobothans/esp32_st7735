#ifndef MAIN_TFT_H_
#define MAIN_TFT_H_ "MAIN_TFT_H_"

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

#if CONFIG_BSP_ESP_SD_ENABLE
#include "bsp_sd_card.h"
#endif 


#define	INTERVAL		400
#define WAIT	vTaskDelay(INTERVAL)

//1开启调试;0关闭调试
#define TFTDebug 0 // for Debug
// if(TFTDebug)printf("[TFTDebug]\n");
//调试延时时间
#define Debugdelay 5

//1-spiffs,0-sd
#define sd_or_spiffs 1

// --- Constants for ellipse function ---
#define TFT_ELLIPSE_UPPER_RIGHT 0x01
#define TFT_ELLIPSE_UPPER_LEFT  0x02
#define TFT_ELLIPSE_LOWER_LEFT  0x04
#define TFT_ELLIPSE_LOWER_RIGHT 0x08

#define DEG_TO_RAD 0.01745329252
#define RAD_TO_DEG 57.295779513
#define deg_to_rad 0.01745329252 + 3.14159265359
// 弧度制(radian measure)角度制(degree measure)


#define USE_HORIZONTAL 2  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏
extern uint16_t st7789_width;
extern uint16_t st7789_hight;

// You have to set these CONFIG value using menuconfig.
#if 0
#define CONFIG_WIDTH  240
#define CONFIG_HEIGHT 320
#define CONFIG_CS_GPIO 5
#define CONFIG_DC_GPIO 26
#define CONFIG_RESET_GPIO 2
#define CONFIG_BL_GPIO 2
#endif

void lcdWriteRegisterWord(TFT_t * dev, uint16_t addr, uint16_t data);
void lcdWriteRegisterByte(TFT_t * dev, uint8_t addr, uint16_t data);
void lcdInit(TFT_t * dev, uint16_t model, int width, int height, int offsetx, int offsety);
void lcdDrawPixel(TFT_t * dev, uint16_t x, uint16_t y, uint16_t color);
void lcdDrawMultiPixels(TFT_t * dev, uint16_t x, uint16_t y, uint16_t size, uint16_t * colors);
void lcdDrawMultiPixels_lvgl(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t * colors);
void lcdDrawFillRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcdDisplayOff(TFT_t * dev);
void lcdDisplayOn(TFT_t * dev);
void lcdInversionOff(TFT_t * dev);
void lcdInversionOn(TFT_t * dev);
void lcdBGRFilter(TFT_t * dev);
void lcdFillScreen(TFT_t * dev, uint16_t color);

void lcdDrawLine(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void TFTDrawLineByAngle(TFT_t * dev, uint16_t x, uint16_t y, uint16_t start, uint16_t len, uint16_t angle, uint16_t color);

void lcdDrawRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcdFillRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

void lcdDrawRectAngle(TFT_t * dev, uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint16_t color);
void lcdFillRectAngle(TFT_t * dev, uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint16_t color);

void lcdDrawTriangle(TFT_t * dev, uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint16_t color);
void lcdFillTriangle(TFT_t * dev, uint16_t xc, uint16_t yc, uint16_t w, uint16_t h, uint16_t angle, uint16_t color);

void lcdDrawCircle(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void lcdFillCircle(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);

void TFTDrawEllipse(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t rx, uint16_t ry, uint16_t color, uint8_t option);
void TFTFillEllipse(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t rx, uint16_t ry, uint16_t color, uint8_t option);

void lcdDrawRoundRect(TFT_t * dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t r, uint16_t color);
void lcdDrawArrow(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t w, uint16_t color);
void lcdDrawFillArrow(TFT_t * dev, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t w, uint16_t color);

uint16_t rgb565_conv(uint16_t r, uint16_t g, uint16_t b);
int lcdDrawChar(TFT_t * dev, FontxFile *fx, uint16_t x, uint16_t y, uint8_t ascii, uint16_t color);
int lcdDrawString(TFT_t * dev, FontxFile *fx, uint16_t x, uint16_t y, uint8_t * ascii, uint16_t color);
//int lcdDrawSJISChar(TFT_t * dev, FontxFile *fx, uint16_t x, uint16_t y, uint16_t sjis, uint16_t color);
//int lcdDrawUTF8Char(TFT_t * dev, FontxFile *fx, uint16_t x, uint16_t y, uint8_t *utf8, uint16_t color);
//int lcdDrawUTF8String(TFT_t * dev, FontxFile *fx, uint16_t x, uint16_t y, unsigned char *utfs, uint16_t color);
void lcdSetFontDirection(TFT_t * dev, uint16_t);
void lcdSetFontFill(TFT_t * dev, uint16_t color);
void lcdUnsetFontFill(TFT_t * dev);
void lcdSetFontUnderLine(TFT_t * dev, uint16_t color);
void lcdUnsetFontUnderLine(TFT_t * dev);
void lcdBacklightOff(TFT_t * dev);
void lcdBacklightOn(TFT_t * dev);
void lcdSetScrollArea(TFT_t * dev, uint16_t tfa, uint16_t vsa, uint16_t bfa);
void lcdResetScrollArea(TFT_t * dev);
void lcdScroll(TFT_t * dev, uint16_t vsp);
uint16_t TFT_INIT(void);
void TFT_SPIP_FREE(void);


#endif /* MAIN_TFT_H_ */