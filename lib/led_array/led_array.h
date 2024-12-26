/**
 * @file    led_array.h
 * @brief   This file contains the function declarations for controlling the LEDs.
 */

#ifndef LED_ARRAY_H
#define LED_ARRAY_H

#include <led_patterns.h>

namespace LedArray {
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
    void output(LedPattern::Pattern pattern);
}

#endif //LED_ARRAY_H
