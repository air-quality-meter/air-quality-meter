/**
 * @file    acknowledge_button.cpp
 * @brief   This file contains the functions for the acknowledge button.
 */

#include <Arduino.h>
#include <acknowledge_button.h>
#include <button_debouncer.h>
#include <ArduinoLog.h>
#include <state.h>
#include <pin_configuration.h>
#include "../log_controller/log_controller.h"

namespace AcknowledgeButton {

    void initialize() {
        pinMode(DIGITAL_PIN, INPUT);
        attachInterrupt(
            digitalPinToInterrupt(DIGITAL_PIN),
            acknowledge_warning, RISING);
    }

    void acknowledge_warning() {
        Log.infoln(LogController::ACKNOWLEDGE_BUTTON_PRESSED);
        static unsigned long last_button_press_detected_ms = 0;
        ///< Timestamp of last interrupt initialized with static to persist until next function call.
        TRACE_LN_u(last_button_press_detected_ms);
        if (!ButtonDebouncer::is_button_debounced(last_button_press_detected_ms)) {
            Log.verboseln(LogController::ACKNOWLEDGE_BUTTON_DEBOUNCED);
            return;
        }

        noInterrupts(); // Temporarily disable interrupts while updating system state
        AirQualityMeter::state.last_co2_below_threshold_time_ms = millis();
        AirQualityMeter::state.warning_counter = 0;
        interrupts(); // Re-enable interrupts

        Log.verboseln(LogController::STATE_UPDATED);
        LogController::log_current_state();
    }
}
