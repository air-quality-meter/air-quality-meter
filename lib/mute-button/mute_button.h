/**
 * @file    mute_button.h
 * @brief   Header file for the mute button functionality.
 */

#ifndef MUTE_BUTTON_H
#define MUTE_BUTTON_H

namespace MuteButton {
    /**
     * @brief    Initializes the mute button functionality.
     * @details  Sets up the required pin mode and interrupt to handle
     *           toggling the mute state when the button is pressed.
     */
    void initialize();

    /**
     * @brief    Toggles the mute state of the system.
     * @details  This function switches the system's mute state
     *           between muted and unmuted when called.
     */
    void toggle_mute_state();
}

#endif //MUTE_BUTTON_H
