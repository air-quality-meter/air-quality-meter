/**
 * @file    air_quality_manager.h
 * @brief   This file contains the function declarations for managing
 *          the air quality.
 */

#ifndef AIR_QUALITY_MANAGER_H
#define AIR_QUALITY_MANAGER_H

constexpr int co2_upper_threshold_high_air_quality_ppm = 800;
///< Upper CO2 threshold (less than or equal to) for high indoor air quality (IDA 1 DIN EN 13779)
///< in parts per million (ppm)

constexpr int co2_upper_threshold_medium_air_quality_ppm = 1000;
///< Upper CO2 threshold (less than or equal to) for medium indoor air quality (IDA 2 DIN EN 13779)
///< in parts per million (ppm)

constexpr int co2_mid_threshold_moderate_air_quality_ppm = 1200;
///< Upper CO2 threshold (less than or equal to) for lower half (mid) of moderate indoor air quality
///< (IDA 3 DIN EN 13779) parts per million (ppm). The IDA 3 bandwidth is double the size of the IDA 2 bandwidth,
///< which is why it is divided into two halves here.

constexpr int co2_upper_threshold_moderate_air_quality_ppm = 1400;
///< Upper CO2 threshold (less than or equal to) for moderate indoor air quality (IDA 3 DIN EN 13779)
///< parts per million (ppm). At the same time, this value represents the lower threshold (greater than) value
///< for poor indoor air quality (IDA 4 DIN EN 13779)

constexpr int NO_UPPER_LIMIT = -1;

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

constexpr LEDIndicator high_air_quality_led_indicator = {
    true,
    true,
    false,
    false,
    false,
    false
};

constexpr LEDIndicator medium_air_quality_led_indicator = {
    false,
    true,
    true,
    false,
    false,
    false
};

constexpr LEDIndicator lower_moderate_air_quality_led_indicator = {
    false,
    false,
    true,
    true,
    false,
    false
};

constexpr LEDIndicator upper_moderate_air_quality_led_indicator = {
    false,
    false,
    false,
    true,
    true,
    false
};

constexpr LEDIndicator poor_air_quality_led_indicator = {
    false,
    false,
    false,
    false,
    true,
    true
};

AirQualityRule get_air_quality_rule(int co2_measurement_ppm);

void update_display_air_quality_output(int co2_measurement_ppm, const String &air_quality_description);

void update_led_air_quality_output(const LEDIndicator &led_indicator);

#endif //AIR_QUALITY_MANAGER_H
