/**
 * @file    air_quality_manager.h
 * @brief   This file contains the function declarations for managing
 *          the air quality.
 */

#ifndef AIR_QUALITY_MANAGER_H
#define AIR_QUALITY_MANAGER_H

// String array constants.
constexpr char co2_prefix[] = "CO2: "; ///< Prefix to display CO2 value
constexpr char ppm_suffix[] = " ppm"; ///< Suffix to display a value with ppm as the unit
constexpr char high_air_quality_description[] = "High air quality"; ///< Text for IDA 1
constexpr char medium_air_quality_description[] = "Medium air quality"; ///< Text for IDA 2
constexpr char moderate_air_quality_description[] = "Moderate air quality"; ///< Text for IDA 3
constexpr char poor_air_quality_description[] = "Poor air quality"; ///< Text for IDA 4

// Constants for fix length of Strings.
constexpr size_t display_line_1_size = 16; ///< Maximum size for the first line of the LCD.
constexpr size_t display_line_2_size = 24; ///< Maximum size for the second line of the LCD.

// String variables
extern char display_line_1[display_line_1_size]; ///< first line to display on the LCD
extern char display_line_2[display_line_2_size]; ///< second line to display on the LCD

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
void manage_air_quality(int co2_measurement_ppm);

#endif //AIR_QUALITY_MANAGER_H
