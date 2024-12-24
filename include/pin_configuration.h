/**
 * @file pin_configuration.h
 * @brief This file contains the pin configuration for the Arduino Mega 2560.
 */

#ifndef PIN_CONFIGURATION_H
#define PIN_CONFIGURATION_H

#include <Arduino.h>

// Acknowledge Button
constexpr byte ACKNOWLEDGE_BUTTON_PIN = 2; ///< Interrupt functionality (Int0)

// CO2 Sensor: MH-Z19B Infrared CO2 Sensor Module.
namespace Co2SensorController {
    // TODO CO2 Sensor is on Serial1 and probably don't need PIN declaration?
}

// Display: LCD1602 Module (with pin header)
namespace DisplayController {
    constexpr byte RS_PIN = 7;  ///< LCD Register Select pin
    constexpr byte EN_PIN = 8;  ///< LCD Enable pin
    constexpr byte D4_PIN = 9;  ///< LCD Data pin 4
    constexpr byte D5_PIN = 10; ///< LCD Data pin 5
    constexpr byte D6_PIN = 11; ///< LCD Data pin 6
    constexpr byte D7_PIN = 12; ///< LCD Data pin 7
}


// MP3 Module: Gravity UART MP3 Voice Module
namespace AudioController {
    constexpr byte TX_PIN = 14; ///< MP3 Modul Serial Pin T
    constexpr byte RX_PIN = 15; ///< MP3 Modul Serial Pin R
}

// LEDs
constexpr byte GREEN_LED_1_PIN = 22; ///< LED to indicate high air quality
constexpr byte GREEN_LED_2_PIN = 24; ///< LED to indicate high or medium air quality
constexpr byte YELLOW_LED_1_PIN = 26; ///< LED to indicate medium or moderate air quality
constexpr byte YELLOW_LED_2_PIN = 28; ///< LED to indicate moderate air quality
constexpr byte RED_LED_1_PIN = 30; ///< LED to indicate moderate or poor air quality
constexpr byte RED_LED_2_PIN = 32; ///< LED to indicate poor air quality

#endif //PIN_CONFIGURATION_H