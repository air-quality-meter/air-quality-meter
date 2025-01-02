/**
 * @file warning_controller.h
 * @brief Header file for the WarningController namespace.
 *
 * This file includes declarations of functions that manage warning logic
 * based on CO2 threshold exceedance. It serves as the interface for
 * implementing warning controllers.
 */

#ifndef WARNING_CONTROLLER_H
#define WARNING_CONTROLLER_H

namespace WarningController {
    /**
     * @brief Determines if an audio warning should be issued.
     *
     * @details This function evaluates whether an audio alert is necessary
     * based on the time elapsed since CO2 levels have been unacceptable.
     *
     * @param time_since_co2_level_not_acceptable_s Time in seconds that CO2
     *                                              levels have been above the
     *                                              acceptable threshold.
     * @return `true` if an audio warning should be issued, `false` otherwise.
     */
    bool is_audio_warning_to_be_issued(unsigned long time_since_co2_level_not_acceptable_s);
}

#endif //WARNING_CONTROLLER_H
