#ifndef WARNING_STATE_CONTROLLER_H
#define WARNING_STATE_CONTROLLER_H

namespace WarningStateController {
    void reset_warning_state(unsigned long current_time_s);

    void update_warning_state_for_co2_level_not_acceptable(unsigned long current_time_s);
}
#endif //WARNING_STATE_CONTROLLER_H
