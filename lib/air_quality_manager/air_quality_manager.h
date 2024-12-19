/**
 * @file    air_quality_manager.h
 * @brief   This file contains the function declarations for managing
 *          the air quality.
 */

#ifndef AIR_QUALITY_MANAGER_H
#define AIR_QUALITY_MANAGER_H

enum AirQualityLevel {
    HIGH_AIR_QUALITY_LEVEL,
    MEDIUM_AIR_QUALITY_LEVEL,
    LOWER_MODERATE_AIR_QUALITY_LEVEL,
    UPPER_MODERATE_AIR_QUALITY_LEVEL,
    POOR_AIR_QUALITY_LEVEL,
};

struct LEDIndicator {
    bool is_green_led_1_on;
    bool is_green_led_2_on;
    bool is_yellow_led_1_on;
    bool is_yellow_led_2_on;
    bool is_red_led_1_on;
    bool is_red_led_2_on;
};

struct AirQualityRule {
    AirQualityLevel air_quality_level;
    LEDIndicator led_indicator;
    String description;
    bool is_level_acceptable;
    int upper_threshold_ppm;
    ///< Upper co2 threshold for level; -1 indicates "no upper limit" (poor air quality)
};

AirQualityRule get_air_quality_rule(int co2_measurement_ppm);

void update_display_air_quality_output(int co2_measurement_ppm, const String &air_quality_description);

void update_led_air_quality_output(const LEDIndicator &led_indicator);

void manage_unacceptable_air_quality_level(unsigned long current_time_s, bool is_air_quality_acceptable);

#endif //AIR_QUALITY_MANAGER_H
