#include "bsp_lvgl_user.h"

//Creates a semaphore to handle concurrent call to lvgl stuff
//If you wish to call *any* lvgl function from other threads/tasks
//you should lock on the very same semaphore!
SemaphoreHandle_t xGuiSemaphore;
//设置显示缓冲区,如下代码
lv_disp_buf_t disp_buf;      //定义变量disp_buf
lv_color_t buf1[CONFIG_WIDTH * 100];   //声明缓冲区大小
lv_color_t buf2[CONFIG_WIDTH * 100];   //声明缓冲区大小

int text_num = 0;

//回调函数的打点驱动函数实现
void my_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
{

    // 一下全部打点
    // int x1,x2,y1,y2;
    // x1 = area->x1;
    // x2 = area->x2;
    // y1 = area->y1;
    // y2 = area->y2;
    // if(LVGLUserDebug)printf("[LVGLUserDebug]:%d",++text_num);
    // if(LVGLUserDebug)printf("[LVGLUserDebug]:x1:%d\tx2:%d\ty1:%d\ty2:%d\t\n",x1, x2, y1, y2);
    // lcdDrawMultiPixels_lvgl(&dev, x1, x2, y1, y2,color_p);
    // lv_disp_flush_ready(disp); 
    
    // 一行行打点
    int32_t y, w;
    w = area->x2 - area->x1 + 1;

    if(LVGLUserDebug)printf("[LVGLUserDebug]:%d\n",++text_num);
    for(y = area->y1; y <= area->y2; y++) 
    {
        // vTaskDelay(1);
        lcdDrawMultiPixels(&dev,area->x1,y, w,color_p);
        color_p += w;
    }
    lv_disp_flush_ready(disp); 

    // 一个个打点
    // int32_t x, y;
    // for(y = area->y1; y <= area->y2; y++) 
    // {
    //     for(x = area->x1; x <= area->x2; x++)
    //     {
    //        lcdDrawPixel(&dev, x, y,color_p->full );//自己的打点函数
    //        color_p++;
    //     }
    // }
    // lv_disp_flush_ready(disp); 
}

static void IRAM_ATTR lv_tick_task(void *arg) {
    (void) arg;

    lv_tick_inc(portTICK_RATE_MS);
    // lv_tick_inc(10);
}

void lvgl_user_init(void)
{
    lv_init();
    TFT_INIT();
    lv_disp_buf_init(&disp_buf, buf1, buf2, CONFIG_WIDTH * 10);  //初始化显示缓冲区


    //像素打点,函数注册
    lv_disp_drv_t disp_drv;             //定义变量disp_drv
    lv_disp_drv_init(&disp_drv);        //初始化
    disp_drv.flush_cb = my_disp_flush;  //设置驱动功能的回调函数名
    disp_drv.buffer = &disp_buf;        //将缓冲区分配给显示器
    lv_disp_drv_register(&disp_drv);    //注册驱动程序

    const esp_timer_create_args_t periodic_timer_args = {
            .callback = &lv_tick_task,
            /* name is optional, but may help identify the timer when debugging */
            .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    //On ESP32 it's better to create a periodic task instead of esp_register_freertos_tick_hook
    // ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1*1000)); //10ms (expressed as microseconds)
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 10*1000)); //10ms (expressed as microseconds)
}
void lvgl_text(void)
{
    xGuiSemaphore = xSemaphoreCreateMutex();
    lvgl_user_init();

    demo_create();
    // lv_obj_t * scr = lv_disp_get_scr_act(NULL);     /*Get the current screen*/

    // /*Create a Label on the currently active screen*/
    // lv_obj_t * label1 =  lv_label_create(scr, NULL);

    // /*Modify the Label's text*/
    // lv_label_set_text(label1, "Hello world!");

    // /* Align the Label to the center
    //  * NULL means align on parent (which is the screen now)
    //  * 0, 0 at the end means an x, y offset after alignment*/
    // lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
    while (1) 
    {
        vTaskDelay(1);
        //Try to lock the semaphore, if success, call lvgl stuff
        if (xSemaphoreTake(xGuiSemaphore, (TickType_t)10) == pdTRUE) 
        {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
        }
    }
}
