#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "nvs_controller.h"
#include <string.h>

nvs_handle *init_nvs() {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
        return NULL;
    }
    ESP_ERROR_CHECK( err );

    // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    nvs_handle *my_handle;
    my_handle = (nvs_handle*) malloc (sizeof(nvs_handle));
    err = nvs_open("storage", NVS_READWRITE, my_handle);
    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
        return NULL;
    }
    return my_handle;
}

char *read_device_name() {
    nvs_handle *my_handle = init_nvs();
    esp_err_t err = ESP_OK;
    char *device_name = NULL;
    const char *bt_device_key = "bt_device_name";
    if (my_handle != NULL) {
        // Read
        int32_t len = 0; // value will default to 0, if not set yet in NVS
        err = nvs_get_i32(*my_handle, "strlen", &len);
        switch (err) {
            case ESP_OK:
                printf("Done\n");
                printf("Restart counter = %d\n", len);
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The value is not initialized yet!\n");
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
        }
        if (len > 0) {
            printf("Reading restart counter from NVS ... ");
            size_t max_size = len;
            err = nvs_get_str(*my_handle, bt_device_key, device_name, &max_size);
            switch (err) {
                case ESP_OK:
                    printf("Done\n");
                    printf("bt_device_name read = %s\n", device_name);
                    break;
                case ESP_ERR_NVS_NOT_FOUND:
                    printf("The value is not initialized yet!\n");
                    break;
                default :
                    printf("Error (%s) reading!\n", esp_err_to_name(err));
            }
        }
        nvs_close(*my_handle);
    }
    return device_name;
}

void write_device_name(const char *device_name) {
    nvs_handle *my_handle = init_nvs();
    if (my_handle != NULL) {
        esp_err_t err = ESP_OK;
        err = nvs_set_i32(*my_handle, "strlen", strlen(device_name));
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        printf("%d\n", strlen(device_name));
        err = nvs_set_str(*my_handle, "bt_device_name", device_name);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

        printf("Committing updates in NVS ... ");
        err = nvs_commit(*my_handle);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

        // Close
        nvs_close(*my_handle);
    }
}

void clear_device_name() {
    printf("%s: enter\n", __func__);
    //nvs_handle *my_handle = init_nvs();
    write_device_name("");
}