/**
 * @file    global_constants.h
 * @brief   This file contains the global constants used in the program.
 * @note    Air quality thresholds based on DIN EN 13779.
 * @see     https://www.umweltbundesamt.de/sites/default/files/medien/publikation/long/4113.pdf
 */

#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H

constexpr unsigned int waiting_period_initialization_s = 2000;
///< Wait after initializing the board and all other hardware modules to make sure, they are ready.

constexpr unsigned int waiting_period_loop_iteration_s = 3000;
///< Wait after each loop iteration to prevent overlapping device triggering.


constexpr int max_consecutive_warnings = 5; ///< Max consecutive audio warnings before reset

constexpr unsigned int max_co2_above_threshold_time_s = 3600;
///< Max time period allowed CO2 above threshold (seconds)

constexpr unsigned int waiting_period_between_warnings_s = 60; ///< Time period between two warnings (seconds)

#endif //GLOBAL_CONSTANTS_H
