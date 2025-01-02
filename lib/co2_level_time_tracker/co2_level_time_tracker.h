/**
 * @file co2_level_time_tracker.h
 * @brief Header file for CO2 level time tracker functionality.
 * @details This module provides functionality to calculate the time since the CO2 level was not acceptable.
 */

#ifndef CO2_LEVEL_TIME_TRACKER_H
#define CO2_LEVEL_TIME_TRACKER_H

namespace Co2LevelTimeTracker {
    /**
     * @brief Computes the time elapsed since the CO2 level was last acceptable.
     * @details This function calculates the time difference between `current_time_s` and a
     *          previously stored timestamp (`last_co2_below_threshold_time_s`) that records
     *          the last acceptable CO2 level time. The implementation ensures correctness, even
     *          when millis() overflow occurs.
     *          For details about unsigned arithmetic overflow, check the C++ standard documentation.
     * @param current_time_s The current time in seconds (unsigned long).
     * @return Elapsed time in seconds (unsigned long) since the CO2 level was last below the threshold.
     * @see https://en.cppreference.com/w/cpp/language/operator_arithmetic#:~:text=conversions%20are%20applied.-,Overflows,-Unsigned%20integer%20arithmetic
     */
    unsigned long get_time_since_co2_level_not_acceptable_s(unsigned long current_time_s);
}

#endif //CO2_LEVEL_TIME_TRACKER_H
