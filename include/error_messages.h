/**
   * @file error_messages.h
   * @brief Centralized error message definitions for general and sensor-specific issues.
   *
   * @details This file organizes reusable error messages related to sensor conditions or
   * generic failures.
   */

#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

namespace GeneralError {
    // Generic error messages.
    constexpr char ERROR_MESSAGE_ROW_ONE[] = "Error";
    ///< Generic error message.
}

namespace SensorError {
    // Error messages for the sensor.
    constexpr char NOT_CONNECTED[] = "Sensor not connected";
    ///< Error message, which indicates, that the sensor is not connected.
    constexpr char MEASUREMENT_NOT_VALID[] = "Measurement not valid";
    ///< Error message, which indicates, that the measurement is not valid.
}

#endif //ERROR_MESSAGES_H
