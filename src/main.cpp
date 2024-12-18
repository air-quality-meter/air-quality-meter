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

// Import header files
#include "system/global_constants.h"
#include "system/global_variables.h"
#include "system/system_manager.h"
#include "sensor/co2_sensor.h"
#include "display/leds.h"
#include "display/display.h"
#include "air_quality/air_quality_manager.h"
#include "audio/audio_warning.h"

// Import external libraries

/// Arduino Sketch functions
/**
 * @brief   Initializes the Arduino setup routine.
 * @details Configures initial system states and sets up the interrupt service routine.
 *          Runs once when the board is powered on or reset.
 */
void setup() {
    Serial.begin(9600); ///< Initialize serial communication over USB (for debugging)
    initialize_display();
    initialize_reset_button();
    initialize_co2_sensor();
    initialize_leds();
    initialize_mp3_module();
    delay(waiting_period_initialization_s); ///< Make sure, hardware is ready to use.
    current_time_s = get_current_time_in_s();
    reset_co2_below_threshold_and_warning_counter();
}

/**
 * @brief   Main loop for air-quality meter logic.
 * @details Continuously reads CO2 levels, updates the display and LEDs and triggers warnings if necessary.
 */
void loop() {
    current_time_s = get_current_time_in_s();
    current_co2_measurement_ppm = get_co2_measurement_in_ppm();
    const AirQualityRule *current_air_quality_rule = get_air_quality_rule(current_co2_measurement_ppm);
    update_air_quality_output(current_co2_measurement_ppm, current_air_quality_rule);
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
            }
        }
    } else {
        reset_co2_below_threshold_and_warning_counter();
    }
    delay(waiting_period_loop_iteration_s); ///< Make sure, hardware is ready for next loop iteration.
}
