/*
 * Filename: 4_intro_to_rotary_encoder.c
 * Author: Darshan Savaliya github@sadarshan
 * Date: 19 Oct 2025
 * Purpose: read and print HW-040 rotary encoder clockwise and counter-clockwise signals as well as the button
 * connection: push button connected to GPIO 8 pin
 *             VCC connected to 3V3
 *             GND connected to GND
 *             rotary encoder CLK or A pin connected to GPIO 10 
 *             rotary encoder DT or B pin connected to GPIO 11
 * Board: ESP32-C6
 */


#include <stdio.h>             // standard input output header to print anything 
#include "freertos/FreeRTOS.h" // this header is needed to use app_main() as app_main is a standart function to use when running freertos on esp32
#include "freertos/task.h"     // header needed to use __LINE__ and portTICK_PERIOD_MS
#include "driver/gpio.h"       // header needed to interface with ESP32 GPIO pins
#include "esp_err.h"           // header needed to use any macro and functions related to esp errors
#include "esp_log.h"           // header needed to use any macro and functions related to esp logging

static const char *ERROR_TAG = "intro_to_rotary_encoder_app";
volatile unsigned int button_push_count = 0; // variable to count button push
volatile unsigned int encoder_counter = 0; // variable to count encoder push

void ISR_handler_for_gpio8(void *arg); // function prototype for ISR
void ISR_handler_for_gpio10(void *arg); // function prototype for ISR

void app_main(void)
{
    esp_err_t return_check;
    int previous_encoder_counter = 0;


    return_check = gpio_reset_pin(GPIO_NUM_10);  
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error resetting GPIO pin 10 at line %d of app_main() error id: %d", __LINE__, return_check);
    }
    return_check = gpio_reset_pin(GPIO_NUM_8);  
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error resetting GPIO pin 8 at line %d of app_main() error id: %d", __LINE__, return_check);
    }
    return_check = gpio_reset_pin(GPIO_NUM_11);  
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error resetting GPIO pin 11 at line %d of app_main() error id: %d", __LINE__, return_check);
    }

    gpio_config_t io_conf = {0};
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_8);   // Configure GPIO8
    io_conf.mode = GPIO_MODE_INPUT;                // Set as input
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;       // Enable internal pull-up
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;  // Disable pull-down
    io_conf.intr_type = GPIO_INTR_POSEDGE;         // Set interrupt type to positive edge

    return_check = gpio_config(&io_conf);
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error configuring GPIO 8 at line %d of app_main() error id: %d", __LINE__, return_check);
    }

    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_10);   // Configure GPIO11
    io_conf.intr_type = GPIO_INTR_ANYEDGE;         // Set interrupt type to any edge

    return_check = gpio_config(&io_conf);
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error configuring GPIO 10 at line %d of app_main() error id: %d", __LINE__, return_check);
    }
    return_check = gpio_set_direction(GPIO_NUM_11, GPIO_MODE_INPUT);
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error setting GPIO pin 11 to input at line %d of app_main() error id: %d", __LINE__, return_check);
    }
    return_check = gpio_pullup_en(GPIO_NUM_11);
    if (return_check!=ESP_OK) {
        ESP_LOGI(ERROR_TAG, "Error pulling up GPIO pin 11 at line %d of app_main() error id: %d", __LINE__, return_check);
    }
    
    // assign ISR to GPIO pin 8
    gpio_install_isr_service(0); // install ISR service for all GPIO pins and use default config
    gpio_isr_handler_add(GPIO_NUM_8, ISR_handler_for_gpio8, (void *) GPIO_NUM_8); // add ISR handler for GPIO pin 8; (void *) GPIO_NUM_8 is optional
    gpio_isr_handler_add(GPIO_NUM_10, ISR_handler_for_gpio10, (void *) GPIO_NUM_10); // add ISR handler for GPIO pin 10; (void *) GPIO_NUM_10 is optional
    
    int loop_value = 0; // variable to count loop
    int button_loop_print_count = 0; // variable to count button push
    int encoder_loop_print_count = 0; // variable to count encoder pin state change

    while (1) {
        loop_value++;
        // printf("Reading the button state and encoder pins A and B: Loop value: %d button push count: %d\n", loop_value, button_push_count);
        if (button_push_count > 0) {
            printf("----------\n");
            printf("Button is pressed; toggling LED state. Button print count: %d\n", button_loop_print_count);
            button_loop_print_count++;
            button_push_count = 0; // reset button push count to 0
            vTaskDelay(50/portTICK_PERIOD_MS); // delay to debounce button
        }

        if (encoder_counter > previous_encoder_counter) {
            printf("----------\n");
            printf("Encoder clockwise rotation detected. Encoder counter: %d\n", encoder_counter);
            previous_encoder_counter = encoder_counter;
        }
        else if (encoder_counter < previous_encoder_counter) {
            printf("----------\n");
            printf("Encoder anti-clockwise rotation detected. Encoder counter: %d\n", encoder_counter);
            previous_encoder_counter = encoder_counter;
        }
        vTaskDelay(100/portTICK_PERIOD_MS); // delay to avoid over-running
    }
}

void ISR_handler_for_gpio8(void *arg)
{
    button_push_count++;
}

void ISR_handler_for_gpio10(void *arg)
{
    if (gpio_get_level(GPIO_NUM_10) == 0 && gpio_get_level(GPIO_NUM_11) == 0) {
        encoder_counter--;
    } else if (gpio_get_level(GPIO_NUM_10) == 1 && gpio_get_level(GPIO_NUM_11) == 1) {
        encoder_counter--;
    } else if (gpio_get_level(GPIO_NUM_10) == 0 && gpio_get_level(GPIO_NUM_11) == 1) {
        encoder_counter++;
    } else if (gpio_get_level(GPIO_NUM_10) == 1 && gpio_get_level(GPIO_NUM_11) == 0) {
        encoder_counter++;
    }
}

