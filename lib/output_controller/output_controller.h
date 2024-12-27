#ifndef OUTPUT_CONTROLLER_H
#define OUTPUT_CONTROLLER_H

#include <air_quality.h>

namespace OutputController {
    void reset_warning_state(unsigned long current_time_s);

    void update_warning_state_for_co2_level_not_acceptable(unsigned long current_time_s);
}

#endif //OUTPUT_CONTROLLER_H
