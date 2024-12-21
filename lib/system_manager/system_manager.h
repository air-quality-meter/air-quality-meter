/**
 * @file    system_manager.h
 * @brief   This file contains the function declarations for system management functions.
 */

#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

/**
 * @brief   Initializes acknowledge button.
 * @details Initializes interrupt service routine for acknowledge button pin.
 *          Device reacts on pressing acknowledge button (rising).
 */
void acknowledge_button();

/**
 * @brief   Resets last_co2_below_threshold_time_s and warning_counter.
 * @details Resets the timestamp of the last CO2 measurement that was below the threshold
 *          and the counter for consecutive warnings.
 */
void acknowledge_warning();


#endif //SYSTEM_MANAGER_H
