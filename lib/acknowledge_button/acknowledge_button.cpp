/**
 * @file    acknowledge_button.cpp
 * @brief   This file contains the functions for the acknowledge button.
 */

#include <Arduino.h>
#include <acknowledge_button.h>
#include <ArduinoLog.h>
#include <state.h>
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
        if (interrupt_time_ms - AirQualityMeter::state.last_interrupt_time_ms < DEBOUNCE_DELAY_MS) {
            Log.verbose("Acknowledge button debounced.");
            return;
        }
        Log.info("Acknowledge button pressed.");
        noInterrupts(); // Temporarily disable interrupts while updating system state
        AirQualityMeter::state.last_co2_below_threshold_time_s = TimeController::get_timestamp_s();
        AirQualityMeter::state.warning_counter = 0;
        AirQualityMeter::state.last_interrupt_time_ms = interrupt_time_ms; // Save the time of this interrupt for debouncing logic
        interrupts(); // Re-enable interrupts
        Log.info("State updated.");
    }
}