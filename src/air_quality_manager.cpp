#include <Arduino.h>

/**
 * @file    air_quality_manager.cpp
 * @brief   This file contains the function definitions for managing
 *          the air quality.
 */

#include "air_quality_manager.h"
#include "global_constants.h"
#include "leds.h"
#include "display.h"

// variables
char display_line_1[display_line_1_size] = ""; ///< first line to display on the LCD1602 Module
char display_line_2[display_line_2_size] = ""; ///< second line to display on the LCD1602 Module

enum AirQualityLevel {
    HIGH_AIR_QUALITY_LEVEL,
    MEDIUM_AIR_QUALITY_LEVEL,
    LOWER_MODERATE_AIR_QUALITY_LEVEL,
    UPPER_MODERATE_AIR_QUALITY_LEVEL,
    POOR_AIR_QUALITY_LEVEL
};

struct LEDIndicator {
    AirQualityLevel air_quality_level;
    bool is_green_led_1_on;
    bool is_green_led_2_on;
    bool is_yellow_led_1_on;
    bool is_yellow_led_2_on;
    bool is_red_led_1_on;
    bool is_red_led_2_on;
};

struct AirQualityRule {
    constexpr AirQualityLevel air_quality_level;
    const char *description;
    ///< Pointer to a description char array (string). That allows storing and referencing a text description for
    ///< an air quality level without copying the entire string
    constexpr LEDIndicator led_indicator;
    const bool is_level_acceptable;
    constexpr int upper_threshold_ppm;
    ///< Upper co2 threshold for level; -1 indicates "no upper limit" (poor air quality)
};

LEDIndicator air_quality_led_indicators[] = {
    {HIGH_AIR_QUALITY_LEVEL, true, true, false, false, false, false},
    {MEDIUM_AIR_QUALITY_LEVEL, false, true, true, false, false, false},
    {LOWER_MODERATE_AIR_QUALITY_LEVEL, false, false, true, true, false, false},
    {UPPER_MODERATE_AIR_QUALITY_LEVEL, false, false, false, true, true, false},
    {POOR_AIR_QUALITY_LEVEL, false, false, false, false, true, true}
};

AirQualityRule air_quality_rules[] = {
    {
        HIGH_AIR_QUALITY_LEVEL, high_air_quality_description, air_quality_led_indicators[HIGH_AIR_QUALITY_LEVEL], true,
        co2_upper_threshold_high_air_quality_ppm
    },
    {
        MEDIUM_AIR_QUALITY_LEVEL, medium_air_quality_description, air_quality_led_indicators[MEDIUM_AIR_QUALITY_LEVEL],
        true, co2_upper_threshold_medium_air_quality_ppm
    },
    {
        LOWER_MODERATE_AIR_QUALITY_LEVEL, moderate_air_quality_description,
        air_quality_led_indicators[LOWER_MODERATE_AIR_QUALITY_LEVEL], true, co2_mid_threshold_moderate_air_quality_ppm
    },
    {
        UPPER_MODERATE_AIR_QUALITY_LEVEL, moderate_air_quality_description,
        air_quality_led_indicators[UPPER_MODERATE_AIR_QUALITY_LEVEL], true, co2_upper_threshold_medium_air_quality_ppm
    },
    {
        POOR_AIR_QUALITY_LEVEL, poor_air_quality_description, air_quality_led_indicators[POOR_AIR_QUALITY_LEVEL], false,
        -1
    } ///< Poor air quality has no upper limit.
};

void manage_air_quality(const int co2_measurement_ppm) {
    snprintf(display_line_1, display_line_1_size, "%s %d %s", co2_prefix, co2_measurement_ppm, ppm_suffix);
    ///< Formatting the text (concatenate).
    if (co2_measurement_ppm <= co2_upper_threshold_high_air_quality_ppm) {
        strncpy(display_line_2, high_air_quality_description, display_line_2_size - 1);
        display_line_2[display_line_2_size - 1] = '\0'; // Ensure there is a null termination at the end.
        set_leds(true, true, false, false, false, false);
    } else if (co2_measurement_ppm <= co2_upper_threshold_medium_air_quality_ppm) {
        strncpy(display_line_2, medium_air_quality_description, display_line_2_size - 1);
        display_line_2[display_line_2_size - 1] = '\0'; // Ensure there is a null termination at the end.
        set_leds(false, true, true, false, false, false);
    } else if (co2_measurement_ppm <= co2_mid_threshold_moderate_air_quality_ppm) {
        strncpy(display_line_2, moderate_air_quality_description, display_line_2_size - 1);
        display_line_2[display_line_2_size - 1] = '\0'; // Ensure there is a null termination at the end.
        set_leds(false, false, true, true, false, false);
    } else if (co2_measurement_ppm <= co2_upper_threshold_moderate_air_quality_ppm) {
        strncpy(display_line_2, moderate_air_quality_description, display_line_2_size - 1);
        display_line_2[display_line_2_size - 1] = '\0'; // Ensure there is a null termination at the end.
        set_leds(false, false, false, true, true, false);
    } else {
        strncpy(display_line_2, poor_air_quality_description, display_line_2_size - 1);
        display_line_2[display_line_2_size - 1] = '\0'; // Ensure there is a null termination at the end.
        set_leds(false, false, false, false, true, true);
    }
    display_out(display_line_1, display_line_2);
}
