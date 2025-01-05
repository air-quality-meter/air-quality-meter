/**
 * @file warning_controller.h
 * @brief Header file for the WarningController namespace.
 *
 * This file provides declarations for functionalities to manage warning mechanisms
 * triggered by CO2 threshold exceedance. It defines the interfaces required for
 * implementing warning control logic, including audio alerts and state resets.
 */

#ifndef WARNING_CONTROLLER_H
#define WARNING_CONTROLLER_H

namespace WarningController {
    /**
     * @brief Determines if an audio warning should be issued.
     *
     * @details This function evaluates whether an audio alert is necessary
     * based on the time elapsed since CO2 levels have been unacceptable.
     *
     * @param time_since_co2_level_not_acceptable_s Time in seconds that CO2
     *                                              levels have been above the
     *                                              acceptable threshold.
     * @return `true` if an audio warning should be issued, `false` otherwise.
     */
    bool is_audio_warning_to_be_issued(unsigned long time_since_co2_level_not_acceptable_s);

    /**
     * @brief Resets the audio warning state variables.
     * @details Sets the CO2 threshold timestamp to the current time and resets the warning counter to zero.
     * This halts any ongoing warnings and starts over.
     *
     * @param current_time_s Current time in seconds (used to update the warning state).
     */
    void reset(unsigned long current_time_s);

    /**
     * @brief Updates the warning state for unacceptable CO2 levels.
     * @details Increments the warning counter and ensures a minimum waiting period between audio warnings.
     * If the number of warnings reaches the maximum consecutive limit, the warning state is reset.
     *
     * @param current_time_s Current time in seconds (used for timing warnings and resets).
     */
    void update_for_co2_level_not_acceptable(unsigned long current_time_s);
}

#endif //WARNING_CONTROLLER_H
