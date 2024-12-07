#include <Arduino.h>

/**
 * @file    main.cpp
 * @brief   Arduino Sketch for the air quality meter.
 * @details This program monitors the CO2 concentration in indoor air and shows the current value in ppm on a display.
 *          The interpretation of the values is supported by a multi-colored LED display. CO2 values above the
 *          threshold value trigger an acoustic warning after a defined period of time. A reset button can be used
 *          to cancel the warning.
 */

// import libraries

// Pins
#define BUTTON 2 ///< Interrupt functionality on Pin2 (Int0)

// Global constants
constexpr int co2_threshold_ppm = 1400; ///< CO2 threshold value in parts per million (ppm)
constexpr int max_co2_above_threshold_time_s = 3600; ///< Max time period allowed CO2 above threshold (seconds)
constexpr int waiting_period_between_warnings_s = 60; ///< Time period between two warnings (seconds)
constexpr int max_consecutive_warnings = 5; ///< Max consecutive audio warnings before reset

// Global variables
int current_time_s; ///< Current timestamp (~time since board is powered on) (seconds)
int current_co2_measurement_ppm; ///< Current CO2 measurement in parts per million (ppm)
// Volatile variables (to allow mutation by interrupt function)
volatile int last_co2_below_threshold_time_s; ///< Timestamp of last CO2 measurement below threshold (seconds)
volatile int warning_counter; ///< Counter for consecutive warnings

// function declarations
void reset();

int get_current_time_in_s();

int get_co2_measurement_in_ppm();

void issue_audio_warning();

void display_co2_value(int);

void set_led(int);

/**
 * @brief   Initializes the Arduino setup routine.
 * @details Configures initial system states and sets up the interrupt service routine.
 *          Runs once when the board is powered on or reset.
 */
void setup() {
    // Set initial current_time_s timestamp (seconds since board is on).
    current_time_s = get_current_time_in_s();

    // Set initial last_co2_below_threshold_time_s to current_time_s and warning_counter to 0
    reset();

    // Setup Interrupt Service Routine
    attachInterrupt(BUTTON, reset,FALLING); ///< reset() function when button is pressed (released)
};

// the loop function runs over and over again forever
void loop() {
    // set the current_time_s timestamp (seconds since board is on)
    current_time_s = get_current_time_in_s();

    // get the current measurement from co2 sensor in ppm
    current_co2_measurement_ppm = get_co2_measurement_in_ppm();

    // display the current co2 measurement on the display
    display_co2_value(current_co2_measurement_ppm);

    // set the LEDs according to the CO2 measurement value
    set_led(current_co2_measurement_ppm);

    // check whether the current CO2 measurement is above the threshold value
    if (current_co2_measurement_ppm > co2_threshold_ppm) {
        // check whether the CO2 threshold value has already been exceeded for longer than the maximum period of time
        if (current_time_s - last_co2_below_threshold_time_s > max_co2_above_threshold_time_s) {
            // issue an audio warning
            issue_audio_warning();

            // adjust the timestamp to wait until the next audio warning
            last_co2_below_threshold_time_s = last_co2_below_threshold_time_s + waiting_period_between_warnings_s;

            // increase the warning counter
            warning_counter++;

            // reset timestamp when the maximum number of warnings has been reached
            if (warning_counter >= max_consecutive_warnings) {
                reset();
            };
        };
    } else {
        // reset timestamp if the CO2 measurement is below or equal to threshold value
        reset();
    };
};

// function definitions

// reset last_co_2_below_threshold_time and warning_counter
void reset() {
    last_co2_below_threshold_time_s = current_time_s;
    warning_counter = 0;
};

// get the current time since board is on in seconds
int get_current_time_in_s() {
    const unsigned long time_since_board_on_ms = millis();
    // get seconds from milliseconds
    int time_since_board_on_s = time_since_board_on_ms / 1000;
    return time_since_board_on_s;
};

// get current co2 measurement in ppm
int get_co2_measurement_in_ppm() {
    int co2_measurement_ppm;
    return co2_measurement_ppm;
};

// issue an audio warning
void issue_audio_warning() {
};

// show the current co2 measurement on the display
void display_co2_value(int) {
};

// set the LEDs according to the CO2 measurement value
void set_led(int) {
};
