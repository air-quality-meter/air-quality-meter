#include <Arduino.h>
#include <mute_indicator.h>
#include <pin_configuration.h>
#include <ArduinoLog.h>
#include <log_controller.h>

namespace MuteIndicator {
    void initialize() {
        pinMode(BLUE_PIN, OUTPUT);
    }

    void indicate_system_mute(const bool is_mute) {
        digitalWrite(BLUE_PIN, is_mute);
        Log.verboseln(LogController::MUTE_INDICATOR_UPDATED);
    }
}
