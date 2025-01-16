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
        // default volume configuration for the module.
        constexpr uint8_t DEFAULT_VOLUME = 0x1E; ///< Default volume level (30)
        constexpr uint8_t SET_VOLUME_COMMAND_SIZE = 5; ///< Size of the volume command array
        constexpr uint8_t SET_DEFAULT_VOLUME[SET_VOLUME_COMMAND_SIZE] = {
            0xAA, 0x13, 0x01, DEFAULT_VOLUME, DEFAULT_VOLUME + 0xBE
        };
        ///< Command array to set the default volume.
    }

    namespace Play {
        // Command specifications for playing tracks.
        constexpr uint8_t PLAY_TRACK_COMMAND_SIZE = 6; ///< Size of the play command array
        constexpr uint8_t PLAY_TRACK_1[PLAY_TRACK_COMMAND_SIZE] = {
            0xAA, 0x07, 0x02, 0x00, WARNING_1_TRACK, WARNING_1_TRACK + 0xB3
        };
        ///< Command array to play the first warning track.
    }

    SoftwareSerial mp3_module(MP3_T, MP3_R);
    ///< Connection instance for MP3 module communication.
    ///< MP3 T (Transmit) to Arduino SoftwareSerial Receive.
    ///< MP3 R (Receive) to Arduino SoftwareSerial Transmit.

    void initialize() {
        mp3_module.begin(BAUD_RATE);
        mp3_module.write(Volume::SET_DEFAULT_VOLUME, Volume::SET_VOLUME_COMMAND_SIZE);
    }

    void issue_warning() {
        mp3_module.write(Play::PLAY_TRACK_1, Play::PLAY_TRACK_COMMAND_SIZE);
    }
}
