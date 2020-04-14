#include "main.h"



void app_main(void)
{
	//sd卡初始化
	// SD_INIT();
	//sd卡测试函数
	// sd_text();
	//卸载sd卡
	// SD_UNMOUNT();
	
	//测试tft  开始
	ESP_LOGI(TAG, "Initializing SPIFFS");

	esp_vfs_spiffs_conf_t conf = {
		.base_path = "/spiffs",
		.partition_label = NULL,
		.max_files = 8,
		.format_if_mount_failed =true
	};

	// Use settings defined above toinitialize and mount SPIFFS filesystem.
	// Note: esp_vfs_spiffs_register is anall-in-one convenience function.
	esp_err_t ret =esp_vfs_spiffs_register(&conf);

	if (ret != ESP_OK) {
		if (ret == ESP_FAIL) {
			ESP_LOGE(TAG, "Failed to mount or format filesystem");
		} else if (ret == ESP_ERR_NOT_FOUND) {
			ESP_LOGE(TAG, "Failed to find SPIFFS partition");
		} else {
			ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)",esp_err_to_name(ret));
		}
		return;
	}

	size_t total = 0, used = 0;
	ret = esp_spiffs_info(NULL, &total,&used);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG,"Failed to get SPIFFS partition information (%s)",esp_err_to_name(ret));
	} else {
		ESP_LOGI(TAG,"Partition size: total: %d, used: %d", total, used);
	}

	SPIFFS_Directory("/spiffs/");
	xTaskCreate(TFT_TEXT, "TFT_TEXT", 1024*6, NULL, 2, NULL);
	//测试tft  结束

	//非创建任务式测试屏幕
	// TFT_TEXT(NULL);

	//测试表的代码
	// watch_background();
	// watch_pointer();

	// 测试lvgl代码
	// xTaskCreatePinnedToCore(lvgl_text, "gui", 4096*2, NULL, 0, NULL, 1);
	// lvgl_text();
	
	//测试快速填充
	// TFT_INIT();
	// while(1)
	// {
	// 	lcdDrawFillRect(&dev, 0, 0, 135, 120, RED);
	// 	vTaskDelay(400);
	// 	lcdDrawFillRect(&dev, 0, 0, 135, 120, BLUE);
	// 	vTaskDelay(400);
	// }

	//测试显示小兔子
	// do3d();

	//测试旋转正方体
	// TFT_INIT();
	// draw_cube();

	// while(1)
	// {
	// 	sd_text();
	// 	vTaskDelay(400);
	// }
	// while(1)
	// {
	// 	printf("haha\n");
	// 	vTaskDelay(400);
	// }
	
}
