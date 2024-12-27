#include <state.h>

constexpr unsigned int MAX_CO2_ABOVE_THRESHOLD_TIME_S = 3600;
///< Max time period allowed CO2 above threshold (seconds)

namespace WarningController {
    bool is_audio_warning_to_be_issued(const unsigned long time_since_co2_level_not_acceptable_s) {
        return time_since_co2_level_not_acceptable_s > MAX_CO2_ABOVE_THRESHOLD_TIME_S;
    }
}
