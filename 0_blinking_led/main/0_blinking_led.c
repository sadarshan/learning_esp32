/*
 * Filename: 0_blinking_led.c
 * Author: Darshan Savaliya github@sadarshan
 * Date: 16 Oct 2025
 * Purpose: blink an LED(connected to GPIO 2 pin) with an interval of 1s
 * Board: ESP32-C6
 */


#include <stdio.h>             // standard input output header to print anything 
#include "freertos/FreeRTOS.h" // this header is needed to use app_main() as app_main is a standart function to use when running freertos on esp32
#include "freertos/task.h"     // header needed to use __LINE__ and portTICK_PERIOD_MS
#include "driver/gpio.h"       // header needed to interface with ESP32 GPIO pins
#include "esp_log.h"           // header needed to use any macro and functions related to esp logging


static const char *ERROR_TAG = "blinking_led_app";


void app_main(void)
{
    esp_err_t return_check; // this is optional, however if any error occurs, better to catch and display error code on UART terminal
    return_check = gpio_reset_pin(GPIO_NUM_2);  
    /* gpio_reset_pin() function declaration is present in esp-idf/components/esp_driver_gpio/include/driver/gpio.h 
    and function definition in esp-idf/components/esp_driver_gpio/src/gpio.c file
    */

    // print log with function name and line number with error code
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error resetting GPIO pin at line %d of app_main() error id: %d", __LINE__, return_check);
    }

    // set GPIO pin 2 direction to output to set it for LED pin high and low output
    return_check = gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error setting GPIO pin 2 to output at line %d of app_main() error id: %d", __LINE__, return_check);
    }

    // prepare a while loop that sets the pin to high and low every one second

    while (1) {
        printf("Setting the GPIO pin to High\n");
        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        printf("Setting the GPIO pin to Low\n");
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}