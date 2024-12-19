#include <Arduino.h>

/**
 * @file    air_quality_manager.cpp
 * @brief   This file contains the function definitions for managing
 *          the air quality.
 */

#include "air_quality_manager.h"
#include "audio_warning.h"
#include "system_state.h"
#include "system_manager.h"
#include "leds.h"
#include "display.h"

const String CO2_PREFIX = "CO2: "; ///< Prefix to display CO2 value
const String PPM_SUFFIX = " ppm"; ///< Suffix to display a value with ppm as the unit
const String HIGH_AIR_QUALITY_DESCRIPTION = "High air quality"; ///< Text for IDA 1
const String MEDIUM_AIR_QUALITY_DESCRIPTION = "Medium air quality"; ///< Text for IDA 2
const String MODERATE_AIR_QUALITY_DESCRIPTION = "Moderate air quality"; ///< Text for IDA 3
const String POOR_AIR_QUALITY_DESCRIPTION = "Poor air quality"; ///< Text for IDA 4

const AirQualityRule HIGH_AIR_QUALITY_RULE = {
    HIGH_AIR_QUALITY_LEVEL,
    HIGH_AIR_QUALITY_LED_INDICATOR,
    HIGH_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_HIGH_AIR_QUALITY_PPM
};

const AirQualityRule MEDIUM_AIR_QUALITY_RULE = {
    MEDIUM_AIR_QUALITY_LEVEL,
    MEDIUM_AIR_QUALITY_LED_INDICATOR,
    MEDIUM_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_MEDIUM_AIR_QUALITY_PPM
};

const AirQualityRule LOWER_MODERATE_AIR_QUALITY_RULE = {
    LOWER_MODERATE_AIR_QUALITY_LEVEL,
    LOWER_MODERATE_AIR_QUALITY_LED_INDICATOR,
    MODERATE_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_MID_THRESHOLD_MODERATE_AIR_QUALITY_PPM
};

const AirQualityRule UPPER_MODERATE_AIR_QUALITY_RULE = {
    UPPER_MODERATE_AIR_QUALITY_LEVEL,
    UPPER_MODERATE_AIR_QUALITY_LED_INDICATOR,
    MODERATE_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_MODERATE_AIR_QUALITY_PPM
};

const AirQualityRule POOR_AIR_QUALITY_RULE = {
    POOR_AIR_QUALITY_LEVEL,
    POOR_AIR_QUALITY_LED_INDICATOR,
    POOR_AIR_QUALITY_DESCRIPTION,
    false,
    NO_UPPER_LIMIT // No upper limit for poor air quality.
};

const AirQualityRule AIR_QUALITY_RULES[] = {
    HIGH_AIR_QUALITY_RULE,
    MEDIUM_AIR_QUALITY_RULE,
    LOWER_MODERATE_AIR_QUALITY_RULE,
    UPPER_MODERATE_AIR_QUALITY_RULE,
    POOR_AIR_QUALITY_RULE
};

AirQualityRule get_air_quality_rule(const int co2_measurement_ppm) {
    for (const AirQualityRule &air_quality_rule: AIR_QUALITY_RULES) {
        if (co2_measurement_ppm <= air_quality_rule.upper_threshold_ppm) {
            return air_quality_rule;
        }
    }
    return AIR_QUALITY_RULES[POOR_AIR_QUALITY_LEVEL];
}

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
    if (time_since_co2_level_not_acceptable_s > MAX_CO2_ABOVE_THRESHOLD_TIME_S) {
        issue_audio_warning();
        // Wait until the next audio warning to prevent uninterrupted audio output.
        system_state.last_co2_below_threshold_time_s =
                system_state.last_co2_below_threshold_time_s + WAITING_PERIOD_BETWEEN_WARNINGS_S;
        system_state.warning_counter++;
        if (system_state.warning_counter >= MAX_CONSECUTIVE_WARNINGS) {
            reset_co2_below_threshold_and_warning_counter();
        }
    }
}
