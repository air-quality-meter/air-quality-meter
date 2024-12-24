/**
 * @file    led_controller.h
 * @brief   This file contains the function declarations for controlling the LEDs.
 */

#ifndef LEDS_CONTROLLER_H
#define LEDS_CONTROLLER_H

namespace LedController {
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
     * @param is_green_led_1_on Is the green LED 1 on?
     * @param is_green_led_2_on  Is the green LED 2 on?
     * @param is_yellow_led_1_on  Is the yellow LED 1 on?
     * @param is_yellow_led_2_on  Is the yellow LED 2 on?
     * @param is_red_led_1_on  Is the red LED 1 on?
     * @param is_red_led_2_on  Is the red LED 2 on?
     */
    void output(bool is_green_led_1_on,
                bool is_green_led_2_on,
                bool is_yellow_led_1_on,
                bool is_yellow_led_2_on,
                bool is_red_led_1_on,
                bool is_red_led_2_on);
}

#endif //LEDS_CONTROLLER_H
