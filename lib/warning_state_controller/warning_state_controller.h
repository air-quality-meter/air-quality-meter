#ifndef WARNING_STATE_CONTROLLER_H
#define WARNING_STATE_CONTROLLER_H

namespace WarningStateController {
    void reset(unsigned long current_time_s);

    void update_for_co2_level_not_acceptable(unsigned long current_time_s);
}
#endif //WARNING_STATE_CONTROLLER_H
