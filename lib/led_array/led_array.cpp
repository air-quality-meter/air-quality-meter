/**
 * @file    led_array.cpp
 * @brief   This file contains the function definitions for controlling the LEDs.
 */

#include <Arduino.h>
#include <led_array.h>
#include <led_pattern.h>
#include <pin_configuration.h>

namespace LedArray {
    void initialize() {
        pinMode(GREEN_1_PIN, OUTPUT);
        pinMode(GREEN_2_PIN, OUTPUT);
        pinMode(YELLOW_1_PIN, OUTPUT);
        pinMode(YELLOW_2_PIN, OUTPUT);
        pinMode(RED_1_PIN, OUTPUT);
        pinMode(RED_2_PIN, OUTPUT);
    }

    void output(const LedPattern::Pattern pattern) {
        digitalWrite(GREEN_1_PIN, pattern.is_green_led_1_on);
        digitalWrite(GREEN_2_PIN, pattern.is_green_led_2_on);
        digitalWrite(YELLOW_1_PIN, pattern.is_yellow_led_1_on);
        digitalWrite(YELLOW_2_PIN, pattern.is_yellow_led_2_on);
        digitalWrite(RED_1_PIN, pattern.is_red_led_1_on);
        digitalWrite(RED_2_PIN, pattern.is_red_led_2_on);
    }
}
