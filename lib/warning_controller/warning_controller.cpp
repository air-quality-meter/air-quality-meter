/**
 * @file warning_controller.cpp
 * @brief Implementation of the WarningController namespace.
 *
 * Contains the implementation of warning logic based on CO2 exceedance time.
 */

namespace WarningController {
    constexpr unsigned int MAX_CO2_ABOVE_THRESHOLD_TIME_S = 3600;
    ///< The maximum duration (in seconds) for CO2 levels to remain above the threshold
    ///< before triggering a warning.

    bool is_audio_warning_to_be_issued(const unsigned long time_since_co2_level_not_acceptable_s) {
        return time_since_co2_level_not_acceptable_s > MAX_CO2_ABOVE_THRESHOLD_TIME_S;
    }
}
