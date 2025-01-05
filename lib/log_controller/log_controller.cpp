/**
 * @file log_controller.cpp
 * @brief Implements the logging functionality for the Air Quality Meter project.
 *
 * This file defines methods to initialize logging, log system events, and
 * manage log prefixes and suffixes. It also provides helper functions to
 * format timestamps and log levels.
 */

#include <ArduinoLog.h>
#include <log_controller.h>
#include <state.h>

namespace LogController {
    /**
     * @brief Prints the prefix for each log message, including the timestamp and log level.
     *
     * @param _log_output The output stream to print to.
     * @param log_level The level of the log message.
     */
    void print_prefix(Print *_log_output, int log_level);

    /**
     * @brief Generates and prints the current timestamp for the log message.
     *
     * @param _log_output The output stream to print to.
     */
    void print_timestamp(Print *_log_output);

    /**
     * @brief Prints the log level for a log message (e.g., NOTICE, TRACE).
     *
     * @param _log_output The output stream to print to.
     * @param log_level The level of the log message.
     */
    void print_log_level(Print *_log_output, int log_level);

    /**
     * @brief Adds a suffix to each log message.
     *
     * @param _log_output The output stream to print to.
     * @param log_level The level of the log message.
     */
    void print_suffix(Print *_log_output, int log_level);

    constexpr unsigned int SERIAL_BAUD_RATE = 9600;
    ///< Defines the baud rate used for serial communication during debugging.

    void initialize(const int log_level) {
        Serial.begin(SERIAL_BAUD_RATE);
        while (!Serial && !Serial.available()) {
        }
        Log.setPrefix(print_prefix);
        Log.setSuffix(print_suffix);
        Log.begin(log_level, &Serial);
        Log.setShowLevel(false);
    }

    void log_welcome_message() {
        Log.noticeln(DIVIDING_LINE_WELCOME);
        Log.noticeln(WELCOME_MESSAGE);
        Log.noticeln(DIVIDING_LINE_WELCOME);
    }

    void log_initialization(const char *module) {
        char module_initialized[128];
        sprintf(module_initialized, "%s %s", module, INIT);
        Log.verboseln(module_initialized);
    }

    void log_current_state() {
        Log.traceln("%s", DIVIDING_LINE_STATE);
        Log.traceln("%s", STATE);
        TRACE_LN_u(AirQualityMeter::state.last_co2_below_threshold_time_s);
        TRACE_LN_d(AirQualityMeter::state.warning_counter);
        TRACE_LN_u(AirQualityMeter::state.last_co2_sensor_used_time_stamp_ms);
        Log.traceln("%s", DIVIDING_LINE_STATE);
    }

    void log_loop_start() {
        Log.traceln("%s", DIVIDING_LINE_LOOP);
        Log.traceln("%s", LOOP_START);
    }

    void log_loop_end() {
        log_current_state();
        Log.traceln(LOOP_END);
    }

    void print_prefix(Print *_log_output, const int log_level) {
        print_timestamp(_log_output);
        print_log_level(_log_output, log_level);
    }

    void print_timestamp(Print *_log_output) {
        // Division constants
        constexpr unsigned long MSECS_PER_SEC = 1000; ///< Number of milliseconds per second.
        constexpr unsigned long SECS_PER_MIN = 60; ///< Number of seconds per minute.
        constexpr unsigned long SECS_PER_HOUR = 3600; ///< Number of seconds per hour.
        constexpr unsigned long SECS_PER_DAY = 86400; ///< Number of seconds per day.

        // Total time
        const unsigned long msecs = millis(); ///< Total milliseconds elapsed since the program started.
        const unsigned long secs = msecs / MSECS_PER_SEC; ///< Total seconds elapsed since the program started.

        // Time in components
        const unsigned long milli_seconds = msecs % MSECS_PER_SEC; ///< Milliseconds component of the current time.
        const unsigned long seconds = secs % SECS_PER_MIN; ///< Seconds component of the current time.
        const unsigned long minutes = (secs / SECS_PER_MIN) % SECS_PER_MIN; ///< Minutes component of the current time.
        const unsigned long hours = (secs % SECS_PER_DAY) / SECS_PER_HOUR; ///< Hours component of the current time.

        // Time as string
        char timestamp[20]; ///< Buffer to store the formatted timestamp.
        sprintf(timestamp, "[%02lu:%02lu:%02lu.%03lu] ", hours, minutes, seconds, milli_seconds);
        _log_output->print(timestamp);
    }

    void print_log_level(Print *_log_output, const int log_level) {
        switch (log_level) {
            default:
            case 0: _log_output->print("[SILENT]  ");
                break;
            case 1: _log_output->print("[FATAL]   ");
                break;
            case 2: _log_output->print("[ERROR]   ");
                break;
            case 3: _log_output->print("[WARNING] ");
                break;
            case 4: _log_output->print("[NOTICE]  ");
                break;
            case 5: _log_output->print("[TRACE]   ");
                break;
            case 6: _log_output->print("[VERBOSE] ");
        }
    }

    void print_suffix(Print *_log_output, const int log_level) {
        _log_output->print("");
    }
}
