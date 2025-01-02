/**
 * @file  time_controller.cpp
 * @brief Provides functionality to retrieve the current time in seconds since the Arduino board was powered on.
 */

#include <Arduino.h>
#include <time_controller.h>

namespace TimeController {
    unsigned long get_timestamp_s() {
        const unsigned long time_since_board_on_ms = millis(); ///< Current time since power-on in milliseconds.
        const unsigned long time_since_board_on_s = time_since_board_on_ms / 1000; ///< Current time in seconds.
        return time_since_board_on_s;
    }
}
