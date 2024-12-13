/**
 * @file pin_configuration.h
 * @brief This file contains the pin configuration for the Arduino Mega 2560.
 */

#ifndef PIN_CONFIGURATION_H
#define PIN_CONFIGURATION_H

// Pins
#define TIME_COUNTER_RESET_BUTTON_PIN 2 ///< Interrupt functionality on Pin2 (Int0)
#define GREEN_LED_1_PIN 22 ///< LED to indicate high air quality on Pin 22
#define GREEN_LED_2_PIN 24 ///< LED to indicate high or medium air quality on Pin 24
#define YELLOW_LED_1_PIN 26 ///< LED to indicate medium or moderate air quality on Pin 26
#define YELLOW_LED_2_PIN 28 ///< LED to indicate moderate air quality on Pin 28
#define RED_LED_1_PIN 30 ///< LED to indicate moderate or poor air quality on Pin 30
#define RED_LED_2_PIN 32 ///< LED to indicate poor air quality on Pin 32

#endif //PIN_CONFIGURATION_H