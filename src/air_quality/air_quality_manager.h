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

// String array constants.
constexpr char co2_prefix[] = "CO2: "; ///< Prefix to display CO2 value
constexpr char ppm_suffix[] = " ppm"; ///< Suffix to display a value with ppm as the unit
constexpr char high_air_quality_description[] = "High air quality"; ///< Text for IDA 1
constexpr char medium_air_quality_description[] = "Medium air quality"; ///< Text for IDA 2
constexpr char moderate_air_quality_description[] = "Moderate air quality"; ///< Text for IDA 3
constexpr char poor_air_quality_description[] = "Poor air quality"; ///< Text for IDA 4

// Constants for fix length of Strings.
constexpr size_t display_line_1_size = 16;
///< Maximum size for the text to show on the first line of the LCD1602 Module.
constexpr size_t display_line_2_size = 24;
///< Maximum size for the text to show on the second line of the LCD1602 Module.

constexpr int NO_UPPER_LIMIT = -1;

struct DisplayLines {
    char line_1[display_line_1_size] = ""; ///< first line to display on the LCD1602 Module
    char line_2[display_line_2_size] = ""; ///< second line to display on the LCD1602 Module
};

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
    const AirQualityLevel air_quality_level;
    const char *description;
    ///< Pointer to a description char array (string). That allows storing and referencing a text description for
    ///< an air quality level without copying the entire string
    const LEDIndicator led_indicator;
    const bool is_level_acceptable;
    ///< If level is not acceptable, there are further steps following.
    const int upper_threshold_ppm;
    ///< Upper co2 threshold for level; -1 indicates "no upper limit" (poor air quality)
};

extern LEDIndicator air_quality_led_indicators[];

extern AirQualityRule air_quality_rules[];

const AirQualityRule *get_air_quality_rule(int co2_measurement_ppm);

/**
 * @brief   Visually outputs air quality to LCD and LED indicators.
 * @details Sends CO2 value and a description of the air quality to display_output() and
 *          sets the LED indicators accordingly.
 *              - high indoor air quality: Both green LEDs light up.
 *              - medium indoor air quality: One green and one yellow LED (adjacent to each other) light up.
 *              - lower half of moderate indoor air quality: Both yellow LEDs light up.
 *              - upper half of moderate indoor air quality: One yellow and one red LED (adjacent to each other) light up.
 *              - poor indoor air quality: Both red LEDs light up.
 * @param co2_measurement_ppm CO2 value.
 */
void manage_air_quality(int co2_measurement_ppm, const AirQualityRule *air_quality_rule);

#endif //AIR_QUALITY_MANAGER_H
