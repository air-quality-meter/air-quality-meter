/**
 * @file  time_controller.cpp
 * @brief Provides functionality to retrieve the current time in seconds since the Arduino board was powered on.
 */

#include <Arduino.h>
#include <time_controller.h>

namespace TimeController {
    unsigned long get_current_time_in_s() {
        const unsigned long time_since_board_on_ms = millis(); ///< timestamp in milliseconds
        const unsigned long time_since_board_on_s = time_since_board_on_ms / 1000; ///< timestamp in seconds
        return time_since_board_on_s;
    }
}
