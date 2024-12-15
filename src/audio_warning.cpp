#include <Arduino.h>

/**
 * @file    audio_warning.cpp
 * @brief   This file contains the function definitions for the audio warning system.
 */

#include "audio_warning.h"
#include "pin_configuration.h"

void initialize_mp3_module() {
    Serial3.begin(9600);
    ///< Initialize Serial communication on Serial3 (PINs 14 and 15) for Gravity UART MP3 Voice Module with baud rate 9600.
    //TODO: This function needs to be finalized. (all the stuff, that should run on device startup)
}


void issue_audio_warning() {
    //TODO: This function needs to be written. (all the stuff that runs on every loop iteration)
}
