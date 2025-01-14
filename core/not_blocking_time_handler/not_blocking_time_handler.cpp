/**
 * @file not_blocking_time_handler.cpp
 * @brief Provides a non-blocking time delay implementation.
 *
 * This file contains the definition of the `wait_ms` function, 
 * which enables a non-blocking delay mechanism, allowing other tasks 
 * (like handling interrupts) to execute during the waiting period.
 */

#include <Arduino.h>
#include "not_blocking_time_handler.h"

namespace NotBlockingTimeHandler {
    void wait_ms(const unsigned long waiting_time_ms) {
        const unsigned long start_time_ms = millis();
        const unsigned long end_time_ms = start_time_ms + waiting_time_ms;
        while (millis() < end_time_ms) {
        }
    }
}
