#include <Arduino.h>

/**
 * @file    display.cpp
 * @brief   This file contains the function definitions for the display.
 */

#include <display.h>
#include "pin_configuration.h"
#include <LiquidCrystal.h> // lib for LCD

constexpr int welcome_message_time_ms = 2000;
constexpr byte display_n_cols = 16;
constexpr byte display_n_rows = 2;
constexpr byte start_col = 0;
enum Rows : byte {
    ROW_1 = 0,
    ROW_2 = 1
};
constexpr char welcome_message[] = "Air Quality Meter";
constexpr char initializing_message[] = "Initializing...";

// Initialisierung des LCD-Displays (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

void initialize_display() {
    lcd.begin(display_n_cols, display_n_rows); // Initialisiere das LCD mit 16 Zeichen und 2 Zeilen
    lcd.clear(); // delete the display content

    // display Welcome message
    lcd.setCursor(start_col, Rows::ROW_1); // first line
    lcd.print(welcome_message);
    lcd.setCursor(start_col, Rows::ROW_2); // second line
    lcd.print(initializing_message);

    delay(welcome_message_time_ms); // show the message for 2 seconds
    lcd.clear(); // delete the display content
}

void display_out(const String &line_1, const String &line_2) {
    lcd.clear(); // delete the display content

    // display line 1
    lcd.setCursor(start_col, Rows::ROW_1); // first line
    lcd.print(line_1);

    // display line 2
    lcd.setCursor(start_col, Rows::ROW_2); // second line
    lcd.print(line_2);
}
