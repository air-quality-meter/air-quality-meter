#include <state.h>

namespace Co2LevelTimeTracker {
    unsigned long get_time_since_co2_level_not_acceptable_s(const unsigned long current_time_s) {
        return current_time_s - AirQualityMeter::state.last_co2_below_threshold_time_s;
        ///< Time delta since air quality is not acceptable.
        ///< @note As all time variables and constants are unsigned, a possible time overflow will still be handled correctly.
        ///< A potentially very high value for the variable last_co2_below_threshold_time_s of almost the maximum of the unsigned
        ///< long type still leads to a correct result of the subraction (current_time_s - last_co2_below_threshold_time_s) even
        ///< after an overflow of millis(), when current_time_s has a very small value again.
        ///< @see  https://en.cppreference.com/w/cpp/language/operator_arithmetic#:~:text=conversions%20are%20applied.-,Overflows,-Unsigned%20integer%20arithmetic
    }
}
