/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "esp_system.h"
#include "esp_log.h"

#include "bt_controller.h"
#include "nvs_controller.h"

void app_main()
{
    // const char *device = "AWS-810\0";
    // write_device_name(device);
    // clear_device_name();
    char *test = read_device_name();
    if (test == NULL) {
        printf ("No config found\n");
    }

    //bt_a2dp_init();
}
