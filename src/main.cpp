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
#include "system_state.h"
#include "global_constants.h"
#include "system_manager.h"
#include "co2_sensor.h"
#include "leds.h"
#include "display.h"
#include "air_quality_manager.h"
#include "audio_warning.h"

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
    reset_co2_below_threshold_and_warning_counter();
}

/**
 * @brief   Main loop for air-quality meter logic.
 * @details Continuously reads CO2 levels, updates the display and LEDs and triggers warnings if necessary.
 */
void loop() {
    const unsigned long current_time_s = get_current_time_in_s();
    const int current_co2_measurement_ppm = get_co2_measurement_in_ppm();
    const AirQualityRule current_air_quality_rule = get_air_quality_rule(current_co2_measurement_ppm);
    update_display_air_quality_output(current_co2_measurement_ppm, current_air_quality_rule.description);
    update_led_air_quality_output(current_air_quality_rule.led_indicator);
    manage_unacceptable_air_quality_level(current_time_s, current_air_quality_rule.is_level_acceptable);
    delay(waiting_period_loop_iteration_s); ///< Make sure, hardware is ready for next loop iteration.
}
