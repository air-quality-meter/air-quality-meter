/**
 * @file pin_configuration.h
 * @brief This file contains the pin configuration for the Arduino Mega 2560.
 */

#ifndef PIN_CONFIGURATION_H
#define PIN_CONFIGURATION_H

#include <Arduino.h>

// Acknowledge Button
constexpr byte ACKNOWLEDGE_BUTTON_PIN = 2; ///< Interrupt functionality on Pin2 (Int0)

// CO2 Sensor: MH-Z19B Infrared CO2 Sensor Module.
// TODO CO2 Sensor is on Serial1 and probably don't need PIN declaration?

// Display: LCD1602 Module (with pin header)
// TODO declare PINS for the Display (use constexpr int, since this should not change during runtime)

// MP3 Module: Gravity UART MP3 Voice Module
constexpr byte MP3_MODULE_TX_PIN = 14; ///< MP3 Modul Serial Pin T
constexpr byte MP3_MODULE_RX_PIN = 15; ///< MP3 Modul Serial Pin R

// LEDs
constexpr byte GREEN_LED_1_PIN = 22; ///< LED to indicate high air quality on Pin 22
constexpr byte GREEN_LED_2_PIN = 24; ///< LED to indicate high or medium air quality on Pin 24
constexpr byte YELLOW_LED_1_PIN = 26; ///< LED to indicate medium or moderate air quality on Pin 26
constexpr byte YELLOW_LED_2_PIN = 28; ///< LED to indicate moderate air quality on Pin 28
constexpr byte RED_LED_1_PIN = 30; ///< LED to indicate moderate or poor air quality on Pin 30
constexpr byte RED_LED_2_PIN = 32; ///< LED to indicate poor air quality on Pin 32

#endif //PIN_CONFIGURATION_H