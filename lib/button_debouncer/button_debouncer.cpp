/**
 * @file    button_debouncer.cpp
 * @brief   Implementation of the button debouncing logic.
 */

#include <button_debouncer.h>
#include <Arduino.h>

namespace ButtonDebouncer {
    constexpr unsigned long DEBOUNCE_DELAY_MS = 1000; ///< Time between two interrupts to debounce.
    bool is_button_debounced(unsigned long &last_button_press_detected_ms) {
        const unsigned long current_time = millis();
        const unsigned long time_delta_between_detected_button_press_ms = current_time - last_button_press_detected_ms;
        if (time_delta_between_detected_button_press_ms < DEBOUNCE_DELAY_MS) {
            return false;
        }
        last_button_press_detected_ms = current_time;
        return true;
    }
}
