#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "simple_io.h"

#define RGB_LED_RED_PIN 4
#define RGB_LED_GREEN_PIN 5
#define RGB_LED_BLUE_PIN 6

#define RGB_LED_RED_CHANNEL LEDC_CHANNEL_0
#define RGB_LED_GREEN_CHANNEL LEDC_CHANNEL_1
#define RGB_LED_BLUE_CHANNEL LEDC_CHANNEL_2

static int32_t color_array[55] = {
    BLACK,
    WHITE,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    MAGENTA,
    CYAN,
    GRAY,
    SILVER,
    MAROON,
    OLIVE,
    DARKGREEN,
    NAVY,
    PURPLE,
    TEAL,
    INDIGO,
    BROWN,
    CORAL,
    CRIMSON,
    DARKBLUE,
    DARKGRAY,
    DARKKHAKI,
    DARKMAGENTA,
    DARKOLIVE,
    DARKORANGE,
    DARKRED,
    DARKSALMON,
    DARKSEAGREEN,
    DARKSLATEBLUE,
    DARKTURQUOISE,
    DEEPPINK,
    FORESTGREEN,
    GOLD,
    GOLDENROD,
    HOTPINK,
    INDIANRED,
    KHAKI,
    LIGHTBLUE,
    LIGHTCORAL,
    LIGHTGRAY,
    LIGHTGREEN,
    LIGHTPINK,
    LIGHTSALMON,
    LIGHTSEAGREEN,
    LIGHTSKYBLUE,
    LIGHTSLATEGRAY,
    LIMEGREEN,
    MEDIUMAQUAMARINE,
    MEDIUMPURPLE,
    MEDIUMSEAGREEN,
    MEDIUMSLATEBLUE,
    MEDIUMSPRINGGREEN,
    MEDIUMTURQUOISE,
    MIDNIGHTBLUE,
};

static ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .timer_num = LEDC_TIMER_0,
    .duty_resolution = LEDC_TIMER_8_BIT,
    .freq_hz = 5000,
    .clk_cfg = LEDC_AUTO_CLK,
};

static ledc_channel_config_t RGB_red_channel_config = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = RGB_LED_RED_CHANNEL,
    .timer_sel = LEDC_TIMER_0,
    .intr_type = LEDC_INTR_DISABLE,
    .gpio_num = RGB_LED_RED_PIN,
    .duty = 0,
    .hpoint = 0,
};

static ledc_channel_config_t RGB_green_channel_config = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = RGB_LED_GREEN_CHANNEL,
    .timer_sel = LEDC_TIMER_0,
    .intr_type = LEDC_INTR_DISABLE,
    .gpio_num = RGB_LED_GREEN_PIN,
    .duty = 0,
    .hpoint = 0,
};

static ledc_channel_config_t RGB_blue_channel_config = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = RGB_LED_BLUE_CHANNEL,
    .timer_sel = LEDC_TIMER_0,
    .intr_type = LEDC_INTR_DISABLE,
    .gpio_num = RGB_LED_BLUE_PIN,
    .duty = 0,
    .hpoint = 0,
};

static esp_err_t config_RGB_LEDC()
{
    esp_err_t error = ESP_OK;

    // Configure timer for LEDC
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_timer_config(&ledc_timer));

    // Configure channels; each channels corresponds to each color led pins.
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_channel_config(&RGB_red_channel_config));
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_channel_config(&RGB_green_channel_config));
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_channel_config(&RGB_blue_channel_config));

    return error;
}

static esp_err_t RGB_LED_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    esp_err_t error = ESP_OK;

    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_set_duty(LEDC_LOW_SPEED_MODE, RGB_LED_RED_CHANNEL, red));
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_set_duty(LEDC_LOW_SPEED_MODE, RGB_LED_GREEN_CHANNEL, green));
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_set_duty(LEDC_LOW_SPEED_MODE, RGB_LED_BLUE_CHANNEL, blue));

    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_update_duty(LEDC_LOW_SPEED_MODE, RGB_LED_RED_CHANNEL));
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_update_duty(LEDC_LOW_SPEED_MODE, RGB_LED_GREEN_CHANNEL));
    ESP_ERROR_CHECK_WITHOUT_ABORT(ledc_update_duty(LEDC_LOW_SPEED_MODE, RGB_LED_BLUE_CHANNEL));

    return error;
}

void app_main()
{
    ESP_LOGI(__FILE__, "ESP RGB controller!!");

    config_RGB_LEDC();

    while (1)
    {
        for (int i = 0; i < 55; i++)
        {
            int32_t full_color = color_array[i];
            uint8_t red_color = (full_color >> 16) & 0xFF;
            uint8_t green_color = (full_color >> 8) & 0xFF;
            uint8_t blue_color = full_color & 0xFF;
            ESP_LOGI(__FILE__, "full color = 0x%X, red = 0x%X, green = 0x%X, blue 0x%X", full_color, red_color, green_color, blue_color);
            RGB_LED_set_color(red_color, green_color, blue_color);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
    }
}
