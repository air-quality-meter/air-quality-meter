#ifndef LOG_CONTROLLER_H
#define LOG_CONTROLLER_H

#include <Arduino.h>
#include <ArduinoLog.h>

namespace LogController {
    constexpr char INIT[] = "initialized";
    constexpr char FILE[] = "file";
    void initialize(int log_level);
}

#endif //LOG_CONTROLLER_H
