#include <Arduino.h>

/**
 * @file    system_manager.cpp
 * @brief   This file contains the function definitions for system management functions.
 */

#include "system_manager.h"
#include "system_state.h"
#include "pin_configuration.h"

constexpr unsigned long DEBOUNCE_DELAY_MS = 1000; ///< Time between two interrupts to debounce.

void initialize_reset_button() {
    attachInterrupt(TIME_COUNTER_RESET_BUTTON_PIN, reset_co2_below_threshold_and_warning_counter,FALLING);
}

void reset_co2_below_threshold_and_warning_counter() {
    // Debounce: If elapsed time since last interrupt is less than debounce time, ignore this and return
    const unsigned long interrupt_time_ms = millis(); ///< timestamp in milliseconds
    if (interrupt_time_ms - system_state.last_interrupt_time_ms < DEBOUNCE_DELAY_MS) {
        return;
    }
    system_state.last_co2_below_threshold_time_s = get_current_time_in_s();
    system_state.warning_counter = 0;
}

unsigned long get_current_time_in_s() {
    const unsigned long time_since_board_on_ms = millis(); ///< timestamp in milliseconds
    const unsigned long time_since_board_on_s = time_since_board_on_ms / 1000; ///< timestamp in seconds
    return time_since_board_on_s;
}