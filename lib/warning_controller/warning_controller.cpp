#include <state.h>

unsigned long get_time_since_co2_level_not_acceptable_s(unsigned long current_time_s);

constexpr unsigned int MAX_CO2_ABOVE_THRESHOLD_TIME_S = 3600;
///< Max time period allowed CO2 above threshold (seconds)

namespace WarningController {
    bool is_audio_warning_to_be_issued(const unsigned long current_time_s) {
        const unsigned long time_since_co2_level_not_acceptable_s = get_time_since_co2_level_not_acceptable_s(
            current_time_s);
        return time_since_co2_level_not_acceptable_s > MAX_CO2_ABOVE_THRESHOLD_TIME_S;
    }
}

unsigned long get_time_since_co2_level_not_acceptable_s(const unsigned long current_time_s) {
    return current_time_s - AirQualityMeter::state.last_co2_below_threshold_time_s;
    ///< Time delta since air quality is not acceptable.
    ///< @note As all time variables and constants are unsigned, a possible time overflow will still be handled correctly.
    ///< A potentially very high value for the variable last_co2_below_threshold_time_s of almost the maximum of the unsigned
    ///< long type still leads to a correct result of the subraction (current_time_s - last_co2_below_threshold_time_s) even
    ///< after an overflow of millis(), when current_time_s has a very small value again.
    ///< @see  https://en.cppreference.com/w/cpp/language/operator_arithmetic#:~:text=conversions%20are%20applied.-,Overflows,-Unsigned%20integer%20arithmetic
}
