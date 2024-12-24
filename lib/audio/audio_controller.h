/**
 * @file    audio_controller.h
 * @brief   This file contains the function declarations for the audio warning system.
 */

#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H

namespace AudioController {
    /**
     * @brief   Initializes the Gravity UART MP3 Voice Module.
     * @details TODO: Write some more details such as initializes Serial3...
     */
    void initialize();

    /**
     * @brief   Issues an audio warning.
     * @details Voice message that calls for the room to be ventilated (output of an MP3 track).
     *          MP3 module used: Gravity UART MP3 Voice Module
     *          Speaker used: Stereo Enclosed Speaker - 3W 8Ω
     */
    void issue_warning();
}

#endif //AUDIO_CONTROLLER_H