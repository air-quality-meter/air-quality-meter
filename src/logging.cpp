#include <Arduino.h>
#include <logging.h>
#include <config.h>
#include <stdarg.h>

void log_message(const LogLevel log_level, const char *tag, const char *format) {
  if (log_level <= LOG_LEVEL) {
    switch (log_level) {
      case LogLevel::ERROR:   Serial.println("[ERROR  ] "); break;
      case LogLevel::WARNING: Serial.println("[WARNING] "); break;
      case LogLevel::INFO:    Serial.println("[INFO   ] "); break;
      case LogLevel::DEBUG:   Serial.println("[DEBUG  ] "); break;
      default: return;
    }

    Serial.print(tag);
    Serial.print(": ");

    // Format message (with potential arguments for formatted strings)
    char buffer[128]; // Size of buffer
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // Print the formatted string
    Serial.println(buffer);
  }
}