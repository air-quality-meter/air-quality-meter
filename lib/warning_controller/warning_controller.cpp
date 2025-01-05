/**
 * @file warning_controller.cpp
 * @brief Implementation of the WarningController namespace.
 *
 * Contains the implementation of warning logic based on CO2 exceedance time.
 */

#include <Arduino.h>
#include <warning_controller.h>
#include <state.h>

namespace WarningController {
    constexpr int MAX_CONSECUTIVE_WARNINGS = 5; ///< Max consecutive audio warnings before auto reset

    constexpr unsigned int WAITING_PERIOD_BETWEEN_WARNINGS_S = 60; ///< Time period between two warnings (seconds)

    constexpr unsigned int MAX_CO2_ABOVE_THRESHOLD_TIME_S = 3600;
    ///< The maximum duration (in seconds) for CO2 levels to remain above the threshold
    ///< before triggering a warning.

    bool is_audio_warning_to_be_issued(const unsigned long time_since_co2_level_not_acceptable_s) {
        return time_since_co2_level_not_acceptable_s > MAX_CO2_ABOVE_THRESHOLD_TIME_S;
    }

    void reset(const unsigned long current_time_s) {
        noInterrupts(); ///< prevent interrupts while writing on system state
        AirQualityMeter::state.last_co2_below_threshold_time_s = current_time_s;
        AirQualityMeter::state.warning_counter = 0;
        interrupts();
    }

    void update_for_co2_level_not_acceptable(const unsigned long current_time_s) {
        AirQualityMeter::state.warning_counter++;
        if (AirQualityMeter::state.warning_counter >= MAX_CONSECUTIVE_WARNINGS) {
            noInterrupts(); ///< prevent interrupts while writing on system state
            AirQualityMeter::state.last_co2_below_threshold_time_s = current_time_s;
            AirQualityMeter::state.warning_counter = 0;
            interrupts();
            return;
        }
        // Wait until the next audio warning to prevent uninterrupted audio output.
        AirQualityMeter::state.last_co2_below_threshold_time_s =
                AirQualityMeter::state.last_co2_below_threshold_time_s + WAITING_PERIOD_BETWEEN_WARNINGS_S;
    }
}
