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

const String HIGH_AIR_QUALITY_DESCRIPTION = "High air quality"; ///< Text for IDA 1
const String MEDIUM_AIR_QUALITY_DESCRIPTION = "Medium air quality"; ///< Text for IDA 2
const String MODERATE_AIR_QUALITY_DESCRIPTION = "Moderate air quality"; ///< Text for IDA 3
const String POOR_AIR_QUALITY_DESCRIPTION = "Poor air quality"; ///< Text for IDA 4

constexpr LEDIndicator HIGH_AIR_QUALITY_LED_INDICATOR = {
    true, true, false, false, false, false
};

constexpr LEDIndicator MEDIUM_AIR_QUALITY_LED_INDICATOR = {
    false, true, true, false, false, false
};

constexpr LEDIndicator LOWER_MODERATE_AIR_QUALITY_LED_INDICATOR = {
    false, false, true, true, false, false
};

constexpr LEDIndicator UPPER_MODERATE_AIR_QUALITY_LED_INDICATOR = {
    false, false, false, true, true, false
};

constexpr LEDIndicator POOR_AIR_QUALITY_LED_INDICATOR = {
    false, false, false, false, true, true
};

const AirQualityRule HIGH_AIR_QUALITY_RULE = {
    HIGH_AIR_QUALITY_LEVEL,
    HIGH_AIR_QUALITY_LED_INDICATOR,
    HIGH_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_HIGH_AIR_QUALITY_PPM
};

const AirQualityRule MEDIUM_AIR_QUALITY_RULE = {
    MEDIUM_AIR_QUALITY_LEVEL,
    MEDIUM_AIR_QUALITY_LED_INDICATOR,
    MEDIUM_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_MEDIUM_AIR_QUALITY_PPM
};

const AirQualityRule LOWER_MODERATE_AIR_QUALITY_RULE = {
    LOWER_MODERATE_AIR_QUALITY_LEVEL,
    LOWER_MODERATE_AIR_QUALITY_LED_INDICATOR,
    MODERATE_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_MID_THRESHOLD_MODERATE_AIR_QUALITY_PPM
};

const AirQualityRule UPPER_MODERATE_AIR_QUALITY_RULE = {
    UPPER_MODERATE_AIR_QUALITY_LEVEL,
    UPPER_MODERATE_AIR_QUALITY_LED_INDICATOR,
    MODERATE_AIR_QUALITY_DESCRIPTION,
    true,
    CO2_UPPER_THRESHOLD_MODERATE_AIR_QUALITY_PPM
};

const AirQualityRule POOR_AIR_QUALITY_RULE = {
    POOR_AIR_QUALITY_LEVEL,
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
    return AIR_QUALITY_RULES[POOR_AIR_QUALITY_LEVEL];
}