#include <Arduino.h>

/**
 * @file    air_quality_manager.cpp
 * @brief   This file contains the function definitions for managing
 *          the air quality.
 */

#include "air_quality_manager.h"

#include <global_constants.h>
#include "audio_warning.h"
#include "system_state.h"
#include "system_manager.h"
#include "leds.h"
#include "display.h"

const String co2_prefix = "CO2: "; ///< Prefix to display CO2 value
const String ppm_suffix = " ppm"; ///< Suffix to display a value with ppm as the unit
const String high_air_quality_description = "High air quality"; ///< Text for IDA 1
const String medium_air_quality_description = "Medium air quality"; ///< Text for IDA 2
const String moderate_air_quality_description = "Moderate air quality"; ///< Text for IDA 3
const String poor_air_quality_description = "Poor air quality"; ///< Text for IDA 4

const AirQualityRule high_air_quality_rule = {
    HIGH_AIR_QUALITY_LEVEL,
    high_air_quality_led_indicator,
    high_air_quality_description,
    true,
    co2_upper_threshold_high_air_quality_ppm
};

const AirQualityRule medium_air_quality_rule = {
    MEDIUM_AIR_QUALITY_LEVEL,
    medium_air_quality_led_indicator,
    medium_air_quality_description,
    true,
    co2_upper_threshold_medium_air_quality_ppm
};

const AirQualityRule lower_moderate_air_quality_rule = {
    LOWER_MODERATE_AIR_QUALITY_LEVEL,
    lower_moderate_air_quality_led_indicator,
    moderate_air_quality_description,
    true,
    co2_mid_threshold_moderate_air_quality_ppm
};

const AirQualityRule upper_moderate_air_quality_rule = {
    UPPER_MODERATE_AIR_QUALITY_LEVEL,
    upper_moderate_air_quality_led_indicator,
    moderate_air_quality_description,
    true,
    co2_upper_threshold_moderate_air_quality_ppm
};

const AirQualityRule poor_air_quality_rule = {
    POOR_AIR_QUALITY_LEVEL,
    poor_air_quality_led_indicator,
    poor_air_quality_description,
    false,
    NO_UPPER_LIMIT // No upper limit for poor air quality.
};

const AirQualityRule air_quality_rules[] = {
    high_air_quality_rule,
    medium_air_quality_rule,
    lower_moderate_air_quality_rule,
    upper_moderate_air_quality_rule,
    poor_air_quality_rule
};

AirQualityRule get_air_quality_rule(const int co2_measurement_ppm) {
    for (const AirQualityRule &air_quality_rule: air_quality_rules) {
        if (co2_measurement_ppm <= air_quality_rule.upper_threshold_ppm) {
            return air_quality_rule;
        }
    }
    return air_quality_rules[POOR_AIR_QUALITY_LEVEL];
}

void update_display_air_quality_output(const int co2_measurement_ppm, const String &air_quality_description) {
    const String line_1 = co2_prefix + co2_measurement_ppm + ppm_suffix;
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
        reset_co2_below_threshold_and_warning_counter();
        return;
    }
    const unsigned long time_since_co2_level_not_acceptable_s = current_time_s - system_state.last_co2_below_threshold_time_s;
    ///< Time delta since air quality is not acceptable.
    ///< @note As all time variables and constants are unsigned, a possible time overflow will still be handled correctly.
    ///< A potentially very high value for the variable last_co2_below_threshold_time_s of almost the maximum of the unsigned
    ///< long type still leads to a correct result of the subraction (current_time_s - last_co2_below_threshold_time_s) even
    ///< after an overflow of millis(), when current_time_s has a very small value again.
    ///< @see  https://en.cppreference.com/w/cpp/language/operator_arithmetic#:~:text=conversions%20are%20applied.-,Overflows,-Unsigned%20integer%20arithmetic
    if (time_since_co2_level_not_acceptable_s > max_co2_above_threshold_time_s) {
        issue_audio_warning();
        // Wait until the next audio warning to prevent uninterrupted audio output.
        system_state.last_co2_below_threshold_time_s =
                system_state.last_co2_below_threshold_time_s + waiting_period_between_warnings_s;
        system_state.warning_counter++;
        if (system_state.warning_counter >= max_consecutive_warnings) {
            reset_co2_below_threshold_and_warning_counter();
        }
    }
}
