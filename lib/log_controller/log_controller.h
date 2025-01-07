/**
 * @file log_controller.h
 * @brief Provides logging functionality for the Air Quality Meter project.
 *
 * This header defines macros and functions that enable modular logging
 * for different modules within the system. It makes use of the ArduinoLog
 * library to perform logging at different levels (e.g., verbose, trace).
 *
 * @details The header contains constants for log messages, logging macros
 * for specific data types (e.g., integers, floats, booleans), and function
 * declarations for operations such as initializing the logging controller
 * and logging system states.
 */

#ifndef LOG_CONTROLLER_H
#define LOG_CONTROLLER_H

namespace LogController {
    /**
     * @def TRACE_LN_s
     * @brief Logs a string variable and its name.
     * @param variable The variable to log (type: char*).
     */
#define TRACE_LN_s(variable) Log.traceln("Variable: " #variable " == \"%s\"", variable)

    /**
     * @def TRACE_LN_S
     * @brief Logs a string variable stored in program memory (flash) with its name.
     * @param variable The variable to log (type: char*).
     */
#define TRACE_LN_S(variable) Log.traceln("Variable: " #variable " == \"%S\"", variable)

    /**
     * @def TRACE_LN_c
     * @brief Logs a single character variable and its name.
     * @param variable The variable to log (type: char).
     */
#define TRACE_LN_c(variable) Log.traceln("Variable: " #variable " == \"%c\"", variable)

    /**
     * @def TRACE_LN_C
     * @brief Logs a single character variable or its hex value if not printable.
     * @param variable The variable to log (type: char).
     */
#define TRACE_LN_C(variable) Log.traceln("Variable: " #variable " == \"%C\"", variable)

    /**
     * @def TRACE_LN_d
     * @brief Logs an integer variable and its name.
     * @param variable The variable to log (type: int).
     */
#define TRACE_LN_d(variable) Log.traceln("Variable: " #variable " == %d", variable)

    /**
     * @def TRACE_LN_l
     * @brief Logs a long integer variable and its name.
     * @param variable The variable to log (type: long).
     */
#define TRACE_LN_l(variable) Log.traceln("Variable: " #variable " == %l", variable)

    /**
     * @def TRACE_LN_u
     * @brief Logs an unsigned long variable and its name.
     * @param variable The variable to log (type: unsigned long).
     */
#define TRACE_LN_u(variable) Log.traceln("Variable: " #variable " == %u", variable)

    /**
     * @def TRACE_LN_x
     * @brief Logs an integer variable as a hexadecimal value.
     * @param variable The variable to log (type: int).
     */
#define TRACE_LN_x(variable) Log.traceln("Variable: " #variable " == %x", variable)

    /**
     * @def TRACE_LN_X
     * @brief Logs an integer variable as a hexadecimal value prefixed with "0x".
     * @param variable The variable to log (type: int).
     */
#define TRACE_LN_X(variable) Log.traceln("Variable: " #variable " == %X", variable)

    /**
     * @def TRACE_LN_b
     * @brief Logs an integer variable as a binary value.
     * @param variable The variable to log (type: int).
     */
#define TRACE_LN_b(variable) Log.traceln("Variable: " #variable " == %b", variable)

    /**
     * @def TRACE_LN_B
     * @brief Logs an integer variable as a binary value prefixed with "0b".
     * @param variable The variable to log (type: int).
     */
#define TRACE_LN_B(variable) Log.traceln("Variable: " #variable " == %B", variable)

    /**
     * @def TRACE_LN_t
     * @brief Logs a boolean variable as 't' or 'f'.
     * @param variable The variable to log (type: bool).
     */
#define TRACE_LN_t(variable) Log.traceln("Variable: " #variable " == \'%t\'", variable)

    /**
     * @def TRACE_LN_T
     * @brief Logs a boolean variable as "true" or "false".
     * @param variable The variable to log (type: bool).
     */
#define TRACE_LN_T(variable) Log.traceln("Variable: " #variable " == \'%T\'", variable)

    /**
     * @def TRACE_LN_F
     * @brief Logs a floating point variable and its name.
     * @param variable The variable to log (type: float).
     */
#define TRACE_LN_F(variable) Log.traceln("Variable: " #variable " == %F", variable)

    /**
     * @def TRACE_LN_D
     * @brief Logs a double precision floating point variable and its name.
     * @param variable The variable to log (type: double).
     */
#define TRACE_LN_D(variable) Log.traceln("Variable: " #variable " == %D", variable)

    constexpr char WELCOME_MESSAGE[] = "*           Welcome to the Air Quality Meter!           *";
    ///< Message displayed during system startup.

    constexpr char INIT[] = "initialized"; ///< Indicates a module has been successfully initialized.

    constexpr char LOG_CONTROLLER[] = "Log controller"; ///< Label for the Log Controller module.
    constexpr char DISPLAY_CONTROLLER[] = "Display controller"; ///< Label for the Display Controller module.
    constexpr char ACKNOWLEDGE_BUTTON[] = "Acknowledge button"; ///< Label for the Acknowledge Button in the system.
    constexpr char MUTE_BUTTON[] = "Mute button"; ///< Label for the Acknowledge Button in the system.
    constexpr char SENSOR_CONTROLLER[] = "Sensor controller"; ///< Label for the Sensor Controller module.
    constexpr char LED_ARRAY[] = "LED array"; ///< Label for the LED Array module.
    constexpr char MUTE_INDICATOR[] = "Mute indicator"; ///< Label for the Mute indicator (LED).
    constexpr char AUDIO_CONTROLLER[] = "Audio controller"; ///< Label for the Audio Controller module.

    constexpr char SYSTEM_READY[] = "System ready"; ///< Message logged when the system is ready to operate.

    constexpr char STATE[] = "Current State:"; ///< Label for the current system state.

    constexpr char LOOP_START[] = "Loop start"; ///< Message logged at the beginning of the main system loop.
    constexpr char LOOP_END[] = "Loop end"; ///< Message logged at the end of the main system loop.

    constexpr char LED_UPDATED[] = "LED array updated"; ///< Message indicating the LED array has been updated.
    constexpr char MUTE_INDICATOR_UPDATED[] = "Mute indicator updated";
    ///< Message indicating the Mute indicator has been updated.
    constexpr char DISPLAY_UPDATED[] = "Display updated"; ///< Message indicating the display module has been updated.
    constexpr char AUDIO_WARNING_ISSUED[] = "Audio warning issued"; ///< Message indicating an audio warning was issued.
    constexpr char STATE_UPDATED[] = "State updated"; ///< Message indicating the current state has been updated.
    constexpr char ACKNOWLEDGE_BUTTON_DEBOUNCED[] = "Acknowledge button debounced";
    ///< Message indicating the acknowledge button has been debounced.
    constexpr char ACKNOWLEDGE_BUTTON_PRESSED[] = "Acknowledge button pressed";
    ///< Message logged when the acknowledge button is pressed.
    constexpr char MUTE_BUTTON_DEBOUNCED[] = "Mute button debounced";
    ///< Message indicating the mute button has been debounced.
    constexpr char MUTE_BUTTON_PRESSED[] = "Mute button pressed";
    ///< Message logged when the mute button is pressed.

    constexpr char DELAY_TIME[] = "Delay time: "; ///< Prefix for displaying the delay time.

    constexpr char DIVIDING_LINE_WELCOME[] = "*********************************************************";
    ///< Divider for the welcome message.
    constexpr char DIVIDING_LINE_LOOP[] = "#########################################################";
    ///< Divider for the loop message logs.
    constexpr char DIVIDING_LINE_STATE[] = "---------------------------------------------------------";
    ///< Divider for the state-related logs.

    /**
     * @brief Initializes the logging system with a specified log level.
     *
     * @param log_level The desired log level (0-6) defining the verbosity of logs.
     */
    void initialize(int log_level);

    /**
     * @brief Logs a welcome message at system startup.
     */
    void log_welcome_message();

    /**
     * @brief Logs the initialization status of a specific module.
     *
     * @param module Name of the module being initialized.
     */
    void log_initialization(const char *module);

    /**
     * @brief Logs the system's current operational state.
     */
    void log_current_state();

    /**
     * @brief Logs the start of the system loop.
     */
    void log_loop_start();

    /**
     * @brief Logs the end of the system loop.
     */
    void log_loop_end();
}

#endif //LOG_CONTROLLER_H
