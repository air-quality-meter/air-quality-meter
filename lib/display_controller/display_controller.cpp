/**
 * @file    display_controller.cpp
 * @brief   This file contains the function definitions for the display.
 */

#include <display_controller.h>
#include <Arduino.h>
#include <pin_configuration.h>
#include <LiquidCrystal.h> // lib for LCD

namespace DisplayController {
    constexpr int WELCOME_MESSAGE_TIME_MS = 2000;
    constexpr byte DISPLAY_N_COLS = 16;
    constexpr byte DISPLAY_N_ROWS = 2;
    constexpr byte START_COL = 0;
    enum Rows : byte {
        ROW_1 = 0,
        ROW_2 = 1
    };
    constexpr char WELCOME_MESSAGE[] = "Air Quality Meter";
    constexpr char INITIALIZING_MESSAGE[] = "Initializing...";

    // Initialisierung des LCD-Displays (RS, EN, D4, D5, D6, D7)
    LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

    void initialize() {
        lcd.begin(DISPLAY_N_COLS, DISPLAY_N_ROWS); // Initialisiere das LCD mit 16 Zeichen und 2 Zeilen
        lcd.clear(); // delete the display content

        // display Welcome message
        lcd.setCursor(START_COL, ROW_1); // first line
        lcd.print(WELCOME_MESSAGE);
        lcd.setCursor(START_COL, ROW_2); // second line
        lcd.print(INITIALIZING_MESSAGE);

        delay(WELCOME_MESSAGE_TIME_MS); // show the message for 2 seconds
        lcd.clear(); // delete the display content
    }

    void output(const String &line_1, const String &line_2) {
        lcd.clear(); // delete the display content

        // display line 1
        lcd.setCursor(START_COL, ROW_1); // first line
        lcd.print(line_1);

        // display line 2
        lcd.setCursor(START_COL, ROW_2); // second line
        lcd.print(line_2);
    }
}
