#include <Arduino.h>

/**
 * @file    air_quality_manager.cpp
 * @brief   This file contains the function definitions for managing
 *          the air quality.
 */

#include "air_quality_manager.h"
#include "../display/leds.h"
#include "../display/display.h"

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
