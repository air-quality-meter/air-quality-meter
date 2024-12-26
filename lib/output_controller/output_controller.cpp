/**
 * @file    output_controller.cpp
 * @brief   This file contains functions and constants to manage the air quality measurements,
 *          display outputs, LED indicators, and audio warnings for the air quality monitoring system.
 * 
 * @details The functions in this file handle updating the display with CO2 levels and air quality
 *          descriptions, controlling LED indicators based on air quality status, and managing warnings
 *          when the air quality exceeds acceptable thresholds.
 */

#include <Arduino.h>
#include <output_controller.h>
#include <audio_controller.h>
#include <state.h>

void reset_warning_state(unsigned long current_time_s);

unsigned long get_time_since_co2_level_not_acceptable_s(unsigned long current_time_s);

void update_warning_state_for_co2_level_not_acceptable(unsigned long current_time_s);

constexpr int MAX_CONSECUTIVE_WARNINGS = 5; ///< Max consecutive audio warnings before auto reset

constexpr unsigned int MAX_CO2_ABOVE_THRESHOLD_TIME_S = 3600;
///< Max time period allowed CO2 above threshold (seconds)

constexpr unsigned int WAITING_PERIOD_BETWEEN_WARNINGS_S = 60; ///< Time period between two warnings (seconds)


namespace OutputController {
    void manage_audio_warnings(const unsigned long current_time_s, const bool is_air_quality_acceptable) {
        if (is_air_quality_acceptable) {
            reset_warning_state(current_time_s);
            return;
        }
        const unsigned long time_since_co2_level_not_acceptable_s = get_time_since_co2_level_not_acceptable_s(
            current_time_s);
        if (time_since_co2_level_not_acceptable_s > MAX_CO2_ABOVE_THRESHOLD_TIME_S) {
            AudioController::issue_warning();
            update_warning_state_for_co2_level_not_acceptable(current_time_s);
        }
    }
}

void update_warning_state_for_co2_level_not_acceptable(const unsigned long current_time_s) {
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

void reset_warning_state(const unsigned long current_time_s) {
    noInterrupts(); ///< prevent interrupts while writing on system state
    AirQualityMeter::state.last_co2_below_threshold_time_s = current_time_s;
    AirQualityMeter::state.warning_counter = 0;
    interrupts();
}

unsigned long get_time_since_co2_level_not_acceptable_s(const unsigned long current_time_s) {
    return current_time_s - AirQualityMeter::state.last_co2_below_threshold_time_s;
    ///< Time delta since air quality is not acceptable.
    ///< @note As all time variables and constants are unsigned, a possible time overflow will still be handled correctly.
    ///< A potentially very high value for the variable last_co2_below_threshold_time_s of almost the maximum of the unsigned
    ///< long type still leads to a correct result of the subraction (current_time_s - last_co2_below_threshold_time_s) even
    ///< after an overflow of millis(), when current_time_s has a very small value again.
    ///< @see  https://en.cppreference.com/w/cpp/language/operator_arithmetic#:~:text=conversions%20are%20applied.-,Overflows,-Unsigned%20integer%20arithmetic
}
