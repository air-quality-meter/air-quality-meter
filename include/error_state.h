#ifndef ERROR_STATE_H
#define ERROR_STATE_H

#include <Arduino.h>
#include <led_pattern.h>

const String ERROR_MESSAGE_LINE_ONE = "Error";
namespace SensorError {
    const String TEXT = "Sensor error";
    constexpr LedPattern::Pattern LED_PATTERN = {true, true, true, true, true, true};
}

#endif //ERROR_STATE_H
