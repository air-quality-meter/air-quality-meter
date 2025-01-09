
/**
 * @file MuteIndicator.h
 * @brief Header file for the MuteIndicator module.
 *
 * This file contains the declarations for the MuteIndicator module, 
 * which provides functionality to initialize and control an LED 
 * indicating the system's mute state.
 */

#ifndef MUTE_INDICATOR_H
#define MUTE_INDICATOR_H

namespace MuteIndicator {
    /**
     * @brief   Initializes the MuteIndicator module for operation.
     *
     * @details This function configures the necessary hardware by setting up the required pins
     *          as output to enable mute indication functionality. It prepares the mute indicator
     *          to reflect the system's mute status.
     */
    void initialize();

    /**
     * @brief   Updates the visual indicator to reflect the system's mute state.
     *
     * @details This function controls the LED responsible for indicating
     *          whether the system is muted or unmuted by toggling the LED on or off.
     *
     * @param is_mute Indicates whether the system is muted (`true` for muted, `false` for unmuted).
     */
    void indicate_system_mute(bool is_mute);
}

#endif //MUTE_INDICATOR_H
