#ifndef LOG_CONTROLLER_H
#define LOG_CONTROLLER_H

#include <Arduino.h>
#include <ArduinoLog.h>

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


    constexpr char INIT[] = "initialized";

    void initialize(int log_level);
}

#endif //LOG_CONTROLLER_H
