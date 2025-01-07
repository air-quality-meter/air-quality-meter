/**
 * @file    mute_indicator.cpp
 * @brief   Implementation of the Mute Indicator functionality.
 *
 * @details This file contains the implementation of the functions related to
 *          controlling the mute indicator, which visually indicates whether the system
 *          is in a muted state.
 */

#include <Arduino.h>
#include <mute_indicator.h>
#include <pin_configuration.h>
#include <ArduinoLog.h>
#include <log_controller.h>

namespace MuteIndicator {
    void initialize() {
        pinMode(BLUE_PIN, OUTPUT);
    }

    void indicate_system_mute(const bool is_mute) {
        digitalWrite(BLUE_PIN, is_mute);
        Log.verboseln(LogController::MUTE_INDICATOR_UPDATED);
    }
}
