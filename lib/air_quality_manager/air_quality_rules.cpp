/**
 * @file    air_quality_rules.cpp
 * @brief   Implementation of air quality rules for categorizing indoor air quality based on CO2 levels.
 * @details This file contains constants, configurations, and rules for determining indoor air
 *          quality levels based on CO2 concentration in parts per million (ppm) using predefined thresholds
 *          as per DIN EN 13779 specifications. It also provides LED indicator configurations for each air
 *          quality category and a function to determine the corresponding air quality rule based
 *          on measured CO2 levels.
 */

#include <Arduino.h>
#include "air_quality_manager.h"

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
///< Indicates that there is no upper limit for a given air quality rule.

const String HIGH_AIR_QUALITY_DESCRIPTION = "High air quality"; ///< Description for high air quality level.
const String MEDIUM_AIR_QUALITY_DESCRIPTION = "Medium air quality"; ///< Description for medium air quality level.
const String MODERATE_AIR_QUALITY_DESCRIPTION = "Moderate air quality"; ///< Description for moderate air quality level.
const String POOR_AIR_QUALITY_DESCRIPTION = "Poor air quality"; ///< Description for poor air quality level.

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

const AirQualityRule HIGH_AIR_QUALITY_RULE = {
    HIGH_AIR_QUALITY_LED_INDICATOR,
    HIGH_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_HIGH_AIR_QUALITY_PPM
};

const AirQualityRule MEDIUM_AIR_QUALITY_RULE = {
    MEDIUM_AIR_QUALITY_LED_INDICATOR,
    MEDIUM_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_MEDIUM_AIR_QUALITY_PPM
};

const AirQualityRule LOWER_MODERATE_AIR_QUALITY_RULE = {
    LOWER_MODERATE_AIR_QUALITY_LED_INDICATOR,
    MODERATE_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_MID_THRESHOLD_MODERATE_AIR_QUALITY_PPM
};

const AirQualityRule UPPER_MODERATE_AIR_QUALITY_RULE = {
    UPPER_MODERATE_AIR_QUALITY_LED_INDICATOR,
    MODERATE_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_MODERATE_AIR_QUALITY_PPM
};

const AirQualityRule POOR_AIR_QUALITY_RULE = {
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
    return POOR_AIR_QUALITY_RULE;
}
