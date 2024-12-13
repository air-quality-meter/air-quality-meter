/**
 * @file    global_constants.h
 * @brief   This file contains the global constants used in the program.
 * @note    Air quality thresholds based on DIN EN 13779.
 * @see     https://www.umweltbundesamt.de/sites/default/files/medien/publikation/long/4113.pdf
 */

#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H

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

constexpr int max_consecutive_warnings = 5; ///< Max consecutive audio warnings before reset

constexpr unsigned long max_co2_above_threshold_time_s = 3600;
///< Max time period allowed CO2 above threshold (seconds)

constexpr unsigned long waiting_period_between_warnings_s = 60; ///< Time period between two warnings (seconds)

#endif //GLOBAL_CONSTANTS_H
