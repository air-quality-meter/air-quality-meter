/**
 * @file pin_configuration.h
 * @brief This file contains the pin configuration for the Arduino Mega 2560.
 */

#ifndef PIN_CONFIGURATION_H
#define PIN_CONFIGURATION_H

// Reset Button
constexpr int TIME_COUNTER_RESET_BUTTON_PIN = 2; ///< Interrupt functionality on Pin2 (Int0)

// LEDs
constexpr int GREEN_LED_1_PIN = 22; ///< LED to indicate high air quality on Pin 22
constexpr int GREEN_LED_2_PIN = 24; ///< LED to indicate high or medium air quality on Pin 24
constexpr int YELLOW_LED_1_PIN = 26; ///< LED to indicate medium or moderate air quality on Pin 26
constexpr int YELLOW_LED_2_PIN = 28; ///< LED to indicate moderate air quality on Pin 28
constexpr int RED_LED_1_PIN = 30; ///< LED to indicate moderate or poor air quality on Pin 30
constexpr int RED_LED_2_PIN = 32; ///< LED to indicate poor air quality on Pin 32

// CO2 Sensor
// TODO CO2 Sensor is on Serial1 and probably don't need PIN declaration?

// Display
// TODO declare PINS for the Display (use constexpr int, since this should not change during runtime)

// MP3 Module
// TODO declare PINS for the MP3 Module (use constexpr int, since this should not change during runtime)

#endif //PIN_CONFIGURATION_H