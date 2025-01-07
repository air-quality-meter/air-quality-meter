#include <Arduino.h>
#include <mute_button.h>
#include <ArduinoLog.h>
#include <state.h>
#include <pin_configuration.h>
#include <mute_indicator.h>

#include "../log_controller/log_controller.h"

namespace MuteButton {
    constexpr unsigned long DEBOUNCE_DELAY_MS = 1000; ///< Time between two interrupts to debounce.

    void initialize() {
        pinMode(DIGITAL_PIN, INPUT);
        attachInterrupt(
            digitalPinToInterrupt(DIGITAL_PIN),
            switchMuteState, RISING);
    }

    void switchMuteState() {
        Log.infoln(LogController::MUTE_BUTTON_PRESSED);
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
            // Avoid false triggers caused by mechanical bouncing of the button.
            Log.verboseln(LogController::MUTE_BUTTON_DEBOUNCED);
            return;
        }
        last_interrupt_time_ms = interrupt_time_ms; // updated last interrupt time for debouncing

        noInterrupts(); // Temporarily disable interrupts while updating system state
        AirQualityMeter::state.is_system_muted = !AirQualityMeter::state.is_system_muted;
        interrupts(); // Re-enable interrupts

        MuteIndicator::indicate_system_mute(AirQualityMeter::state.is_system_muted);

        Log.verboseln(LogController::STATE_UPDATED);
        LogController::log_current_state();
    }
}
