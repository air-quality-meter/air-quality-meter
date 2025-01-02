/**
 * @file    display_controller.cpp
 * @brief   This file contains the function definitions for managing the LCD1602 display.
 * @details Implements the functionality for initializing and interacting with the LCD1602
 *          display module, including the `initialize` and `output` functions.
 *          Used in the Air Quality Meter project for displaying messages such as status
 *          or air quality readings.
 */

#include <display_controller.h>
#include <pin_configuration.h>
#include <LiquidCrystal.h> // lib for LCD

namespace DisplayController {
    /**
     * @enum Columns
     * @brief Represents column indices for the LCD1602 display.
     * @details Defines constants used for specifying the cursor's column position on the LCD.
     */
    enum Columns : uint8_t {
        COLUMN_1, ///< The first column (index 0).
        NUMBER_OF_COLUMNS = DISPLAY_WIDTH ///< Total number of columns on the display.
    };

    /**
     * @enum Rows
     * @brief Represents row indices for the LCD1602 display.
     * @details Defines constants used for specifying the cursor's row position on the LCD.
     */
    enum Rows : uint8_t {
        ROW_1, ///< The first row (index 0).
        ROW_2, ///< The second row (index 1).
        NUMBER_OF_ROWS ///< Total number of rows on the display.
    };

    // Constants for welcoming messages
    constexpr int WELCOME_MESSAGE_TIME_MS = 2000; ///< Display duration for the welcome message, in milliseconds.
    constexpr char WELCOME_MESSAGE[] = "Air Quality Meter"; ///< Welcome message displayed on the first line.
    constexpr char INITIALIZING_MESSAGE[] = "Initializing..."; ///< Initialization message displayed on the second line.

    LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
    ///< LiquidCrystal library object for interacting with the LCD1602 module.

    void initialize() {
        lcd.begin(NUMBER_OF_COLUMNS, NUMBER_OF_ROWS); // Initialisiere das LCD mit 16 Zeichen und 2 Zeilen
        lcd.clear(); // delete the display content

        // display Welcome message
        lcd.setCursor(COLUMN_1, ROW_1); // first line
        lcd.print(WELCOME_MESSAGE);
        lcd.setCursor(COLUMN_1, ROW_2); // second line
        lcd.print(INITIALIZING_MESSAGE);

        delay(WELCOME_MESSAGE_TIME_MS); // show the message
        lcd.clear(); // clear the display content
    }

    void output(const char *line_1, const char *line_2) {
        lcd.clear(); // delete the display content

        // display line 1
        lcd.setCursor(COLUMN_1, ROW_1); // first line
        lcd.print(line_1);

        // display line 2
        lcd.setCursor(COLUMN_1, ROW_2); // second line
        lcd.print(line_2);
    }
}
