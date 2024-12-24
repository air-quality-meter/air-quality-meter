/**
 * @file    acknowledge_button.cpp
 * @brief   This file contains the functions for the acknowledge button.
 */

#include <Arduino.h>
#include <acknowledge_button.h>
#include <system_state.h>
#include <../time_controller/time_controller.h>
#include <pin_configuration.h>

namespace AcknowledgeButton {
    constexpr unsigned long DEBOUNCE_DELAY_MS = 1000; ///< Time between two interrupts to debounce.

    void initialize() {
        pinMode(DIGITAL_PIN, INPUT);
        attachInterrupt(
            digitalPinToInterrupt(DIGITAL_PIN),
            acknowledge_warning, RISING);
    }

    void acknowledge_warning() {
        // Debounce: If elapsed time since last interrupt is less than debounce time, ignore this and return
        const unsigned long interrupt_time_ms = millis(); ///< timestamp in milliseconds
        if (interrupt_time_ms - system_state.last_interrupt_time_ms < DEBOUNCE_DELAY_MS) {
            return;
        }
        noInterrupts(); // Temporarily disable interrupts while updating system state
        system_state.last_co2_below_threshold_time_s = TimeController::get_timestamp_s();
        system_state.warning_counter = 0;
        system_state.last_interrupt_time_ms = interrupt_time_ms; // Save the time of this interrupt for debouncing logic
        interrupts(); // Re-enable interrupts
    }
}