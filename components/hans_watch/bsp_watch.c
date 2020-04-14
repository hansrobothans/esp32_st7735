#include "bsp_watch.h"
void watch_background(void)
{
    TFT_INIT();
    lcdFillScreen(&dev, BLACK);
    lcdDrawCircle(&dev, CONFIG_WIDTH/2, CONFIG_HEIGHT/2, 100, RED);
}

void watch_pointer(void)
{
    float hour_pointer = 0;
    float second_pointer = 0;
    float minute_pointer = 0;
    while(1)
    {
         // * Params:
         // *       x: horizontal start position
         // *       y: vertical start position
         // *   start: start offset from (x,y)
         // *     len: length of the line
         // *   angle: line angle in degrees
         // *   color: line color
        // 绘制秒针
        TFTDrawLineByAngle(&dev, CONFIG_WIDTH/2, CONFIG_HEIGHT/2, 0, 80, second_pointer*6, GREEN);
        // 绘制分针
        TFTDrawLineByAngle(&dev, CONFIG_WIDTH/2, CONFIG_HEIGHT/2, 0, 60, (minute_pointer+second_pointer/60)*6, BLUE);
        // 绘制时针
        TFTDrawLineByAngle(&dev, CONFIG_WIDTH/2, CONFIG_HEIGHT/2, 0, 40, (hour_pointer+minute_pointer/60)*30, RED);
        vTaskDelay(WATCHDelayDebug);
        // 绘制秒针
        TFTDrawLineByAngle(&dev, CONFIG_WIDTH/2, CONFIG_HEIGHT/2, 0, 80, second_pointer*6, BLACK);
        // 绘制分针
        TFTDrawLineByAngle(&dev, CONFIG_WIDTH/2, CONFIG_HEIGHT/2, 0, 60, (minute_pointer+second_pointer/60)*6, BLACK);
        // 绘制时针
        printf("%f\n", hour_pointer);
        TFTDrawLineByAngle(&dev, CONFIG_WIDTH/2, CONFIG_HEIGHT/2, 0, 40, (hour_pointer+minute_pointer/60)*30, BLACK);
        watch_print_time(&hour_pointer,&minute_pointer,&second_pointer);
    }

}
void watch_print_time(float *hour_pointer,float *minute_pointer,float *second_pointer)
{
    time_t now;
    char strftime_buf[64];
    struct tm timeinfo;

    time(&now);
    // Set timezone to China Standard Time
    setenv("TZ", "CST-8", 1);
    tzset();

    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);

    *hour_pointer = timeinfo.tm_hour;
    *minute_pointer = timeinfo.tm_min;
    *second_pointer = timeinfo.tm_sec;

    ESP_LOGI(TAG, "当前时间：\tisdst:%d\tyday:%d\twday:%d\tyear:%d\tmon:%d\tmday:%d\thour:%d\tmin:%d\tsec:%d",
        timeinfo.tm_isdst, timeinfo.tm_yday,
        timeinfo.tm_wday, timeinfo.tm_year,
        timeinfo.tm_mon, timeinfo.tm_mday,
        timeinfo.tm_hour, timeinfo.tm_min,
        timeinfo.tm_sec);
    ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);
}


    // struct timeval tv; // struct timeval {
    //                    // time_t      tv_sec;     /* seconds */
    //                    // suseconds_t tv_usec;    /* microseconds */
    //                    // };

    // gettimeofday(&tv, NULL); //  and gives the number of seconds and microseconds since the Epoch (see
    //                          // time(2)).  The tz argument is a struct timezone:

    // secondsSinceEpoch = (uint64_t)(tv.tv_sec); 


