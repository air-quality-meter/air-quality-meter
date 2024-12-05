#include <Arduino.h>

// import libraries

// pins
#define BUTTON 2 // Interrupt functionality on Pin2 (Int0)

// global constants
constexpr int co2_threshold_ppm = 1400; // value in ppm
constexpr int max_co2_above_threshold_time_s = 3600; //  value in seconds
constexpr int waiting_period_between_warnings_s = 60; // value in seconds
constexpr int max_consecutive_warnings = 5; // number of maximum consecutive audio warnings

// global variables
int current_time_s;
int current_co2_measurement_ppm;
volatile int last_co2_below_threshold_time_s; // volatile to allow change by interrupt function
volatile int warning_counter; // volatile to allow change by interrupt function

// function declarations
void reset();

int get_current_time_in_s();

int get_co2_measurement_in_ppm();

void issue_audio_warning();

void display_co2_value(int);

void set_led(int);

// the setup function runs once when you press reset or power the board
void setup() {
    // set the current_time_s timestamp (seconds since board is on)
    current_time_s = get_current_time_in_s();
    reset();

    // setup Interrupt Service Routine
    attachInterrupt(BUTTON, reset,FALLING); // reset when button is released
}

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
