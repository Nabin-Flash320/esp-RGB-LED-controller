

#include "simple_io.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

esp_err_t configure_RGB_LED(pins_t* led_pins)
{
    esp_err_t error = ESP_OK;

    gpio_config_t RGB_red_config = {
        .pin_bit_mask = (1ULL << led_pins->red_pin),
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };

    gpio_config_t RGB_green_config = {
        .pin_bit_mask = (1ULL << led_pins->green_pin),
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };

    gpio_config_t RGB_blue_config = {
        .pin_bit_mask = (1ULL << led_pins->blue_pin),
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };

    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&RGB_red_config));
    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&RGB_green_config));
    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&RGB_blue_config));

    return error;
}


void run_loop(pins_t* led_pins)
{
    while (1)
    {
        gpio_set_level(led_pins->red_pin, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(led_pins->red_pin, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        gpio_set_level(led_pins->green_pin, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(led_pins->green_pin, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        gpio_set_level(led_pins->blue_pin, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(led_pins->blue_pin, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void set_pin_level(uint32_t pin, uint32_t level)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_set_level(pin, level));
}
