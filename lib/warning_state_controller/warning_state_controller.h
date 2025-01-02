/**
 * @file warning_state_controller.h
 * @brief Provides functionality for handling warning states related to CO2 level monitoring.
 * @details This header declares functions for resetting warning states and updating them during unacceptable CO2 levels.
 */

#ifndef WARNING_STATE_CONTROLLER_H
#define WARNING_STATE_CONTROLLER_H

namespace WarningStateController {
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
#endif //WARNING_STATE_CONTROLLER_H
