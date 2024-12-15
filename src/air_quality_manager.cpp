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

void manage_air_quality(const int co2_measurement_ppm) {
    snprintf(display_line_1, display_line_1_size, "%s %d %s", co2_prefix, co2_measurement_ppm, ppm_suffix);
    ///< Formatting the text (concatenate).
    if (co2_measurement_ppm <= co2_upper_threshold_high_air_quality_ppm) {
        strncpy(display_line_2, high_air_quality_description, display_line_2_size - 1);
        display_line_2[display_line_2_size-1] = '\0'; // Ensure there is a null termination at the end.
        set_leds(true, true, false, false, false, false);
    } else if (co2_measurement_ppm <= co2_upper_threshold_medium_air_quality_ppm) {
        strncpy(display_line_2, medium_air_quality_description, display_line_2_size - 1);
        display_line_2[display_line_2_size-1] = '\0'; // Ensure there is a null termination at the end.
        set_leds(false, true, true, false, false, false);
    } else if (co2_measurement_ppm <= co2_mid_threshold_moderate_air_quality_ppm) {
        strncpy(display_line_2, moderate_air_quality_description, display_line_2_size - 1);
        display_line_2[display_line_2_size-1] = '\0'; // Ensure there is a null termination at the end.
        set_leds(false, false, true, true, false, false);
    } else if (co2_measurement_ppm <= co2_upper_threshold_moderate_air_quality_ppm) {
        strncpy(display_line_2, moderate_air_quality_description, display_line_2_size - 1);
        display_line_2[display_line_2_size-1] = '\0'; // Ensure there is a null termination at the end.
        set_leds(false, false, false, true, true, false);
    } else {
        strncpy(display_line_2, poor_air_quality_description, display_line_2_size - 1);
        display_line_2[display_line_2_size-1] = '\0'; // Ensure there is a null termination at the end.
        set_leds(false, false, false, false, true, true);
    }
    display_out(display_line_1, display_line_2);
}
