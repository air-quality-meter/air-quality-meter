/**
 * @file display.h
 * @brief This file contains the function declarations for the display.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @brief   Initializes the display module.
 * @details TODO: Write some more details
 */
void initialize_display();

/**
 * @brief   Outputs text to the LCD1602 Module.
 * @details Updates the connected display module to display the provided text on two lines.
 *          Display used: LCD1602 Module (with pin header)
 *          This function takes pointers to string arrays as parameters to avoid unnecessary
 *          copying of the data, improving performance and reducing memory usage.
 *          Call by pointer. The use of const prevents mutating the strings (char arrays).
 * @param line_1 Pointer to the text to display on the first line of the LCD1602 Module.
 * @param line_2 Pointer to the text to display on the second line of the LCD1602 Module.
 */
void display_out(const String &line_1, const String &line_2);

#endif //DISPLAY_H
