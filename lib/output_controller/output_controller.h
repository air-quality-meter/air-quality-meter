/**
 * @file    output_controller.h
 * @brief   This header file provides the definitions and interfaces for managing air quality levels,
 *          controlling associated LED indicators, and handling CO2 measurements in an air quality
 *          monitoring system.
 *
 * @details This file includes:
 *           - Definitions for structures representing LED indicators and air quality levels.
 *           - Function prototypes to evaluate air quality levels, update display outputs, and manage
 *             unacceptable air quality conditions.
 *
 *           The `AirQualityLevel` structure maps CO2 levels to thresholds, descriptions, LED states,
 *           and acceptability statuses. The provided functions allow for determining air quality levels
 *           based on real-time CO2 measurements while controlling display and LED outputs accordingly.
 */

#ifndef OUTPUT_CONTROLLER_H
#define OUTPUT_CONTROLLER_H

#include <air_quality.h>

namespace OutputController {

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
    void manage_audio_warnings(unsigned long current_time_s, bool is_air_quality_acceptable);
}

#endif //OUTPUT_CONTROLLER_H
