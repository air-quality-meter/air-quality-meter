#ifndef LOG_CONTROLLER_H
#define LOG_CONTROLLER_H

namespace LogController {
#define TRACE_LN_s(variable) Log.traceln("Variable: " #variable " == \"%s\"", variable) ///< Trace variable with name as string (char*).


#define TRACE_LN_S(variable) Log.traceln("Variable: " #variable " == \"%S\"", variable) ///< Trace variable with name as string from flash.


#define TRACE_LN_c(variable) Log.traceln("Variable: " #variable " == \"%c\"", variable) ///< Trace variable with name as single character.


#define TRACE_LN_C(variable) Log.traceln("Variable: " #variable " == \"%C\"", variable) ///< Trace variable with name as single character or as hexadecimal value (prefixed by `0x`) if not a printable character.


#define TRACE_LN_d(variable) Log.traceln("Variable: " #variable " == %d", variable) ///< Trace variable with name as integer.


#define TRACE_LN_l(variable) Log.traceln("Variable: " #variable " == %l", variable) ///< Trace variable with name as long.


#define TRACE_LN_u(variable) Log.traceln("Variable: " #variable " == %u", variable) ///< Trace variable with name as unsigned long.


#define TRACE_LN_x(variable) Log.traceln("Variable: " #variable " == %x", variable) ///< Trace variable with name as hexadecimal value.


#define TRACE_LN_X(variable) Log.traceln("Variable: " #variable " == %X", variable) ///< Trace variable with name as hexadecimal value prefixed by `0x` and leading zeros.


#define TRACE_LN_b(variable) Log.traceln("Variable: " #variable " == %b", variable) ///< Trace variable with name as binary value.


#define TRACE_LN_B(variable) Log.traceln("Variable: " #variable " == %B", variable) ///< Trace variable with name as binary value prefixed by `0b`.


#define TRACE_LN_t(variable) Log.traceln("Variable: " #variable " == \'%t\'", variable) ///< Trace variable with name as boolean value "t" or "f".


#define TRACE_LN_T(variable) Log.traceln("Variable: " #variable " == \'%T\'", variable) ///< Trace variable with name as boolean value "true" or "false".


#define TRACE_LN_F(variable) Log.traceln("Variable: " #variable " == %F", variable) ///< Trace variable with name as floating point.


#define TRACE_LN_D(variable) Log.traceln("Variable: " #variable " == %D", variable) ///< Trace variable with name as double.


    constexpr char WELCOME_MESSAGE[] = "*           Welcome to the Air Quality Meter!           *";
    constexpr char INIT[] = "initialized";
    constexpr char INIT_FAILED[] = "initialization failed";

    constexpr char LOG_CONTROLLER[] = "Log controller";
    constexpr char DISPLAY_CONTROLLER[] = "Display controller";
    constexpr char ACKNOWLEDGE_BUTTON[] = "Acknowledge button";
    constexpr char SENSOR_CONTROLLER[] = "Sensor controller";
    constexpr char LED_ARRAY[] = "LED array";
    constexpr char AUDIO_CONTROLLER[] = "Audio controller";

    constexpr char SYSTEM_READY[] = "System ready";

    constexpr char STATE[] = "Current State:";

    constexpr char LOOP_START[] = "Loop start";
    constexpr char LOOP_END[] = "Loop end";

    constexpr char LED_UPDATED[] = "LED array updated";
    constexpr char DISPLAY_UPDATED[] = "Display updated";
    constexpr char AUDIO_WARNING_ISSUED[] = "Audio warning issued";
    constexpr char STATE_UPDATED[] = "State updated";
    constexpr char ACKNOWLEDGE_BUTTON_DEBOUNCED[] = "Acknowledge button debounced";
    constexpr char ACKNOWLEDGE_BUTTON_PRESSED[] = "Acknowledge button pressed";

    constexpr char DELAY_TIME[] = "Delay time: ";

    constexpr char DIVIDING_LINE_WELCOME[] = "*********************************************************";
    constexpr char DIVIDING_LINE_LOOP[] = "#########################################################";
    constexpr char DIVIDING_LINE_STATE[] = "---------------------------------------------------------";

    void initialize(int log_level);

    void log_welcome_message();

    void log_initialization(const char *module);

    void log_initialization_failed(const char *module);

    void log_current_state();

    void log_loop_start();

    void log_loop_end();
}

#endif //LOG_CONTROLLER_H
