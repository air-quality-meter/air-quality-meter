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

// Global string constants
constexpr auto co2_prefix = String("CO2: "); ///< Prefix to display CO2 value
constexpr auto ppm_suffix = String(" ppm"); ///< Suffix to display a value with ppm as the unit
constexpr auto high_air_quality_description = String("High air quality"); ///< Text for IDA 1
constexpr auto medium_air_quality_description = String("Medium air quality"); ///< Text for IDA 2
constexpr auto moderate_air_quality_description = String("Moderate air quality"); ///< Text for IDA 3
constexpr auto poor_air_quality_description = String("Poor air quality"); ///< Text for IDA 4

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

void visually_output_air_quality(int co2_measurement_ppm);

void display_out(const String &line_1, const String &line_2);

void set_leds(bool is_green_led_1_on,
              bool is_green_led_2_on,
              bool is_yellow_led_1_on,
              bool is_yellow_led_2_on,
              bool is_red_led_1_on,
              bool is_red_led_2_on);

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
    visually_output_air_quality(current_co2_measurement_ppm);
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
 * @brief   Outputs text to the LCD.
 * @details Updates the connected display module to display the provided text on two lines.
 *          Display used: LCD1602 Module (with pin header)
 *          This function uses call by reference for the `String` parameters to avoid unnecessary
 *          copying of potentially large strings, improving performance. The `const` keyword
 *          ensures that the function cannot modify the original strings.
 * @param line_1 Text to display on the first line of the LCD.
 * @param line_2 Text to display on the second line of the LCD.
 */
void display_out(const String &line_1, const String &line_2) {
    //TODO: This function needs to be written.
};

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
void set_leds(const bool is_green_led_1_on,
              const bool is_green_led_2_on,
              const bool is_yellow_led_1_on,
              const bool is_yellow_led_2_on,
              const bool is_red_led_1_on,
              const bool is_red_led_2_on) {
    digitalWrite(GREEN_LED_1_PIN, is_green_led_1_on);
    digitalWrite(GREEN_LED_2_PIN, is_green_led_2_on);
    digitalWrite(YELLOW_LED_1_PIN, is_yellow_led_1_on);
    digitalWrite(YELLOW_LED_2_PIN, is_yellow_led_2_on);
    digitalWrite(RED_LED_1_PIN, is_red_led_1_on);
    digitalWrite(RED_LED_2_PIN, is_red_led_2_on);
};

/**
 * @brief   Visually outputs air quality to display and LED indicators.
 * @details Sends CO2 value and a description of the air quality to display output and
 *          sets the LED indicators accordingly.
 *              - high indoor air quality: Both green LEDs light up.
 *              - medium indoor air quality: One green and one yellow LED (adjacent to each other) light up.
 *              - lower half of moderate indoor air quality: Both yellow LEDs light up.
 *              - upper half of moderate indoor air quality: One yellow and one red LED (adjacent to each other) light up.
 *              - poor indoor air quality: Both red LEDs light up.
 * @param co2_measurement_ppm CO2 value.
 */
void visually_output_air_quality(const int co2_measurement_ppm) {
    const String display_line_1 = co2_prefix + co2_measurement_ppm + ppm_suffix;
    String display_line_2;
    if (co2_measurement_ppm <= co2_upper_threshold_high_air_quality_ppm) {
        display_line_2 = high_air_quality_description;
        set_leds(true, true, false, false, false, false);
    } else if (co2_measurement_ppm <= co2_upper_threshold_medium_air_quality_ppm) {
        display_line_2 = medium_air_quality_description;
        set_leds(false, true, true, false, false, false);
    } else if (co2_measurement_ppm <= co2_mid_threshold_moderate_air_quality_ppm) {
        display_line_2 = moderate_air_quality_description;
        set_leds(false, false, true, true, false, false);
    } else if (co2_measurement_ppm <= co2_upper_threshold_moderate_air_quality_ppm) {
        display_line_2 = moderate_air_quality_description;
        set_leds(false, false, false, true, true, false);
    } else {
        display_line_2 = poor_air_quality_description;
        set_leds(false, false, false, false, true, true);
    };
    display_out(display_line_1, display_line_2);
};
