/**
 * @file    audio_controller.cpp
 * @brief   This file contains the function definitions for the audio warning system.
 */

#include <audio_controller.h>
#include <pin_configuration.h>
#include <SoftwareSerial.h>

namespace AudioController {
    constexpr long BAUD_RATE = 9600; // speed for serial port in bits per second (baud)
    constexpr uint8_t WARNING_1_TRACK = 0x01; ///< Track: "CO2 Wert zu hoch, bitte Fenster öffnen!"
    constexpr uint8_t WARNING_2_TRACK = 0x03; ///< Track: "Die Luftqualität ist schlecht, bitte Fenster öffnen!"
    namespace Volume {
        constexpr uint8_t DEFAULT_VOLUME = 0x1E;
        constexpr uint8_t COMMAND_SIZE = 5;
        constexpr uint8_t COMMAND[COMMAND_SIZE] = {0xAA,0x13,0x01,DEFAULT_VOLUME,DEFAULT_VOLUME+0xBE};
    }
    namespace Play {
        constexpr uint8_t COMMAND_SIZE = 6;
        constexpr uint8_t COMMAND[COMMAND_SIZE] = {0xAA,0x07,0x02,0x00,WARNING_1_TRACK,WARNING_1_TRACK+0xB3};
    }

    SoftwareSerial mp3_module(TX_PIN, RX_PIN);

    //void setup() {
    void initialize() {
        mp3_module.begin(BAUD_RATE);
        mp3_module.write(Volume::COMMAND,Volume::COMMAND_SIZE);
    }

    void issue_warning() {
        mp3_module.write(Play::COMMAND,Play::COMMAND_SIZE);
    }
}