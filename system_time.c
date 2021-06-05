/* 
   This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

void get_sys_time()
{
    time_t current_time;
    char* c_time_string;

    /* Obtain current time. */
    current_time = time(NULL);

    if (current_time == ((time_t)-1))
    {
        printf("Failure to obtain the current time.\n");
        return;
    }

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    if (c_time_string == NULL)
    {
        printf("Failure to convert the current time.\n");
        return;
    }

    /* Print to stdout. ctime() has already added a terminating newline character. */
    printf("Current time is %s", c_time_string);
}

void set_sys_time(void)
{
    struct tm current_time = 
    {
        .tm_sec   = 0,
        .tm_min   = 50,        /* minutes */
        .tm_hour  = 20,        /* hours */
        .tm_mday  = 5,         /* day of the month */
        .tm_mon   = 5,         /* month */
        .tm_year  = 121,       /* year */
        //.tm_wday  = 5,         /* day of the week */
        //.tm_yday  = 155,       /* day in the year */
        .tm_isdst = 1,         /* daylight saving time */
    };

    time_t curr_time_since_epoch = mktime(&current_time);
    struct timespec ts = 
    {
        .tv_sec = curr_time_since_epoch,
    };
    
    if (clock_settime(CLOCK_REALTIME, &ts) == 0)
        printf("Time is set succesfully\n");
    else
        printf("Time wasn't set. Error\n");
}

void app_main(void)
{
    printf("Start\n");

    set_sys_time();

    for (uint8_t i = 0; i < 10; i++)
    {        
        get_sys_time();
        vTaskDelay(100);
    }

    printf("Stopping.\n");
}
