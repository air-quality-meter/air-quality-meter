#include <Arduino.h>

/**
 * @file    audio_warning.cpp
 * @brief   This file contains the function definitions for the audio warning system.
 */

#include "audio_warning.h"
#include "pin_configuration.h"

SoftwareSerial mp3_module(14, 15);

unsigned char order[4] = {0xAA,0x06,0x00,0xB0};

void setup() {
//void initialize_mp3_module() {
    mp3_module.begin(9600);
    volume(0x1E);//Volume settings 0x00-0x1E
    ///< Initialize Serial communication on Serial3 (PINs 14 and 15) for Gravity UART MP3 Voice Module with baud rate 9600.
    //TODO: This function needs to be finalized. (all the stuff, that should run on device startup)
}


//void issue_audio_warning() {
void loop() {
    play(0x01);//Play: "CO2 Wert zu hoch, bitte Fenster öffnen!"
    //play(0x03); //Play: "Die Luftqualität ist schlecht, bitte Fenster öffnen!"
    delay(20000); //Re-plays the same Sound after amount of ms.
}

void play(unsigned char Track)
{
    unsigned char play[6] = {0xAA,0x07,0x02,0x00,Track,Track+0xB3};
    mp3_module.write(play,6);
}
void volume( unsigned char vol)
{
    unsigned char volume[5] = {0xAA,0x13,0x01,vol,vol+0xBE};
    mp3_module.write(volume,5);
    //TODO: This function needs to be written. (all the stuff that runs on every loop iteration)
}
