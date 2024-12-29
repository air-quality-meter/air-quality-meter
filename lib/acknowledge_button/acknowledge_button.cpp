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

#include "../log_controller/log_controller.h"

namespace AcknowledgeButton {
    constexpr unsigned long DEBOUNCE_DELAY_MS = 1000; ///< Time between two interrupts to debounce.

    void initialize() {
        pinMode(DIGITAL_PIN, INPUT);
        attachInterrupt(
            digitalPinToInterrupt(DIGITAL_PIN),
            acknowledge_warning, RISING);
    }

    void acknowledge_warning() {
        Log.infoln(LogController::ACKNOWLEDGE_BUTTON_PRESSED);
        static unsigned long last_interrupt_time_ms = 0;
        ///< Timestamp of last interrupt initialized with static to persist until next function call.
        TRACE_LN_u(last_interrupt_time_ms);
        const unsigned long interrupt_time_ms = millis(); ///< timestamp in milliseconds
        TRACE_LN_u(interrupt_time_ms);
        const unsigned long time_delta_between_interrupt_calls = interrupt_time_ms - last_interrupt_time_ms;
        ///< Time elapsed since last interrupt in milliseconds (handels also potential overflow of millis())
        TRACE_LN_u(time_delta_between_interrupt_calls);
        if (time_delta_between_interrupt_calls < DEBOUNCE_DELAY_MS) {
            // Debounce: If elapsed time since last interrupt is less than debounce time, ignore this and return
            Log.verboseln(LogController::ACKNOWLEDGE_BUTTON_DEBOUNCED);

            return;
        }
        last_interrupt_time_ms = interrupt_time_ms; // updated last interrupt time for debouncing
        TRACE_LN_u(last_interrupt_time_ms);

        noInterrupts(); // Temporarily disable interrupts while updating system state
        AirQualityMeter::state.last_co2_below_threshold_time_s = TimeController::get_timestamp_s();
        AirQualityMeter::state.warning_counter = 0;
        interrupts(); // Re-enable interrupts

        Log.verboseln(LogController::STATE_UPDATED);
        LogController::log_current_state();
    }
}
