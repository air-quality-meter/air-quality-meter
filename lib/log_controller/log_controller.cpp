#include <ArduinoLog.h>
#include <log_controller.h>
#include <state.h>

void print_prefix(Print *_log_output, int log_level);

void print_timestamp(Print *_log_output);

void print_log_level(Print *_log_output, int log_level);

void print_suffix(Print *_log_output, int log_level);

constexpr unsigned int SERIAL_BAUD_RATE = 9600;
///< Baud rate for serial communication for debugging

namespace LogController {
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
}

void print_prefix(Print *_log_output, const int log_level) {
    print_timestamp(_log_output);
    print_log_level(_log_output, log_level);
}

void print_timestamp(Print *_log_output) {
    // Division constants
    constexpr unsigned long MSECS_PER_SEC = 1000;
    constexpr unsigned long SECS_PER_MIN = 60;
    constexpr unsigned long SECS_PER_HOUR = 3600;
    constexpr unsigned long SECS_PER_DAY = 86400;

    // Total time
    const unsigned long msecs = millis();
    const unsigned long secs = msecs / MSECS_PER_SEC;

    // Time in components
    const unsigned long milli_seconds = msecs % MSECS_PER_SEC;
    const unsigned long seconds = secs % SECS_PER_MIN;
    const unsigned long minutes = (secs / SECS_PER_MIN) % SECS_PER_MIN;
    const unsigned long hours = (secs % SECS_PER_DAY) / SECS_PER_HOUR;

    // Time as string
    char timestamp[20];
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
