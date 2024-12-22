#include <Arduino.h>

/**
 * @file    display.cpp
 * @brief   This file contains the function definitions for the display.
 */

#include <display.h>
#include <pin_configuration.h>
#include <LiquidCrystal.h> // lib for LCD

// Initialisierung des LCD-Displays (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void initialize_display() {
    lcd.begin(16, 2); // Initialisiere das LCD mit 16 Zeichen und 2 Zeilen
    lcd.clear(); // delete the display content

    // display Welcome message
    lcd.setCursor(0, 0); // first line
    lcd.print("LCD 1602 ready");
    lcd.setCursor(0, 1); // second line
    lcd.print("Initializing...");

    delay(4000); // show the message for 2 seconds
    lcd.clear(); // delete the display content
}

void display_out(const String &line_1, const String &line_2) {
    lcd.clear(); // delete the display content

    // display line 1
    lcd.setCursor(0, 0); // first line
    lcd.print(line_1);

    // display line 2
    lcd.setCursor(0, 1); // second line
    lcd.print(line_2);
}
