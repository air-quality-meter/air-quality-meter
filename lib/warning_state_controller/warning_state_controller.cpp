/**
 * @file warning_state_controller.cpp
 * @brief Implements warning state handling related to CO2 level monitoring.
 * @details Contains the logic for resetting warnings and managing the timing and frequency of warning alerts.
 */

#include <Arduino.h>
#include <warning_state_controller.h>
#include <state.h>

namespace WarningStateController {
    constexpr int MAX_CONSECUTIVE_WARNINGS = 5; ///< Max consecutive audio warnings before auto reset

    constexpr unsigned int WAITING_PERIOD_BETWEEN_WARNINGS_S = 60; ///< Time period between two warnings (seconds)

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
