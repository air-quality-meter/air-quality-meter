/**
 * @file display.h
 * @brief This file contains the function declarations for the display.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @brief   Initializes the display module.
 */
void initialize_display();

/**
 * @brief   Outputs text to the LCD.
 * @details Updates the connected display module to display the provided text on two lines.
 *          Display used: LCD1602 Module (with pin header)
 *          This function takes pointers to string arrays as parameters to avoid unnecessary
 *          copying of the data, improving performance and reducing memory usage.
 *          Call by pointer. The use of const prevents mutating the strings (char arrays).
 * @param line_1 Pointer to the text to display on the first line of the LCD.
 * @param line_2 Pointer to the text to display on the second line of the LCD.
 */
void display_out(const char *line_1, const char *line_2);

#endif //DISPLAY_H
