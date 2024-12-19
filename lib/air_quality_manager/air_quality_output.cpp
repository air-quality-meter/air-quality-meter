/**
 * @file    air_quality_output.cpp
 * @brief   This file contains functions and constants to manage the air quality measurements,
 *          display outputs, LED indicators, and audio warnings for the air quality monitoring system.
 * 
 * @details The functions in this file handle updating the display with CO2 levels and air quality
 *          descriptions, controlling LED indicators based on air quality status, and managing warnings
 *          when the air quality exceeds acceptable thresholds.
 */

#include <Arduino.h>
#include "air_quality_manager.h"
#include "audio_warning.h"
#include "system_state.h"
#include "system_manager.h"
#include "leds.h"
#include "display.h"

constexpr int MAX_CONSECUTIVE_WARNINGS = 5; ///< Max consecutive audio warnings before reset

constexpr unsigned int MAX_CO2_ABOVE_THRESHOLD_TIME_S = 3600;
///< Max time period allowed CO2 above threshold (seconds)

constexpr unsigned int WAITING_PERIOD_BETWEEN_WARNINGS_S = 60; ///< Time period between two warnings (seconds)

const String CO2_PREFIX = "CO2: "; ///< Prefix to display CO2 value
const String PPM_SUFFIX = " ppm"; ///< Suffix to display a value with ppm as the unit

void update_display_air_quality_output(const int co2_measurement_ppm, const String &air_quality_description) {
    const String line_1 = CO2_PREFIX + co2_measurement_ppm + PPM_SUFFIX;
    display_out(line_1, air_quality_description);
}

void update_led_air_quality_output(const LEDIndicator &led_indicator) {
    set_leds(led_indicator.is_green_led_1_on,
             led_indicator.is_green_led_2_on,
             led_indicator.is_yellow_led_1_on,
             led_indicator.is_yellow_led_2_on,
             led_indicator.is_red_led_1_on,
             led_indicator.is_red_led_2_on);
}

void manage_unacceptable_air_quality_level(const unsigned long current_time_s, const bool is_air_quality_acceptable) {
    if (is_air_quality_acceptable) {
        noInterrupts(); ///< prevent interrupts while calling reset function
        reset_co2_below_threshold_and_warning_counter();
        interrupts();
        return;
    }
    const unsigned long time_since_co2_level_not_acceptable_s = current_time_s - system_state.last_co2_below_threshold_time_s;
    ///< Time delta since air quality is not acceptable.
    ///< @note As all time variables and constants are unsigned, a possible time overflow will still be handled correctly.
    ///< A potentially very high value for the variable last_co2_below_threshold_time_s of almost the maximum of the unsigned
    ///< long type still leads to a correct result of the subraction (current_time_s - last_co2_below_threshold_time_s) even
    ///< after an overflow of millis(), when current_time_s has a very small value again.
    ///< @see  https://en.cppreference.com/w/cpp/language/operator_arithmetic#:~:text=conversions%20are%20applied.-,Overflows,-Unsigned%20integer%20arithmetic
    if (time_since_co2_level_not_acceptable_s > MAX_CO2_ABOVE_THRESHOLD_TIME_S) {
        issue_audio_warning();
        // Wait until the next audio warning to prevent uninterrupted audio output.
        system_state.last_co2_below_threshold_time_s =
                system_state.last_co2_below_threshold_time_s + WAITING_PERIOD_BETWEEN_WARNINGS_S;
        system_state.warning_counter++;
        if (system_state.warning_counter >= MAX_CONSECUTIVE_WARNINGS) {
            noInterrupts(); ///< prevent interrupts while calling reset function
            reset_co2_below_threshold_and_warning_counter();
            interrupts();
        }
    }
}
