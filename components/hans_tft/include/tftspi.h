#ifndef MAIN_TFTSPI_H_
#define MAIN_TFTSPI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"
#include "esp_heap_caps.h"

#include <driver/spi_master.h>
#include <driver/gpio.h>
#include <driver/spi_master.h>

#include "fontx.h"

#define RED				0xf800
#define GREEN			0x07e0
#define BLUE			0x001f
#define BLACK			0x0000
#define WHITE			0xffff
#define GRAY			0x8c51
#define YELLOW			0xFFE0
#define CYAN			0x07FF
#define PURPLE			0xF81F


#define DIRECTION0		0
#define DIRECTION90		1
#define DIRECTION180		2
#define DIRECTION270		3



#define TAG "TFT"
#define	_DEBUG_ 0

#define GPIO_MOSI CONFIG_MOSI_GPIO
#define GPIO_SCLK CONFIG_SCLK_GPIO
#define GPIO_MISO CONFIG_MISO_GPIO

#define SPI_Command_Mode 0
#define SPI_Data_Mode 1
//#define SPI_Frequency SPI_MASTER_FREQ_20M
//#define SPI_Frequency SPI_MASTER_FREQ_26M
// #define SPI_Frequency SPI_MASTER_FREQ_40M
#define SPI_Frequency SPI_MASTER_FREQ_80M



typedef struct {
	uint16_t _model;
	uint16_t _width;
	uint16_t _height;
	uint16_t _offsetx;
	uint16_t _offsety;
	uint16_t _font_direction;
	uint16_t _font_fill;
	uint16_t _font_fill_color;
	uint16_t _font_underline;
	uint16_t _font_underline_color;
	int16_t _dc;
	int16_t _bl;
	spi_device_handle_t _SPIHandle;
} TFT_t;
extern TFT_t dev;

void spi_master_init(TFT_t * dev, int16_t GPIO_CS, int16_t GPIO_DC, int16_t GPIO_RESET, int16_t GPIO_BL);
bool spi_master_write_byte(spi_device_handle_t SPIHandle, const uint8_t* Data, size_t DataLength);
bool spi_master_write_comm_byte(TFT_t * dev, uint8_t cmd);
bool spi_master_write_comm_word(TFT_t * dev, uint16_t cmd);
bool spi_master_write_data_byte(TFT_t * dev, uint8_t data);
bool spi_master_write_data_word(TFT_t * dev, uint16_t data);
bool spi_master_write_addr(TFT_t * dev, uint16_t addr1, uint16_t addr2);
bool spi_master_write_color(TFT_t * dev, uint16_t color, uint16_t size);
bool spi_master_write_colors(TFT_t * dev, uint16_t * colors, uint16_t size);

void delayMS(int ms);
void SPIFFS_Directory(char * path);
#endif /* MAIN_TFTSPI_H_ */

