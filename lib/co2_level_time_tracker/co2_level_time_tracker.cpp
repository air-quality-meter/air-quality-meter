/**
 * @file co2_level_time_tracker.cpp
 * @brief Implementation of CO2 level time tracker functionality.
 * @details This source file provides the definition of functions involved in calculating
 *          how long the CO2 level has been above the acceptable threshold.
 */

#include <state.h>

namespace Co2LevelTimeTracker {

    unsigned long get_time_since_co2_level_not_acceptable_s(const unsigned long current_time_s) {
        return current_time_s - AirQualityMeter::state.last_co2_below_threshold_time_s;
        ///< Time since the last acceptable CO2 level, adjusted for overflow.
    }
}
