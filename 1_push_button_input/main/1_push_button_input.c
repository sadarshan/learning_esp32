/*
 * Filename: 1_push_button_input.c
 * Author: Darshan Savaliya github@sadarshan
 * Date: 17 Oct 2025
 * Purpose: read the push button(connected to GPIO 8 pin) and set the LED(connected to GPIO 2 pin) accordingly
 * connection: push button connected to GPIO 8 pin and LED connected to GPIO 2 pin. 
 *             push button is connected to ground and Pin 8
 *             LED is connected to Pin 2 and ground
 * Board: ESP32-C6
 */


#include <stdio.h>             // standard input output header to print anything 
#include "freertos/FreeRTOS.h" // this header is needed to use app_main() as app_main is a standart function to use when running freertos on esp32
#include "freertos/task.h"     // header needed to use __LINE__ and portTICK_PERIOD_MS
#include "driver/gpio.h"       // header needed to interface with ESP32 GPIO pins
#include "esp_err.h"           // header needed to use any macro and functions related to esp errors
#include "esp_log.h"           // header needed to use any macro and functions related to esp logging

static const char *ERROR_TAG = "push_button_input_app";


void app_main(void)
{
    esp_err_t return_check; // this is optional, however if any error occurs, better to catch and display error code on UART terminal
    return_check = gpio_reset_pin(GPIO_NUM_2);  
    /* gpio_reset_pin() function declaration is present in esp-idf/components/esp_driver_gpio/include/driver/gpio.h 
    and function definition in esp-idf/components/esp_driver_gpio/src/gpio.c file
    */

    // print log with function name and line number with error code
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error resetting GPIO pin 2 at line %d of app_main() error id: %d", __LINE__, return_check);
    }
    return_check = gpio_reset_pin(GPIO_NUM_8);  
    /* gpio_reset_pin() function declaration is present in esp-idf/components/esp_driver_gpio/include/driver/gpio.h 
    and function definition in esp-idf/components/esp_driver_gpio/src/gpio.c file
    */

    // print log with function name and line number with error code
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error resetting GPIO pin 8 at line %d of app_main() error id: %d", __LINE__, return_check);
    }

    // set GPIO pin 8 direction to input to set it for push button pin
    return_check = gpio_set_direction(GPIO_NUM_8, GPIO_MODE_INPUT);

    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error setting GPIO pin 8 to input at line %d of app_main() error id: %d", __LINE__, return_check);
    }

    // set GPIO pin 8 pull up mode to set it for push button pin
    // return_check = gpio_set_pull_mode(GPIO_NUM_8, GPIO_PULLUP_ENABLE); this did not work; idk why
    return_check = gpio_pullup_en(GPIO_NUM_8);

    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error pulling up GPIO pin 8 at line %d of app_main() error id: %d", __LINE__, return_check);
    }

    // set GPIO pin 2 direction to output to set it for LED pin high and low output
    return_check = gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error setting GPIO pin 2 to output at line %d of app_main() error id: %d", __LINE__, return_check);
    }
    // prepare a while loop that sets the pin to high and low every one second
    int button_state = 0;
    int loop_value = 0;
    while (1) {
        printf("Reading the button state: Loop value: %d\n", loop_value++);
        button_state = gpio_get_level(GPIO_NUM_8);
        if (button_state==1) {
            printf("Button is released; setting GPIO pin 2 to low\n");
            return_check = gpio_set_level(GPIO_NUM_2, 0);
            if (return_check!=ESP_OK) {
                ESP_LOGI(ERROR_TAG, "Error setting GPIO pin 2 to low at line %d of app_main() error id: %d", __LINE__, return_check);
            }
        } else if (button_state==0) {
            printf("Button is pressed; setting GPIO pin 2 to high\n");
            return_check = gpio_set_level(GPIO_NUM_2, 1);
            if (return_check!=ESP_OK) {
                ESP_LOGI(ERROR_TAG, "Error setting GPIO pin 2 to high at line %d of app_main() error id: %d", __LINE__, return_check);
            }
        }
        else {
            printf("Error reading button state\n");
        }
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}