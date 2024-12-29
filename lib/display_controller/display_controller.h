/**
 * @file display_controller.h
 * @brief This file contains the function declarations for the display.
 */

#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <Arduino.h>

namespace DisplayController {
    /**
     * @brief   Initializes the LCD1602 Module.
     * @details Prepares the connected LCD1602 display module for operation by configuring its
     *          dimensions (16 characters, 2 lines) and clearing any existing content.
     *          Displays an initialization message for 2 seconds to indicate system readiness.
     *          Display used: LCD1602 Module (with pin header).
     *          This function should be called during the setup phase of the Arduino program.
     */
    void initialize();


    /**
     * @brief   Outputs text to the LCD1602 Module.
     * @details Updates the connected display module to display the provided text on two lines.
     *          Display used: LCD1602 Module (with pin header).
     *          The function clears the display before writing new content to avoid residual text.
     *          It accepts text as `const String&` parameters to improve performance by avoiding
     *          unnecessary copying and to ensure immutability of the provided data.
     * @param line_1 Reference to the text to display on the first line of the LCD1602 Module.
     * @param line_2 Reference to the text to display on the second line of the LCD1602 Module.
     */
    void output(const char *line_1, const char *line_2);
}

#endif //DISPLAY_CONTROLLER_H
