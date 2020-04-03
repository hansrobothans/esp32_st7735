/*
* @file         esp.c 
* @brief        用户应用程序入口
* @details      用户应用程序的入口文件,用户所有要实现的功能逻辑均是从该文件开始或者处理
* @author       hans
* @par Copyright (c):  
*               个人开发库，QQ：304872739
* @par History:          
*               Ver0.0.1:
                     hans, 2019/09/02, 初始化版本\n 
*/

# include"bsp_esp32.h"

void app_main()
{
    // 初始化flash
    // 确认flash没有问题
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    printf("haha\n");

    // // st7735测试
    st7735_init();    
    // st7735_image();
    st7735_rect(60, 60, 50, 50, COLOR_RED);
    // for(int i=0;i<30;i++)
    //     for(int j=0;j<10;j++)
    //         st7735_draw_pixel(i, j, COLOR_WHITE);
    // for(int i=30;i<40;i++)
    //     for(int j=30;j<40;j++)
    //         st7735_draw_pixel(i, j, COLOR_RED);
    // st7735_rect(60, 60, 50, 50, COLOR_WHITE);

    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    // st7735_draw_string(0, 1, "I LOVE benben", COLOR_WHITE, COLOR_RED,1);

    while(1)
    {
        printf("haha\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }



}   

