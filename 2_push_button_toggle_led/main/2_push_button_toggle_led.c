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

static const char *ERROR_TAG = "push_button_toggle_led_app";


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
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error resetting GPIO pin 8 at line %d of app_main() error id: %d", __LINE__, return_check);
    }

    gpio_config_t io_conf = {0};
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_8);   // Configure GPIO8
    io_conf.mode = GPIO_MODE_INPUT;                // Set as input
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;       // Enable internal pull-up
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;  // Disable pull-down
    io_conf.intr_type = GPIO_INTR_DISABLE;         // No interrupt

    return_check = gpio_config(&io_conf);
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error configuring GPIO 8 at line %d of app_main() error id: %d", __LINE__, return_check);
    }

    // set GPIO pin 2 direction to output to set it for LED pin high and low output
    return_check = gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error setting GPIO pin 2 to output at line %d of app_main() error id: %d", __LINE__, return_check);
    }
    // prepare a while loop that sets the pin to high and low every one second
    int previous_button_state = 1, current_button_state = 0;
    bool led_state = false;
    int loop_value = 0;
    while (1) {
        printf("Reading the button state: Loop value: %d\n", loop_value++);
        current_button_state = gpio_get_level(GPIO_NUM_8);
        if ((current_button_state==0 && previous_button_state==1) || (current_button_state==0 && previous_button_state==0)) {
            led_state = !led_state;
            previous_button_state = current_button_state;
            printf("Button is pressed; toggling LED state\n");
            return_check = gpio_set_level(GPIO_NUM_2, led_state);
            if (return_check!=ESP_OK) {
                ESP_LOGI(ERROR_TAG, "Error setting GPIO pin 2 to high at line %d of app_main() error id: %d", __LINE__, return_check);
            }
        }

        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}