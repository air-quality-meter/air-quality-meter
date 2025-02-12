/**
 * @file    acknowledge_button.h
 * @brief   This file contains the function declarations for acknowledge button functions.
 */

#ifndef ACKNOWLEDGE_BUTTON_H
#define ACKNOWLEDGE_BUTTON_H

namespace AcknowledgeButton {
    /**
     * @brief   Initializes acknowledge button.
     * @details Initializes interrupt service routine for acknowledge button pin.
     *          Device reacts on pressing acknowledge button (rising).
     */
    void initialize();

    /**
     * @brief   Resets last_co2_below_threshold_time_s and warning_counter.
     * @details Resets the timestamp of the last CO2 measurement that was below the threshold
     *          and the counter for consecutive warnings.
     */
    void acknowledge_warning();
}


#endif //ACKNOWLEDGE_BUTTON_H
