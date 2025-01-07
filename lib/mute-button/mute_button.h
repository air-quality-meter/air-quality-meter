/**
 * @file    mute_button.h
 * @brief   Header file for the mute button functionality.
 *
 *          This file contains the declarations for initializing and handling
 *          the mute button functionality, including toggling the mute state
 *          of the system when the button is pressed. It provides functions
 *          to manage debouncing and system state updates.
 */

#ifndef MUTE_BUTTON_H
#define MUTE_BUTTON_H

namespace MuteButton {
    /**
     * @brief    Initializes the mute button functionality.
     *
     * @details  Sets up the required pin mode and interrupt to handle
     *           toggling the mute state when the button is pressed.
     */
    void initialize();

    /**
     * @brief    Toggles the mute state of the system.
     *
     * @details  This function switches the system's mute state 
     *           between muted and unmuted when called.
     *           This includes debouncing the button and calling the mute indicator function to toggle.
     */
    void toggle_mute_state();
}

#endif //MUTE_BUTTON_H
