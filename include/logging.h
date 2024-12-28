#ifndef LOGGING_H
#define LOGGING_H

#include <Arduino.h>

enum LogLevel : byte {
    NONE, ///< Disable all logging.
    ERROR, ///< For critical errors.
    WARNING, ///< For warnings.
    INFO, ///< For informational and debugging logs.
    DEBUG ///< For detailed debugging (most verbose) logs.
};

void log_message(LogLevel log_level, const char *tag, const char *format, ...);

#define LOG_ERROR(  tag, ...) log_message(LogLevel::ERROR,    tag, __VA_ARGS__)
#define LOG_WARNING(tag, ...) log_message(LogLevel::WARNING,  tag, __VA_ARGS__)
#define LOG_INFO(   tag, ...) log_message(LogLevel::INFO,     tag, __VA_ARGS__)
#define LOG_DEBUG(  tag, ...) log_message(LogLevel::DEBUG,    tag, __VA_ARGS__)

#endif //LOGGING_H
