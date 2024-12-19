/**
 * @file    air_quality_manager.h
 * @brief   This header file provides the definitions and interfaces for managing air quality levels,
 *          controlling associated LED indicators, and handling CO2 measurements in an air quality
 *          monitoring system.
 *
 * @details This file includes:
 *           - Definitions for structures representing LED indicators and air quality rules.
 *           - Function prototypes to evaluate air quality rules, update display outputs, and manage
 *             unacceptable air quality conditions.
 *
 *           The `AirQualityRule` structure maps CO2 levels to thresholds, descriptions, LED states,
 *           and acceptability statuses. The provided functions allow for determining air quality rules
 *           based on real-time CO2 measurements while controlling display and LED outputs accordingly.
 */

#ifndef AIR_QUALITY_MANAGER_H
#define AIR_QUALITY_MANAGER_H

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

/**
 * @struct  AirQualityRule
 * @brief   Represents the characteristics and thresholds for a specific air quality level.
 *
 * @details This structure defines a mapping between air quality levels and their associated attributes.
 *          It includes thresholds for CO2 measurements, descriptive labels, LED indicator states,
 *          and an acceptability status.
 */
struct AirQualityRule {
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

/**
 * @brief   Determines the air quality rule based on the provided CO2 measurement in ppm.
 *
 * @details This function evaluates the given CO2 measurement against predefined air quality rules
 *          and returns the corresponding rule. The rules define thresholds, descriptions, and
 *          LED indicator states for various air quality levels.
 *
 * @param   co2_measurement_ppm The CO2 concentration measurement in parts per million (ppm).
 *
 * @return  The air quality rule corresponding to the given CO2 measurement.
 */
AirQualityRule get_air_quality_rule(int co2_measurement_ppm);

/**
 * @brief   Updates the display with the air quality measurement and description.
 *
 * @details This function formats and combines CO2 measurement in ppm and its corresponding air
 *          quality description. It then outputs the results to the display device.
 *
 * @param co2_measurement_ppm The CO2 measurement in parts per million (ppm).
 * @param air_quality_description A textual description of the current air quality status.
 */
void update_display_air_quality_output(int co2_measurement_ppm, const String &air_quality_description);

/**
 * @brief   Updates the LED indicators to display the current air quality status.
 *
 * @details Adjusts the state of the LEDs based on the provided LEDIndicator structure,
 *          where each field represents the on/off status of a specific LED.
 *          This is used to visually represent air quality levels.
 *
 * @param led_indicator A constant reference to the LEDIndicator structure containing
 *                       the on/off states for each individual LED.
 */
void update_led_air_quality_output(const LEDIndicator &led_indicator);

/**
 * @brief Manages the response to unacceptable air quality levels over time.
 *
 * @details This function handles actions when air quality levels remain unacceptable for a prolonged period.
 *          It monitors the time since air quality was deemed unacceptable and issues audio warnings
 *          at defined intervals. If a maximum number of consecutive warnings is reached,
 *          the internal state is reset. The function also ensures safe handling of time calculations,
 *          including unsigned integer overflow conditions when calculating elapsed time.
 *
 * @param current_time_s Current timestamp in seconds.
 * @param is_air_quality_acceptable Boolean flag indicating whether the air quality is acceptable or not.
 */
void manage_unacceptable_air_quality_level(unsigned long current_time_s, bool is_air_quality_acceptable);

#endif //AIR_QUALITY_MANAGER_H
