/**
 * @file warning_controller.cpp
 * @brief Implementation of the WarningController namespace.
 *
 * This file contains the implementation of warning logic based on the duration
 * of CO2 level exceedance beyond a defined threshold. It manages warnings such as
 * issuing audio alerts after a specific period and resetting states when necessary.
 * The logic also includes mechanisms to prevent excessive repeated warnings.
 */

#include <Arduino.h>
#include <warning_controller.h>
#include <thresholds.h>
#include <state.h>

namespace WarningController {
    bool is_audio_warning_to_be_issued(const unsigned long time_since_co2_level_not_acceptable_ms) {
        return time_since_co2_level_not_acceptable_ms > WarningThresholds::MAX_TIME_ABOVE_CO2_THRESHOLD_MS;
    }

    void reset() {
        noInterrupts(); ///< prevent interrupts while writing on system state
        AirQualityMeter::state.last_co2_below_threshold_time_ms = millis();
        AirQualityMeter::state.warning_counter = 0;
        interrupts();
    }

    void update_for_co2_level_not_acceptable() {
        AirQualityMeter::state.warning_counter++;
        if (AirQualityMeter::state.warning_counter >= WarningThresholds::MAX_CONSECUTIVE_WARNINGS) {
            noInterrupts(); ///< prevent interrupts while writing on system state
            AirQualityMeter::state.last_co2_below_threshold_time_ms = millis();
            AirQualityMeter::state.warning_counter = 0;
            interrupts();
            return;
        }
        // Wait until the next audio warning to prevent uninterrupted audio output.
        AirQualityMeter::state.last_co2_below_threshold_time_ms =
                AirQualityMeter::state.last_co2_below_threshold_time_ms +
                WarningThresholds::WAITING_PERIOD_BETWEEN_WARNINGS_MS;
    }
}
