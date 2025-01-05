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
#include <ArduinoLog.h>
#include <log_controller.h>
#include <state.h>
#include <acknowledge_button.h>
#include <co2_sensor_controller.h>
#include <led_array.h>
#include <display_controller.h>
#include <display_row_formatter.h>
#include <air_quality.h>
#include <measurement_interpreter.h>
#include <audio_controller.h>
#include <warning_controller.h>
#include <co2_level_time_tracker.h>

namespace AirQualityMeter {
    State state = {0, 0, 0}; ///< Holds the system's current state variables.
    constexpr uint8_t LOG_LEVEL = LOG_LEVEL_VERBOSE; ///< Default log level for the air quality meter system.
}

/**
 * @brief   Sets up and initializes all system components.
 *
 * @details This function is executed once during system startup to initialize all required controllers and hardware modules.
 *          It performs the following actions:
 *           - Initializes the logging controller with the system's log level, logs a welcome message, and registers its own initialization.
 *           - Initializes the display controller and logs its successful setup.
 *           - Initializes the LED array hardware and logs its successful setup.
 *           - Initializes the CO2 sensor controller and logs its successful setup.
 *           - Initializes the audio controller and logs its successful setup.
 *           - Sets up the acknowledge button and logs its successful initialization.
 *           - Logs a message indicating that the system is ready after all components are successfully initialized.
 */
void setup() {
    LogController::initialize(AirQualityMeter::LOG_LEVEL);
    LogController::log_welcome_message();
    LogController::log_initialization(LogController::LOG_CONTROLLER);

    DisplayController::initialize();
    LogController::log_initialization(LogController::DISPLAY_CONTROLLER);

    LedArray::initialize();
    LogController::log_initialization(LogController::LED_ARRAY);

    Co2SensorController::initialize();
    LogController::log_initialization(LogController::SENSOR_CONTROLLER);

    AudioController::initialize();
    LogController::log_initialization(LogController::AUDIO_CONTROLLER);

    AcknowledgeButton::initialize();
    LogController::log_initialization(LogController::ACKNOWLEDGE_BUTTON);

    AirQualityMeter::state.last_co2_below_threshold_time_ms = millis();
    LogController::log_current_state();

    Log.noticeln(LogController::SYSTEM_READY);
}

/**
 * @brief   Executes the main operational loop for the system.
 *
 * @details This function manages the continuous monitoring and response cycle performed by the system. It executes during
 *          runtime to gather sensor data, interpret the measurements, and update outputs accordingly. The actions include:
 *           - Logging the start of the loop iteration.
 *           - Retrieving the current system timestamp and logging it.
 *           - Obtaining the CO2 measurement in parts per million (ppm) from the sensor and checking for errors (disconnection or invalid measurement).
 *           - Determining the air quality level corresponding to the CO2 measurement and logging its description.
 *           - Formatting the CO2 data into a display row for output to the system's display controller.
 *           - Updating the visual interface with CO2 measurement data and air quality information.
 *           - Activating the corresponding LED indicators based on the detected air quality level.
 *           - Checking if the air quality is within acceptable limits and resetting the warning state if conditions are safe.
 *           - Calculating the elapsed time since the air quality level was deemed unacceptable.
 *           - Evaluating whether an audio warning should be issued based on the elapsed time and triggering it when needed.
 *           - Updating the system's warning state when an audio warning is issued for unacceptable air quality.
 *           - Logging the end of the main loop iteration.
 */
void loop() {
    LogController::log_loop_start();

    const int current_co2_measurement_ppm = Co2SensorController::get_measurement_in_ppm();
    TRACE_LN_d(current_co2_measurement_ppm);

    if (
        current_co2_measurement_ppm == Co2SensorController::MEASUREMENT_NOT_VALID_ERROR
    ) {
        return;
    }
    const AirQuality::Level current_air_quality_level = MeasurementInterpreter::get_air_quality_level(
        current_co2_measurement_ppm);
    TRACE_LN_s(current_air_quality_level.description);

    char co2_display_row[DisplayRowFormatter::BUFFER_SIZE];
    DisplayRowFormatter::set_co2_display_row(co2_display_row, current_co2_measurement_ppm);
    TRACE_LN_s(co2_display_row);

    DisplayController::output(co2_display_row, current_air_quality_level.description);
    Log.verboseln(LogController::DISPLAY_UPDATED);

    LedArray::output(current_air_quality_level.led_indicator);
    Log.verboseln(LogController::LED_UPDATED);

    TRACE_LN_T(current_air_quality_level.is_acceptable);
    if (current_air_quality_level.is_acceptable) {
        WarningController::reset();
        Log.verboseln(LogController::STATE_UPDATED);

        LogController::log_loop_end();
        return;
    }
    const unsigned long time_since_co2_level_not_acceptable_ms =
            Co2LevelTimeTracker::get_time_since_co2_level_not_acceptable_ms();
    TRACE_LN_u(time_since_co2_level_not_acceptable_ms);

    const bool is_audio_warning_to_be_issued = WarningController::is_audio_warning_to_be_issued(
        time_since_co2_level_not_acceptable_ms);
    TRACE_LN_T(is_audio_warning_to_be_issued);

    if (is_audio_warning_to_be_issued) {
        AudioController::issue_warning();
        Log.verboseln(LogController::AUDIO_WARNING_ISSUED);

        WarningController::update_for_co2_level_not_acceptable();
        Log.verboseln(LogController::STATE_UPDATED);
    }
    Log.noticeln(LogController::LOOP_END);
}
