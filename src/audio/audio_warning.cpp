#include <Arduino.h>

/**
 * @file    audio_warning.cpp
 * @brief   This file contains the function definitions for the audio warning system.
 */

#include "audio_warning.h"
#include "../system/pin_configuration.h"
#include <SoftwareSerial.h>

SoftwareSerial mp3_module(MP3_MODULE_TX_PIN, MP3_MODULE_RX_PIN);

//void setup() {
void initialize_mp3_module() {
    mp3_module.begin(9600);
    const unsigned char vol = 0x1E;
    unsigned char volume[5] = {0xAA,0x13,0x01,vol,vol+0xBE};
    mp3_module.write(volume,5);
}

void issue_audio_warning() {
  	const unsigned char track = 0x01; ///< Track: "CO2 Wert zu hoch, bitte Fenster öffnen!"
    //const unsigned char track = 0x03; ///< Track: "Die Luftqualität ist schlecht, bitte Fenster öffnen!"
    unsigned char play[6] = {0xAA,0x07,0x02,0x00,track,track+0xB3};
    mp3_module.write(play,6);
}