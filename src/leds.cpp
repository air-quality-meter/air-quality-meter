#include <Arduino.h>
/**
 * @file    leds.cpp
 * @brief   This file contains the function definitions for controlling the LEDs.
 */

#include "leds.h"
#include "pin_configuration.h"


void set_leds(const bool is_green_led_1_on,
              const bool is_green_led_2_on,
              const bool is_yellow_led_1_on,
              const bool is_yellow_led_2_on,
              const bool is_red_led_1_on,
              const bool is_red_led_2_on) {
    digitalWrite(GREEN_LED_1_PIN, is_green_led_1_on);
    digitalWrite(GREEN_LED_2_PIN, is_green_led_2_on);
    digitalWrite(YELLOW_LED_1_PIN, is_yellow_led_1_on);
    digitalWrite(YELLOW_LED_2_PIN, is_yellow_led_2_on);
    digitalWrite(RED_LED_1_PIN, is_red_led_1_on);
    digitalWrite(RED_LED_2_PIN, is_red_led_2_on);
};
