#include <Arduino.h>

/**
 * @file    main.cpp
 * @brief   Arduino Sketch for the air quality meter.
 * @details This program controls an Arduino board (Mega 2560) which, along with other components, operates as an
 *          air quality meter. That device monitors the CO2 concentration in indoor air and shows the current value in
 *          ppm on a display. The interpretation of the values is assisted by a series of 6 LEDs in three different
 *          colors. CO2 values above the threshold value trigger an acoustic warning after a defined period of time.
 *          A reset button can be used to cancel the warning.
 */

// Import libraries

// Pins
#define TIME_COUNTER_RESET_BUTTON_PIN 2 ///< Interrupt functionality on Pin2 (Int0)
#define GREEN_LED_1_PIN 22 ///< LED to indicate high air quality on Pin 22
#define GREEN_LED_2_PIN 24 ///< LED to indicate high or medium air quality on Pin 24
#define YELLOW_LED_1_PIN 26 ///< LED to indicate medium or moderate air quality on Pin 26
#define YELLOW_LED_2_PIN 28 ///< LED to indicate moderate air quality on Pin 28
#define RED_LED_1_PIN 30 ///< LED to indicate moderate or poor air quality on Pin 30
#define RED_LED_2_PIN 32 ///< LED to indicate poor air quality on Pin 32

// Global constants
/*
 * Air quality thresholds based on DIN EN 13779.
 * See: https://www.umweltbundesamt.de/sites/default/files/medien/publikation/long/4113.pdf
 */
constexpr int co2_upper_threshold_high_air_quality_ppm = 800;
///< Upper CO2 threshold (less than or equal to) for high indoor air quality (IDA 1 DIN EN 13779)
///< in parts per million (ppm)

constexpr int co2_upper_threshold_medium_air_quality_ppm = 1000;
///< Upper CO2 threshold (less than or equal to) for medium indoor air quality (IDA 2 DIN EN 13779)
///< in parts per million (ppm)

constexpr int co2_mid_threshold_moderate_air_quality_ppm = 1200;
///< Upper CO2 threshold (less than or equal to) for lower half (mid) of moderate indoor air quality
///< (IDA 3 DIN EN 13779) parts per million (ppm). The IDA 3 bandwidth is double the size of the IDA 2 bandwidth,
///< which is why it is divided into two halves here.

constexpr int co2_upper_threshold_moderate_air_quality_ppm = 1400;
///< Upper CO2 threshold (less than or equal to) for moderate indoor air quality (IDA 3 DIN EN 13779)
///< parts per million (ppm). At the same time, this value represents the lower threshold (greater than) value
///< for poor indoor air quality (IDA 4 DIN EN 13779)

constexpr int max_consecutive_warnings = 5; ///< Max consecutive audio warnings before reset

constexpr unsigned long max_co2_above_threshold_time_s = 3600;
///< Max time period allowed CO2 above threshold (seconds)

constexpr unsigned long waiting_period_between_warnings_s = 60; ///< Time period between two warnings (seconds)

// Global variables
unsigned long current_time_s;
///< Current timestamp (time since board is powered on or since last overflow of millis()) (seconds)

int current_co2_measurement_ppm; ///< Current CO2 measurement in parts per million (ppm)

volatile unsigned long last_co2_below_threshold_time_s;
///< Timestamp of last CO2 measurement below threshold (seconds) to calculate the elapsed time, since CO2 concentration
///< is too high. Used to manage warnings and warning intervals

volatile int warning_counter; ///< Counter for consecutive warnings

// function declarations
void reset_co2_below_threshold_and_warning_counter();

unsigned long get_current_time_in_s();

int get_co2_measurement_in_ppm();

void issue_audio_warning();

void display_co2_value(int co2_measurement_ppm);

void set_led(int co2_measurement_ppm);

/// Arduino Sketch functions
/**
 * @brief   Initializes the Arduino setup routine.
 * @details Configures initial system states and sets up the interrupt service routine.
 *          Runs once when the board is powered on or reset.
 */
void setup() {
    current_time_s = get_current_time_in_s();
    reset_co2_below_threshold_and_warning_counter();

    // Setup Interrupt Service Routine.
    attachInterrupt(TIME_COUNTER_RESET_BUTTON_PIN, reset_co2_below_threshold_and_warning_counter,FALLING);

    // Setup Input/Output
    pinMode(GREEN_LED_1_PIN, OUTPUT); ///< LED for high air quality
    pinMode(GREEN_LED_2_PIN, OUTPUT); ///< LED for high or medium air quality
    pinMode(YELLOW_LED_1_PIN, OUTPUT); ///< LED for medium or moderate air quality
    pinMode(YELLOW_LED_2_PIN, OUTPUT); ///< LED for moderate air quality
    pinMode(RED_LED_1_PIN, OUTPUT); ///< LED for moderate or poor air quality
    pinMode(RED_LED_2_PIN, OUTPUT); ///< LED for poor air quality
};

/**
 * @brief   Main loop for air-quality meter logic.
 * @details Continuously reads CO2 levels, updates the display and LEDs and triggers warnings if necessary.
 */
void loop() {
    current_time_s = get_current_time_in_s();
    current_co2_measurement_ppm = get_co2_measurement_in_ppm();
    display_co2_value(current_co2_measurement_ppm);
    set_led(current_co2_measurement_ppm);

    if (current_co2_measurement_ppm > co2_upper_threshold_moderate_air_quality_ppm) {
        /**
         * @brief   check if the CO2 threshold value has already been exceeded for
         *          longer than the maximum allowable time.
         *
         * @note    As all time variables and constants are unsigned, a possible time overflow will still be handled
         *          correctly.
         *          A potentially very high value for the variable last_co2_below_threshold_time_s of almost the
         *          maximum of the unsigned long type still leads to a correct result of the subraction
         *          (current_time_s - last_co2_below_threshold_time_s)
         *          even after an overflow of millis(), when current_time_s has a very small value again.
         *
         * @see     https://en.cppreference.com/w/cpp/language/operator_arithmetic#:~:text=conversions%20are%20applied.-,Overflows,-Unsigned%20integer%20arithmetic
         */
        if (current_time_s - last_co2_below_threshold_time_s > max_co2_above_threshold_time_s) {
            issue_audio_warning();

            // Wait until the next audio warning to prevent uninterrupted audio output.
            last_co2_below_threshold_time_s = last_co2_below_threshold_time_s + waiting_period_between_warnings_s;
            warning_counter++;
            if (warning_counter >= max_consecutive_warnings) {
                reset_co2_below_threshold_and_warning_counter();
            };
        };
    } else {
        reset_co2_below_threshold_and_warning_counter();
    };
};

// Function definitions
/**
 * @brief   Resets last_co2_below_threshold_time_s and warning_counter.
 * @details Resets the timestamp of the last CO2 measurement that was below the threshold
 *          and the counter for consecutive warnings.
 */
void reset_co2_below_threshold_and_warning_counter() {
    last_co2_below_threshold_time_s = current_time_s;
    warning_counter = 0;
};

/**
 * @brief   Retrieves the elapsed time since the board was powered on.
 * @details Converts the internal millis() value from milliseconds to seconds to provide a time reference.
 * @return  The elapsed time since the board was powered on in seconds.
 */
unsigned long get_current_time_in_s() {
    const unsigned long time_since_board_on_ms = millis(); ///< timestamp in milliseconds
    const unsigned long time_since_board_on_s = time_since_board_on_ms / 1000; ///< timestamp in seconds
    return time_since_board_on_s;
};

/**
 * @brief   Retrieves a CO2 measurement.
 * @details Reads the CO2 value from the sensor and provides the measurement in parts per million (ppm).
 *          Sensor used: MH-Z19 Infrared CO2 Sensor Module MH-Z19B
 * @return  The current CO2 measurement in ppm.
 */
int get_co2_measurement_in_ppm() {
    //TODO: This function needs to be written.
    return 1500; //FIXME: this is a placeholder value. Fix when writing this function.
};

/**
 * @brief   Issues an audio warning.
 * @details Voice message that calls for the room to be ventilated (output of an MP3 track).
 *          MP3 module used: Gravity UART MP3 Voice Module
 *          Speaker used: Stereo Enclosed Speaker - 3W 8Ω
 */
void issue_audio_warning() {
    //TODO: This function needs to be written.
};

/**
 * @brief   Displays the provided CO2 measurement.
 * @details Updates the connected display to show the provided CO2 value in ppm.
 *          Display used: LCD1602 Module (with pin header)
 * @param co2_measurement_ppm The CO2 value to be displayed, in parts per million (ppm)
 */
void display_co2_value(const int co2_measurement_ppm) {
    //TODO: This function needs to be written.
};

/**
 * @brief   Controls the LED indicators to visually represent CO2 levels.
 * @details Activates two adjacent LEDs out of six in a series to indicate the current CO2 concentration:
 *              - high indoor air quality: Both green LEDs light up.
 *              - medium indoor air quality: One green and one yellow LED (adjacent to each other) light up.
 *              - lower half of moderate indoor air quality: Both yellow LEDs light up.
 *              - upper half of moderate indoor air quality: One yellow and one red LED (adjacent to each other) light up.
 *              - poor indoor air quality: Both red LEDs light up.
 * @param co2_measurement_ppm The CO2 value whose level should be indicated with the LEDs
 */
void set_led(const int co2_measurement_ppm) {
    // Reset all LEDs to off state to prepare for the next indication.
    digitalWrite(GREEN_LED_1_PIN, LOW);
    digitalWrite(GREEN_LED_2_PIN, LOW);
    digitalWrite(YELLOW_LED_1_PIN, LOW);
    digitalWrite(YELLOW_LED_2_PIN, LOW);
    digitalWrite(RED_LED_1_PIN, LOW);
    digitalWrite(RED_LED_2_PIN, LOW);

    // Set LEDs to indicate the current CO2 measurement.
    if (co2_measurement_ppm <= co2_upper_threshold_high_air_quality_ppm) {
        // High indoor air quality.
        digitalWrite(GREEN_LED_1_PIN, HIGH);
        digitalWrite(GREEN_LED_2_PIN, HIGH);
    } else if (co2_measurement_ppm <= co2_upper_threshold_medium_air_quality_ppm) {
        // Medium indoor air quality.
        digitalWrite(GREEN_LED_2_PIN, HIGH);
        digitalWrite(YELLOW_LED_1_PIN, HIGH);
    } else if (co2_measurement_ppm <= co2_mid_threshold_moderate_air_quality_ppm) {
        // Lower half of moderate indoor air quality.
        digitalWrite(YELLOW_LED_1_PIN, HIGH);
        digitalWrite(YELLOW_LED_2_PIN, HIGH);
    } else if (co2_measurement_ppm <= co2_upper_threshold_moderate_air_quality_ppm) {
        // upper half of moderate indoor air quality.
        digitalWrite(YELLOW_LED_2_PIN, HIGH);
        digitalWrite(RED_LED_1_PIN, HIGH);
    } else {
        // poor indoor air quality.
        digitalWrite(RED_LED_1_PIN, HIGH);
        digitalWrite(RED_LED_2_PIN, HIGH);
    };
};
