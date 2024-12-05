#include <Arduino.h>

// import libraries

// pins
#define BUTTON 2 // Interrupt functionality on Pin2 (Int0)

// global constants
constexpr int co2_threshold_ppm = 1400; // value in ppm
// All time constants and variables as unsigned long to delay the overflow of millis() as long as possible.
constexpr unsigned long max_co2_above_threshold_time_s = 3600; //  value in seconds
constexpr unsigned long waiting_period_between_warnings_s = 60; // value in seconds
constexpr int max_consecutive_warnings = 5; // number of maximum consecutive audio warnings

// global variables
// All time constants and variables as unsigned long to delay the overflow of millis() as long as possible.
unsigned long current_time_s;
unsigned long last_loop_iteration_time_s; // to check, if there was a time overflow
int current_co2_measurement_ppm;
volatile unsigned long last_co2_below_threshold_time_s; // volatile to allow change by interrupt function
volatile int warning_counter; // volatile to allow change by interrupt function

// function declarations
void reset();

unsigned long get_current_time_in_s();

int get_co2_measurement_in_ppm();

void issue_audio_warning();

void display_co2_value(int);

void set_led(int);

// the setup function runs once when you press reset or power the board
void setup() {
    // set the current_time_s timestamp (seconds since board is on)
    current_time_s = get_current_time_in_s();
    last_loop_iteration_time_s = current_time_s;
    last_co2_below_threshold_time_s = current_time_s;
    reset();

    // setup Interrupt Service Routine
    attachInterrupt(BUTTON, reset,FALLING); // reset when button is released
}

// the loop function runs over and over again forever
void loop() {
    // set the current_time_s timestamp (seconds since board is on)
    current_time_s = get_current_time_in_s();

    // check, if there was an overflow in the time since board is on
    if (last_loop_iteration_time_s <= current_time_s) {
        // no overflow. reset last_loop_iteration_time_s value to provide at next loop iteration.
        last_loop_iteration_time_s = current_time_s;
    } else {
        // handle time overflow.
        /*
         * This else branch will be executed one to several times in succession after each time overflow.
         * In each case for a maximum period of max_co2_above_threshold_time_s per time overflow.
         */

        /*
         * set the current_time_s variable to the difference between the last_loop_iteration_time_s variable
         * and the last_co2_below_threshold_time_s variable.
         * This allows a new last_co2_below_threshold_time_s value to be set that
         * is less than or equal to the new current_time_s value and
         * has the same difference to the current_time_s as it had at the end of the last iteration.
         */
        current_time_s = last_loop_iteration_time_s - last_co2_below_threshold_time_s;

        /*
         * set the last_co2_below_threshold_time_s variable to 0
         * This should provide the same
         * time difference between current_time_s and last_co2_below_threshold_time_s
         * as it was at the end of the last loop iteration.
         */
        last_co2_below_threshold_time_s = 0;

        // reset last_loop_iteration_time_s value to provide at next loop iteration.
        last_loop_iteration_time_s = current_time_s;
    }

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
            }
        }
    } else {
        // reset timestamp if the CO2 measurement is below or equal to threshold value
        reset();
    }
}

// function definitions

// reset last_co_2_below_threshold_time and warning_counter
void reset() {
    last_co2_below_threshold_time_s = current_time_s;
    warning_counter = 0;
};

// get the current time since board is on in seconds
unsigned long get_current_time_in_s() {
    const unsigned long time_since_board_on_ms = millis();
    // get seconds from milliseconds
    const unsigned long time_since_board_on_s = time_since_board_on_ms / 1000;
    return time_since_board_on_s;
};

// get current co2 measurement in ppm
int get_co2_measurement_in_ppm() {
    int co2_measurement_ppm;
    return co2_measurement_ppm;
}

// issue an audio warning
void issue_audio_warning() {
};

// show the current co2 measurement on the display
void display_co2_value(int) {
};

// set the LEDs according to the CO2 measurement value
void set_led(int) {
};
