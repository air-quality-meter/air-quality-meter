/**
 * @file    audio_warning.h
 * @brief   This file contains the function declarations for the audio warning system.
 */

#ifndef AUDIO_WARNING_H
#define AUDIO_WARNING_H

/**
 * @brief   Initializes the MP3 module.
 * @details TODO: Write some more details such as initializes Serial3...
 */
void initialize_mp3_module();

/**
 * @brief   Issues an audio warning.
 * @details Voice message that calls for the room to be ventilated (output of an MP3 track).
 *          MP3 module used: Gravity UART MP3 Voice Module
 *          Speaker used: Stereo Enclosed Speaker - 3W 8Ω
 */
void issue_audio_warning();

#endif //AUDIO_WARNING_H