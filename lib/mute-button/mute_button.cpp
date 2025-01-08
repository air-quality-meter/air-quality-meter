/**
 * @file mute_button.cpp
 * @brief Implementation for the mute button functionality.
 */

#include <Arduino.h>
#include <mute_button.h>
#include <button_debouncer.h>
#include <ArduinoLog.h>
#include <state.h>
#include <pin_configuration.h>
#include <mute_indicator.h>

#include "../log_controller/log_controller.h"

namespace MuteButton {
    void initialize() {
        pinMode(DIGITAL_PIN, INPUT);
        attachInterrupt(
            digitalPinToInterrupt(DIGITAL_PIN),
            toggle_mute_state, RISING);
    }

    void toggle_mute_state() {
        Log.infoln(LogController::MUTE_BUTTON_PRESSED);
        static unsigned long last_interrupt_time_ms = 0;
        ///< Timestamp of last interrupt initialized with static to persist until next function call.
        TRACE_LN_u(last_interrupt_time_ms);
        if (!ButtonDebouncer::is_button_debounced(last_interrupt_time_ms)) {
            Log.verboseln(LogController::MUTE_BUTTON_DEBOUNCED);
            return;
        }

        noInterrupts(); // Temporarily disable interrupts while updating system state
        AirQualityMeter::state.is_system_muted = !AirQualityMeter::state.is_system_muted;
        MuteIndicator::indicate_system_mute(AirQualityMeter::state.is_system_muted);
        interrupts(); // Re-enable interrupts

        Log.verboseln(LogController::STATE_UPDATED);
        LogController::log_current_state();

    }
}
