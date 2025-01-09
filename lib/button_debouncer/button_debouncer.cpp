/**
 * @file    button_debouncer.cpp
 * @brief   Implementation of the button debouncing logic.
 */

#include <button_debouncer.h>
#include <Arduino.h>

namespace ButtonDebouncer {
    constexpr unsigned long LONG_DEBOUNCE_DELAY_MS = 1000UL; ///< Time between two button presses to debounce.
    constexpr unsigned long DEFAULT_DEBOUNCE_DELAY_MS = 100UL; ///< Time between two button presses to debounce.

    bool is_button_debounced(unsigned long &last_button_press_detected_ms, const bool is_long_delay_used) {
        const unsigned long current_time = millis();
        const unsigned long time_delta_between_detected_button_press_ms = current_time - last_button_press_detected_ms;
        const unsigned long debounce_delay_ms = is_long_delay_used ? LONG_DEBOUNCE_DELAY_MS : DEFAULT_DEBOUNCE_DELAY_MS;
        if (time_delta_between_detected_button_press_ms < debounce_delay_ms) {
            return false;
        }
        last_button_press_detected_ms = current_time;
        return true;
    }
}
