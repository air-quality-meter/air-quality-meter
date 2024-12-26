/**
 * @file    led_array.h
 * @brief   This file contains the function declarations for controlling the LEDs.
 */

#ifndef LED_ARRAY_H
#define LED_ARRAY_H

namespace LedArray {
    /**
     * @struct  Pattern
     * @brief   Represents the state of LED indicators used to display air quality levels.
     *
     * @details This structure defines six boolean flags corresponding to the on/off state of different LEDs.
     *          Multiple LEDs can be turned on simultaneously.
     */
    struct Pattern {
        bool is_green_led_1_on; ///< Indicates if the first green LED is ON (true) or OFF (false).
        bool is_green_led_2_on; ///< Indicates if the second green LED is ON (true) or OFF (false).
        bool is_yellow_led_1_on; ///< Indicates if the first yellow LED is ON (true) or OFF (false).
        bool is_yellow_led_2_on; ///< Indicates if the second yellow LED is ON (true) or OFF (false).
        bool is_red_led_1_on; ///< Indicates if the first red LED is ON (true) or OFF (false).
        bool is_red_led_2_on; ///< Indicates if the second red LED is ON (true) or OFF (false).
    };
    /**
     * @brief   Initialize LED PINs (Output)
     */
    void initialize();

    /**
     * @brief   Controls the LED indicators.
     * @details Activates LEDs according to the given parameters.
     *          HIGH and LOW as second parameters for digitalWrite() are provided as booleans.
     *          This is valid, because HIGH and LOW are the same as true and false, as well as 1 and 0.
     * @see     https://reference.arduino.cc/reference/en/language/variables/constants/highlow/?_gl=1*12oo2pw*_up*MQ..*_ga*NTMxMjcxOTAwLjE3MzM5NTQ2Mzc.*_ga_NEXN8H46L5*MTczMzk1NDYzNi4xLjEuMTczMzk1NDcxNC4wLjAuMTM1MTQzNjcxNw..
     * @param pattern led pattern
     */
    void output(Pattern pattern);
}

#endif //LED_ARRAY_H
