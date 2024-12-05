#include <Arduino.h>

// import libraries

// pins
#define BUTTON 7

// global constants
const int co2_threshold_ppm = 1400; // value in ppm
const int max_co2_above_threshold_time_s = 3600; //  value in seconds
const int waiting_period_between_warnings_s = 60; // value in seconds
const int max_consecutive_warnings = 5; // number of maximum consecutive audio warnings

// global variables
int current_time;
int current_co2_measurement;
int last_co2_below_threshold_time;
int warning_counter;

// function declarations
int get_current_time();

int get_co2_measurement();

void issue_audio_warning();

void display_co2_value(int);

void set_led(int);

// the setup function runs once when you press reset or power the board
void setup() {
    last_co2_below_threshold_time = get_current_time();
    warning_counter = 0;
    pinMode(BUTTON, INPUT);
}

// the loop function runs over and over again forever
void loop() {
    // set the current_time timestamp
    current_time = get_current_time();

    // get the current measurement from co2 sensor
    current_co2_measurement = get_co2_measurement();

    // display the current co2 measurement on the display
    display_co2_value(current_co2_measurement);

    // set the LEDs according to the CO2 measurement value
    set_led(current_co2_measurement);

    // check if reset button was pressed
    if (digitalRead(BUTTON) == HIGH) {
        // reset timestamp
        last_co2_below_threshold_time = current_time;
    }

    // check whether the current CO2 measurement is above the threshold value
    if (current_co2_measurement > co2_threshold_ppm) {
        // check whether the CO2 threshold value has already been exceeded for longer than the maximum period of time
        if (current_time - last_co2_below_threshold_time > max_co2_above_threshold_time_s) {
            // issue an audio warning
            issue_audio_warning();

            // adjust the timestamp to wait until the next audio warning
            last_co2_below_threshold_time = last_co2_below_threshold_time + waiting_period_between_warnings_s;

            // increase the warning counter
            warning_counter++;

            // reset timestamp when the maximum number of warnings has been reached
            if (warning_counter > max_consecutive_warnings) {
                last_co2_below_threshold_time = current_time;
            }
        }
    } else {
        // reset timestamp
        last_co2_below_threshold_time = current_time;
    }
}

// function definitions

// get the current time since board is on
int get_current_time() {
    return millis();
};

// get current co2 measurement
int get_co2_measurement() {
    int co2_measurement;
    return co2_measurement;
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
