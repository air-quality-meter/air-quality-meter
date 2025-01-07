/**
 * @file pin_configuration.h
 * @brief This file contains the pin configuration for the Arduino Mega 2560.
 */

#ifndef PIN_CONFIGURATION_H
#define PIN_CONFIGURATION_H

#include <Arduino.h>

namespace AcknowledgeButton {
    // Pin configuration for the Acknowledge Button
    constexpr uint8_t DIGITAL_PIN = 2; ///< Interrupt functionality (Int0)
}

namespace MuteButton {
    constexpr uint8_t DIGITAL_PIN = 3; ///< Interrupt functionality (Int1)
}

namespace Co2SensorController {
    // Pin configuration for the CO2 Sensor: MH-Z19B Infrared CO2 Sensor Module.
    constexpr uint8_t PWM_PIN = 4; ///< PWM pin for CO2 sensor
}

namespace DisplayController {
    // Pin configuration for the Display: LCD1602 Module (with pin header)
    constexpr uint8_t RS_PIN = 7; ///< LCD Register Select pin
    constexpr uint8_t EN_PIN = 8; ///< LCD Enable pin
    constexpr uint8_t D4_PIN = 9; ///< LCD Data pin 4
    constexpr uint8_t D5_PIN = 10; ///< LCD Data pin 5
    constexpr uint8_t D6_PIN = 11; ///< LCD Data pin 6
    constexpr uint8_t D7_PIN = 12; ///< LCD Data pin 7
}


namespace AudioController {
    // Pin configuration for the MP3 Module: Gravity UART MP3 Voice Module
    constexpr uint8_t TX_PIN = 14; ///< MP3 Modul Serial Pin T
    constexpr uint8_t RX_PIN = 15; ///< MP3 Modul Serial Pin R
}

namespace LedArray {
    // Pin configuration for the LEDs
    constexpr uint8_t GREEN_1_PIN = 22; ///< LED to indicate high air quality
    constexpr uint8_t GREEN_2_PIN = 24; ///< LED to indicate high or medium air quality
    constexpr uint8_t YELLOW_1_PIN = 26; ///< LED to indicate medium or moderate air quality
    constexpr uint8_t YELLOW_2_PIN = 28; ///< LED to indicate moderate air quality
    constexpr uint8_t RED_1_PIN = 30; ///< LED to indicate moderate or poor air quality
    constexpr uint8_t RED_2_PIN = 32; ///< LED to indicate poor air quality
}

namespace MuteIndicator {
    // Pin configuration for the Mute indicator LED
    constexpr uint8_t BLUE_PIN = 34; ///< LED to indicate the System is muted
}

#endif //PIN_CONFIGURATION_H
