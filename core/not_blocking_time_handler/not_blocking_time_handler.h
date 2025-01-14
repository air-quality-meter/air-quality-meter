/**
 * @file not_blocking_time_handler.h
 * @brief Provides a function for non-blocking delays in milliseconds.
 *
 * This header file contains the declaration of a time handling utility 
 * that allows for non-blocking delays using the `wait_ms` function. 
 */

#ifndef NOT_BLOCKING_TIME_HANDLER_H
#define NOT_BLOCKING_TIME_HANDLER_H

namespace NotBlockingTimeHandler {
    /**
     * @brief Waits for a specified time in milliseconds without blocking critical system tasks.
     *
     * This function pauses execution for the given duration in milliseconds by
     * continuously monitoring elapsed time.
     *
     * @param waiting_time_ms The amount of time in milliseconds to wait.
     */
    void wait_ms(unsigned long waiting_time_ms);
}

#endif //NOT_BLOCKING_TIME_HANDLER_H
