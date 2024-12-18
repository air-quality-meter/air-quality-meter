#include <Arduino.h>

/**
 * @file    air_quality_manager.cpp
 * @brief   This file contains the function definitions for managing
 *          the air quality.
 */

#include "air_quality_manager.h"
#include "../display/leds.h"
#include "../display/display.h"

LEDIndicator air_quality_led_indicators[] = {
    {
        HIGH_AIR_QUALITY_LEVEL,
        true,
        true,
        false,
        false,
        false,
        false
    },
    {
        MEDIUM_AIR_QUALITY_LEVEL,
        false,
        true,
        true,
        false,
        false,
        false
    },
    {
        LOWER_MODERATE_AIR_QUALITY_LEVEL,
        false,
        false,
        true,
        true,
        false,
        false
    },
    {
        UPPER_MODERATE_AIR_QUALITY_LEVEL,
        false,
        false,
        false,
        true,
        true,
        false
    },
    {
        POOR_AIR_QUALITY_LEVEL,
        false,
        false,
        false,
        false,
        true,
        true
    }
};

AirQualityRule air_quality_rules[] = {
    {
        HIGH_AIR_QUALITY_LEVEL,
        high_air_quality_description,
        air_quality_led_indicators[HIGH_AIR_QUALITY_LEVEL],
        true,
        co2_upper_threshold_high_air_quality_ppm
    },
    {
        MEDIUM_AIR_QUALITY_LEVEL,
        medium_air_quality_description,
        air_quality_led_indicators[MEDIUM_AIR_QUALITY_LEVEL],
        true,
        co2_upper_threshold_medium_air_quality_ppm
    },
    {
        LOWER_MODERATE_AIR_QUALITY_LEVEL,
        moderate_air_quality_description,
        air_quality_led_indicators[LOWER_MODERATE_AIR_QUALITY_LEVEL],
        true,
        co2_mid_threshold_moderate_air_quality_ppm
    },
    {
        UPPER_MODERATE_AIR_QUALITY_LEVEL,
        moderate_air_quality_description,
        air_quality_led_indicators[UPPER_MODERATE_AIR_QUALITY_LEVEL],
        true,
        co2_upper_threshold_medium_air_quality_ppm
    },
    {
        POOR_AIR_QUALITY_LEVEL,
        poor_air_quality_description,
        air_quality_led_indicators[POOR_AIR_QUALITY_LEVEL],
        false,
        NO_UPPER_LIMIT
    }
};

const AirQualityRule *get_air_quality_rule(const int co2_measurement_ppm) {
    for (const AirQualityRule &air_quality_rule: air_quality_rules) {
        if (co2_measurement_ppm <= air_quality_rule.upper_threshold_ppm) {
            return &air_quality_rule;
        }
    }
    return &air_quality_rules[POOR_AIR_QUALITY_LEVEL];
}

DisplayLines get_air_quality_display_text(const int co2_measurement_ppm, const char *line_2) {
    DisplayLines display_lines;
    snprintf(display_lines.line_1, display_line_1_size, "%s %d %s", co2_prefix, co2_measurement_ppm, ppm_suffix);
    ///< Formatting the text (concatenate).
    display_lines.line_1[display_line_1_size - 1] = '\0'; // Ensure there is a null termination at the end.
    strncpy(display_lines.line_2, line_2, display_line_2_size - 1);
    display_lines.line_2[display_line_2_size - 1] = '\0'; // Ensure there is a null termination at the end.
    return display_lines;
}

void manage_air_quality(const int co2_measurement_ppm, const AirQualityRule *air_quality_rule) {
    DisplayLines display_lines = get_air_quality_display_text(co2_measurement_ppm, air_quality_rule->description);
    set_leds(air_quality_rule->led_indicator.is_green_led_1_on,
             air_quality_rule->led_indicator.is_green_led_2_on,
             air_quality_rule->led_indicator.is_yellow_led_1_on,
             air_quality_rule->led_indicator.is_yellow_led_2_on,
             air_quality_rule->led_indicator.is_red_led_1_on,
             air_quality_rule->led_indicator.is_red_led_2_on);
    display_out(display_lines.line_1, display_lines.line_2);
}
