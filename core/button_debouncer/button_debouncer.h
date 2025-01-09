/**
 * @file    button_debouncer.h
 * @brief   Header file for button debouncing functionality.
 */

#ifndef BUTTON_DEBOUNCER_H
#define BUTTON_DEBOUNCER_H

namespace ButtonDebouncer {
    /**
     * @brief   Checks if the button press is debounced based on the last detected button press timestamp.
     * @details This function evaluates whether the time elapsed since the last detected button press exceeds
     *          a predefined debounce delay, ensuring stable button press detection.
     * @param last_button_press_detected_ms A reference to the timestamp of the last detected button press.
     *                                      The value is updated if the button press is deemed debounced.
     * @param is_long_delay_used Specifies whether a longer debounce delay should be applied.
     *                           If true, a longer delay is used; otherwise, a standard delay is applied.
     * @return  true if the button press is debounced, false otherwise.
     */
    bool is_button_debounced(unsigned long &last_button_press_detected_ms, bool is_long_delay_used = false);
}

#endif //BUTTON_DEBOUNCER_H