/**
 * @file    main.cpp
 * @brief   Arduino Sketch for the air quality meter.
 * @details This program controls an Arduino board (Mega 2560) which, along with other components, operates as an
 *          air quality meter. That device monitors the CO2 concentration in indoor air and shows the current value in
 *          ppm on a display. The interpretation of the values is assisted by a series of 6 LEDs in three different
 *          colors. CO2 values above the threshold value trigger an acoustic warning after a defined period of time.
 *          An acknowledge button can be used to cancel the warning.
 */

#include <Arduino.h>
#include "system_state.h"
#include <acknowledge_button.h>
#include <time_controller.h>
#include <co2_sensor_controller.h>
#include <led_array.h>
#include <display_controller.h>
#include <output_controller.h>
#include <air_quality.h>
#include <measurement_interpreter.h>
#include <audio_controller.h>

SystemState system_state = {0, 0, 0};

constexpr unsigned int WAITING_PERIOD_INITIALIZATION_MS = 2000;
///< Wait after initializing the board and all other hardware modules to make sure, they are ready.

constexpr unsigned int WAITING_PERIOD_LOOP_ITERATION_MS = 3000;
///< Wait after each loop iteration to prevent overlapping device triggering.

constexpr unsigned int SERIAL_BAUD_RATE = 9600; ///< Baud rate for serial communication for debugging

/**
 * @brief   Sets up the required hardware components and serial communication before the main program loop starts.
 *
 * @details This function initializes
 *           - the serial communication interface,
 *           - the display,
 *           - the acknowledge button,
 *           - the CO2 sensor,
 *           - the LEDs,
 *           - and the MP3 module.
 *          It also adds a delay after initialization to ensure all the hardware is ready for use.
 */
void setup() {
    Serial.begin(SERIAL_BAUD_RATE); ///< Initialize serial communication over USB (for debugging)
    DisplayController::initialize();
    AcknowledgeButton::initialize();
    Co2SensorController::initialize();
    LedArray::initialize();
    AudioController::initialize();
    delay(WAITING_PERIOD_INITIALIZATION_MS); ///< Make sure, hardware is ready to use.
}

/**
 * @brief   Main system loop responsible for air quality measurement, air quality level evaluation, and hardware output updates.
 *
 * @details This function performs the following:
 *           - Retrieves the current system time in seconds.
 *           - Obtains the current CO2 measurement in parts per million (ppm).
 *           - Evaluates air quality levels based on the CO2 measurement.
 *           - Updates the display with the air quality status and description.
 *           - Updates the LED output to reflect air quality level.
 *           - Manages behavior for unacceptable air quality levels.
 *           - Introduces a delay to ensure hardware modules are ready for the next iteration.
 */
void loop() {
    const unsigned long current_iteration_time_stamp_s = TimeController::get_timestamp_s();
    const int current_co2_measurement_ppm = Co2SensorController::get_measurement_in_ppm();
    const AirQuality::Level current_air_quality_level = MeasurementInterpreter::get_air_quality_level(current_co2_measurement_ppm);
    OutputController::update_display(current_co2_measurement_ppm, current_air_quality_level.description);
    OutputController::update_led_array(current_air_quality_level.led_indicator);
    OutputController::manage_audio_warnings(current_iteration_time_stamp_s,
                                          current_air_quality_level.is_level_acceptable);
    delay(WAITING_PERIOD_LOOP_ITERATION_MS); ///< Make sure, hardware is ready for next loop iteration.
}
