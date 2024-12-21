/**
 * @file  system_time.h
 * @brief Header file provides time-related utility functions for system operations.
 */

#ifndef SYSTEM_TIME_H
#define SYSTEM_TIME_H

/**
 * @brief   Retrieves the elapsed time since the board was powered on.
 * @details Converts the internal millis() value from milliseconds to seconds to provide a time reference.
 * @return  The elapsed time since the board was powered on in seconds.
 */
unsigned long get_current_time_in_s();

#endif //SYSTEM_TIME_H
