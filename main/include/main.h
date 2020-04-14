#ifndef ESP32_H
#define ESP32_H "ESP32_H"

//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_spi_flash.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"
#include "esp_heap_caps.h"

#include "nvs_flash.h"
#include "soc/gpio_struct.h"

#include "sdkconfig.h"


// 功能支持库
#include "tftspi.h"
#include "fontx.h"
#include "bmpfile.h"
#include "decode_image.h"
#include "tft.h"
#include "display.h"
#include "bsp_sd_card.h"
#include "bsp_watch.h"
#include "bsp_lvgl_user.h"
#include "Rabbit.h"
#include "cube.h"

#endif//ESP32_H