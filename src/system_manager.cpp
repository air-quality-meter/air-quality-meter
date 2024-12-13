#include <Arduino.h>

/**
 * @file    system_manager.cpp
 * @brief   This file contains the function definitions for system management functions.
 */

#include "system_manager.h"
#include "global_variables.h"

void reset_co2_below_threshold_and_warning_counter() {
    last_co2_below_threshold_time_s = current_time_s;
    warning_counter = 0;
}

unsigned long get_current_time_in_s() {
    const unsigned long time_since_board_on_ms = millis(); ///< timestamp in milliseconds
    const unsigned long time_since_board_on_s = time_since_board_on_ms / 1000; ///< timestamp in seconds
    return time_since_board_on_s;
}