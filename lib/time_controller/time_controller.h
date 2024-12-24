/**
 * @file  time_controller.h
 * @brief Header file provides time-related utility functions for system operations.
 */

#ifndef TIME_CONTROLLER_H
#define TIME_CONTROLLER_H

namespace TimeController {
    /**
     * @brief   Retrieves the elapsed time since the board was powered on.
     * @details Converts the internal millis() value from milliseconds to seconds to provide a time reference.
     * @return  The elapsed time since the board was powered on in seconds.
     */
    unsigned long get_current_time_in_s();
}

#endif //TIME_CONTROLLER_H
