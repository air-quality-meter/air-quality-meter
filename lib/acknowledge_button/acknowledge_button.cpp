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
#include <led_patterns.h>
#include <not_blocking_time_handler.h>
#include <led_array.h>
#include "../log_controller/log_controller.h"

namespace AcknowledgeButton {
    constexpr unsigned long INDICATION_SEQUENCE_DELAY_MS = 100UL;

    /**
     * @brief   Indicates acknowledgment through LED pattern.
     * @details This function outputs a predefined LED indication sequence
     *          to acknowledge the warning. It utilizes a non-blocking delay
     *          between the LED outputs to ensure a fluid sequence pattern.
     */
    void indicate_acknowledge();

    void initialize() {
        pinMode(DIGITAL_PIN, INPUT);
        attachInterrupt(
            digitalPinToInterrupt(DIGITAL_PIN),
            acknowledge_warning, RISING);
    }

    void acknowledge_warning() {
        Log.infoln(LogController::ACKNOWLEDGE_BUTTON_PRESSED);
        static unsigned long last_button_press_detected_ms = 0UL;
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

        indicate_acknowledge();

        Log.verboseln(LogController::STATE_UPDATED);
        LogController::log_current_state();

    }

    void indicate_acknowledge() {
        for (const auto i: LedInfoPattern::INFO_PATTERN_SEQUENCE) {
            LedArray::output(i);
            NotBlockingTimeHandler::wait_ms(INDICATION_SEQUENCE_DELAY_MS);
        }
    }
}
