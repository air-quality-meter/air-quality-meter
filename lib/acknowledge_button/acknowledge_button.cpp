#include <Arduino.h>

/**
 * @file    acknowledge_button.cpp
 * @brief   This file contains the functions for the acknowledge button.
 */

#include "acknowledge_button.h"
#include "system_state.h"
#include "../system_time/system_time.h"
#include "pin_configuration.h"

constexpr unsigned long DEBOUNCE_DELAY_MS = 1000; ///< Time between two interrupts to debounce.

void initialize_acknowledge_button() {
    pinMode(ACKNOWLEDGE_BUTTON_PIN, INPUT);
    attachInterrupt(
        digitalPinToInterrupt(ACKNOWLEDGE_BUTTON_PIN),
        acknowledge_warning, RISING);
}

void acknowledge_warning() {
    // Debounce: If elapsed time since last interrupt is less than debounce time, ignore this and return
    const unsigned long interrupt_time_ms = millis(); ///< timestamp in milliseconds
    if (interrupt_time_ms - system_state.last_interrupt_time_ms < DEBOUNCE_DELAY_MS) {
        return;
    }
    system_state.last_co2_below_threshold_time_s = get_current_time_in_s();
    system_state.warning_counter = 0;
}
