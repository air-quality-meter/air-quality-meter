/**
 * @file    audio_controller.h
 * @brief   Function declarations for the audio warning system.
 * @details Contains declarations related to the initialization and operation of the
 *          Gravity UART MP3 Voice Module used for providing audio warnings.
 */

#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H

namespace AudioController {
     /**
     * @brief   Initializes the Gravity UART MP3 Voice Module.
     * @details Prepares Serial3 for communication, configures the default volume, and ensures
     *          the module is ready for playback commands.
     */
    void initialize();

    /**
     * @brief   Issues an audio warning.
     * @details Plays a prerecorded voice message that calls for the room to be ventilated (output of an MP3 track).
     *          MP3 module used: Gravity UART MP3 Voice Module
     *          Speaker used: Stereo Enclosed Speaker - 3W 8Ω
     */
    void issue_warning();
}

#endif //AUDIO_CONTROLLER_H