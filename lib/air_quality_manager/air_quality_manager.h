/**
 * @file    air_quality_manager.h
 * @brief   This file contains the function declarations for managing
 *          the air quality.
 */

#ifndef AIR_QUALITY_MANAGER_H
#define AIR_QUALITY_MANAGER_H
#include <system_state.h>

constexpr int CO2_UPPER_THRESHOLD_HIGH_AIR_QUALITY_PPM = 800;
///< Upper CO2 threshold (less than or equal to) for high indoor air quality (IDA 1 DIN EN 13779)
///< in parts per million (ppm)

constexpr int CO2_UPPER_THRESHOLD_MEDIUM_AIR_QUALITY_PPM = 1000;
///< Upper CO2 threshold (less than or equal to) for medium indoor air quality (IDA 2 DIN EN 13779)
///< in parts per million (ppm)

constexpr int CO2_MID_THRESHOLD_MODERATE_AIR_QUALITY_PPM = 1200;
///< Upper CO2 threshold (less than or equal to) for lower half (mid) of moderate indoor air quality
///< (IDA 3 DIN EN 13779) parts per million (ppm). The IDA 3 bandwidth is double the size of the IDA 2 bandwidth,
///< which is why it is divided into two halves here.

constexpr int CO2_UPPER_THRESHOLD_MODERATE_AIR_QUALITY_PPM = 1400;
///< Upper CO2 threshold (less than or equal to) for moderate indoor air quality (IDA 3 DIN EN 13779)
///< parts per million (ppm). At the same time, this value represents the lower threshold (greater than) value
///< for poor indoor air quality (IDA 4 DIN EN 13779)

constexpr int NO_UPPER_LIMIT = -1;

constexpr int MAX_CONSECUTIVE_WARNINGS = 5; ///< Max consecutive audio warnings before reset

constexpr unsigned int MAX_CO2_ABOVE_THRESHOLD_TIME_S = 3600;
///< Max time period allowed CO2 above threshold (seconds)

constexpr unsigned int WAITING_PERIOD_BETWEEN_WARNINGS_S = 60; ///< Time period between two warnings (seconds)

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

constexpr LEDIndicator HIGH_AIR_QUALITY_LED_INDICATOR = {
    true,
    true,
    false,
    false,
    false,
    false
};

constexpr LEDIndicator MEDIUM_AIR_QUALITY_LED_INDICATOR = {
    false,
    true,
    true,
    false,
    false,
    false
};

constexpr LEDIndicator LOWER_MODERATE_AIR_QUALITY_LED_INDICATOR = {
    false,
    false,
    true,
    true,
    false,
    false
};

constexpr LEDIndicator UPPER_MODERATE_AIR_QUALITY_LED_INDICATOR = {
    false,
    false,
    false,
    true,
    true,
    false
};

constexpr LEDIndicator POOR_AIR_QUALITY_LED_INDICATOR = {
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

void manage_unacceptable_air_quality_level(unsigned long current_time_s, bool is_air_quality_acceptable);

#endif //AIR_QUALITY_MANAGER_H
