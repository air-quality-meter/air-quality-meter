/**
 * @file    system_manager.h
 * @brief   This file contains the function declarations for system management functions.
 */

#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

/**
 * @brief   Resets last_co2_below_threshold_time_s and warning_counter.
 * @details Resets the timestamp of the last CO2 measurement that was below the threshold
 *          and the counter for consecutive warnings.
 */
void reset_co2_below_threshold_and_warning_counter();

/**
 * @brief   Retrieves the elapsed time since the board was powered on.
 * @details Converts the internal millis() value from milliseconds to seconds to provide a time reference.
 * @return  The elapsed time since the board was powered on in seconds.
 */
unsigned long get_current_time_in_s();

#endif //SYSTEM_MANAGER_H
