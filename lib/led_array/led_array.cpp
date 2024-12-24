/**
 * @file    led_array.cpp
 * @brief   This file contains the function definitions for controlling the LEDs.
 */

#include <Arduino.h>
#include <led_array.h>
#include <pin_configuration.h>

namespace LedArray {
    void initialize() {
        pinMode(GREEN_1_PIN, OUTPUT); ///< LED for high air quality
        pinMode(GREEN_2_PIN, OUTPUT); ///< LED for high or medium air quality
        pinMode(YELLOW_1_PIN, OUTPUT); ///< LED for medium or moderate air quality
        pinMode(YELLOW_2_PIN, OUTPUT); ///< LED for moderate air quality
        pinMode(RED_1_PIN, OUTPUT); ///< LED for moderate or poor air quality
        pinMode(RED_2_PIN, OUTPUT); ///< LED for poor air quality
    }

    void output(const bool is_green_led_1_on,
                const bool is_green_led_2_on,
                const bool is_yellow_led_1_on,
                const bool is_yellow_led_2_on,
                const bool is_red_led_1_on,
                const bool is_red_led_2_on) {
        digitalWrite(GREEN_1_PIN, is_green_led_1_on);
        digitalWrite(GREEN_2_PIN, is_green_led_2_on);
        digitalWrite(YELLOW_1_PIN, is_yellow_led_1_on);
        digitalWrite(YELLOW_2_PIN, is_yellow_led_2_on);
        digitalWrite(RED_1_PIN, is_red_led_1_on);
        digitalWrite(RED_2_PIN, is_red_led_2_on);
    }
}
