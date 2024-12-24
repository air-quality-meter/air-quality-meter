#ifndef AIR_QUALITY_LEVEL_H
#define AIR_QUALITY_LEVEL_H

#include <Arduino.h>

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
///< Indicates that there is no upper limit for a given air quality level.

const String HIGH_AIR_QUALITY_DESCRIPTION = "High air quality"; ///< Description for high air quality level.
const String MEDIUM_AIR_QUALITY_DESCRIPTION = "Medium air quality"; ///< Description for medium air quality level.
const String MODERATE_AIR_QUALITY_DESCRIPTION = "Moderate air quality"; ///< Description for moderate air quality level.
const String POOR_AIR_QUALITY_DESCRIPTION = "Poor air quality"; ///< Description for poor air quality level.

/**
 * @struct  LEDIndicator
 * @brief   Represents the state of LED indicators used to display air quality levels.
 *
 * @details This structure defines six boolean flags corresponding to the on/off state of different LEDs.
 *          Multiple LEDs can be turned on simultaneously to indicate an air quality status.
 */
struct LEDIndicator {
    bool is_green_led_1_on; ///< Indicates if the first green LED is ON (true) or OFF (false).
    bool is_green_led_2_on; ///< Indicates if the second green LED is ON (true) or OFF (false).
    bool is_yellow_led_1_on; ///< Indicates if the first yellow LED is ON (true) or OFF (false).
    bool is_yellow_led_2_on; ///< Indicates if the second yellow LED is ON (true) or OFF (false).
    bool is_red_led_1_on; ///< Indicates if the first red LED is ON (true) or OFF (false).
    bool is_red_led_2_on; ///< Indicates if the second red LED is ON (true) or OFF (false).
};

constexpr LEDIndicator HIGH_AIR_QUALITY_LED_INDICATOR = {true, true, false, false, false, false};
///< LED indicator state for high air quality (both green LEDs ON).

constexpr LEDIndicator MEDIUM_AIR_QUALITY_LED_INDICATOR = {false, true, true, false, false, false};
///< LED indicator state for medium air quality (one green and one yellow LED ON).

constexpr LEDIndicator LOWER_MODERATE_AIR_QUALITY_LED_INDICATOR = {false, false, true, true, false, false};
///< LED indicator state for lower part of moderate air quality (both yellow LEDs ON).

constexpr LEDIndicator UPPER_MODERATE_AIR_QUALITY_LED_INDICATOR = {false, false, false, true, true, false};
///< LED indicator state for upper part of moderate air quality (one yellow and one red LED ON).

constexpr LEDIndicator POOR_AIR_QUALITY_LED_INDICATOR = {false, false, false, false, true, true};
///< LED indicator state for poor air quality (both red LEDs ON).

/**
 * @struct  AirQualityLevel
 * @brief   Represents the characteristics and thresholds for a specific air quality level.
 *
 * @details This structure defines a mapping between air quality levels and their associated attributes.
 *          It includes thresholds for CO2 measurements, descriptive labels, LED indicator states,
 *          and an acceptability status.
 */
struct AirQualityLevel {
    LEDIndicator led_indicator;
    ///< Represents the state of LED indicators used to display air quality levels.
    String description;
    ///< A string that provides a description of the air quality level.
    bool is_level_acceptable;
    ///< indicating whether the air quality level is considered acceptable (true) or not (false).
    int upper_threshold_ppm;
    ///< Specifies the upper CO2 threshold (in parts per million) for this air quality level. A value of -1
    ///< indicates no upper limit, typically representing the poorest air quality.
};

const AirQualityLevel HIGH_AIR_QUALITY_LEVEL = {
    HIGH_AIR_QUALITY_LED_INDICATOR,
    HIGH_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_HIGH_AIR_QUALITY_PPM
};

const AirQualityLevel MEDIUM_AIR_QUALITY_LEVEL = {
    MEDIUM_AIR_QUALITY_LED_INDICATOR,
    MEDIUM_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_MEDIUM_AIR_QUALITY_PPM
};

const AirQualityLevel LOWER_MODERATE_AIR_QUALITY_LEVEL = {
    LOWER_MODERATE_AIR_QUALITY_LED_INDICATOR,
    MODERATE_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_MID_THRESHOLD_MODERATE_AIR_QUALITY_PPM
};

const AirQualityLevel UPPER_MODERATE_AIR_QUALITY_LEVEL = {
    UPPER_MODERATE_AIR_QUALITY_LED_INDICATOR,
    MODERATE_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_MODERATE_AIR_QUALITY_PPM
};

const AirQualityLevel POOR_AIR_QUALITY_LEVEL = {
    POOR_AIR_QUALITY_LED_INDICATOR,
    POOR_AIR_QUALITY_DESCRIPTION,
    false,
    NO_UPPER_LIMIT // No upper limit for poor air quality.
};

const AirQualityLevel AIR_QUALITY_LEVELS[] = {
    HIGH_AIR_QUALITY_LEVEL,
    MEDIUM_AIR_QUALITY_LEVEL,
    LOWER_MODERATE_AIR_QUALITY_LEVEL,
    UPPER_MODERATE_AIR_QUALITY_LEVEL,
    POOR_AIR_QUALITY_LEVEL
};

#endif //AIR_QUALITY_LEVEL_H
