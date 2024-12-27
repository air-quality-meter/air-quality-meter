#ifndef WARNING_CONTROLLER_H
#define WARNING_CONTROLLER_H

namespace WarningController {
    bool is_audio_warning_to_be_issued(unsigned long time_since_co2_level_not_acceptable_s);
}

#endif //WARNING_CONTROLLER_H
