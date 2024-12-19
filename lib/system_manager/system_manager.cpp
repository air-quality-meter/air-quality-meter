#include <Arduino.h>

/**
 * @file    system_manager.cpp
 * @brief   This file contains the function definitions for system management functions.
 */

#include "system_manager.h"
#include "system_state.h"
#include "pin_configuration.h"

void initialize_reset_button() {
    attachInterrupt(TIME_COUNTER_RESET_BUTTON_PIN, reset_co2_below_threshold_and_warning_counter,FALLING);
}

void reset_co2_below_threshold_and_warning_counter() {
    //TODO: debounce reset button.
    system_state.last_co2_below_threshold_time_s = get_current_time_in_s();
    system_state.warning_counter = 0;
}

unsigned long get_current_time_in_s() {
    const unsigned long time_since_board_on_ms = millis(); ///< timestamp in milliseconds
    const unsigned long time_since_board_on_s = time_since_board_on_ms / 1000; ///< timestamp in seconds
    return time_since_board_on_s;
}