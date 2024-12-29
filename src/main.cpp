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
#include <time_controller.h>
#include <co2_sensor_controller.h>
#include <led_array.h>
#include <display_controller.h>
#include <display_row_formatter.h>
#include <air_quality.h>
#include <measurement_interpreter.h>
#include <audio_controller.h>
#include <error_messages.h>
#include <warning_controller.h>
#include <warning_state_controller.h>
#include <co2_level_time_tracker.h>

namespace AirQualityMeter {
    State state = {0, 0, 0};
    constexpr byte LOG_LEVEL = LOG_LEVEL_VERBOSE;
    constexpr unsigned int WAITING_PERIOD_INITIALIZATION_MS = 2000;
    ///< Wait after initializing the board and all other hardware modules to make sure, they are ready.
    constexpr unsigned int WAITING_PERIOD_LOOP_ITERATION_MS = 3000;
    ///< Wait after each loop iteration to prevent overlapping device triggering.
}

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
    LogController::initialize(AirQualityMeter::LOG_LEVEL);
    LogController::log_welcome_message();
    LogController::log_initialization(LogController::LOG_CONTROLLER);

    DisplayController::initialize();
    LogController::log_initialization(LogController::DISPLAY_CONTROLLER);

    AcknowledgeButton::initialize();
    LogController::log_initialization(LogController::ACKNOWLEDGE_BUTTON);

    Co2SensorController::initialize();
    LogController::log_initialization(LogController::SENSOR_CONTROLLER);

    LedArray::initialize();
    LogController::log_initialization(LogController::LED_ARRAY);

    AudioController::initialize();
    LogController::log_initialization(LogController::AUDIO_CONTROLLER);

    delay(AirQualityMeter::WAITING_PERIOD_INITIALIZATION_MS); ///< Make sure, hardware is ready to use.
    Log.noticeln(LogController::SYSTEM_READY);
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
    LogController::log_loop_start();

    const unsigned long current_iteration_time_stamp_s = TimeController::get_timestamp_s();
    TRACE_LN_u(current_iteration_time_stamp_s);

    const int current_co2_measurement_ppm = Co2SensorController::get_measurement_in_ppm();
    TRACE_LN_d(current_co2_measurement_ppm);

    if (current_co2_measurement_ppm == -1) {
        Log.errorln(LogController::SENSOR_ERROR);

        LedArray::output(LedErrorPatterns::SENSOR_ERROR);
        Log.verboseln(LogController::LED_UPDATED);

        DisplayController::output(GeneralError::ERROR_MESSAGE_ROW_ONE, SensorError::ERROR_MESSAGE_ROW_TWO);
        Log.verboseln(LogController::DISPLAY_UPDATED);

        delay(AirQualityMeter::WAITING_PERIOD_LOOP_ITERATION_MS);
        LogController::log_loop_end();
        return;
    }
    const AirQuality::Level current_air_quality_level = MeasurementInterpreter::get_air_quality_level(
        current_co2_measurement_ppm);
    TRACE_LN_s(current_air_quality_level.description);

    const String co2_display_row = DisplayRowFormatter::get_co2_display_row(current_co2_measurement_ppm);
    TRACE_LN_s(co2_display_row);

    DisplayController::output(co2_display_row, current_air_quality_level.description);
    Log.verboseln(LogController::DISPLAY_UPDATED);

    LedArray::output(current_air_quality_level.led_indicator);
    Log.verboseln(LogController::LED_UPDATED);

    TRACE_LN_T(current_air_quality_level.is_acceptable);
    if (current_air_quality_level.is_acceptable) {
        WarningStateController::reset(current_iteration_time_stamp_s);
        Log.verboseln(LogController::STATE_UPDATED);

        delay(AirQualityMeter::WAITING_PERIOD_LOOP_ITERATION_MS);
        ///< Make sure, hardware is ready for next loop iteration.

        LogController::log_loop_end();
        return;
    }
    const unsigned long time_since_co2_level_not_acceptable_s =
            Co2LevelTimeTracker::get_time_since_co2_level_not_acceptable_s(current_iteration_time_stamp_s);
    TRACE_LN_u(time_since_co2_level_not_acceptable_s);

    const bool is_audio_warning_to_be_issued = WarningController::is_audio_warning_to_be_issued(
        time_since_co2_level_not_acceptable_s);
    TRACE_LN_T(is_audio_warning_to_be_issued);

    if (is_audio_warning_to_be_issued) {
        AudioController::issue_warning();
        Log.verboseln(LogController::AUDIO_WARNING_ISSUED);

        WarningStateController::update_for_co2_level_not_acceptable(current_iteration_time_stamp_s);
        Log.verboseln(LogController::STATE_UPDATED);
    }
    delay(AirQualityMeter::WAITING_PERIOD_LOOP_ITERATION_MS);
    ///< Make sure, hardware is ready for next loop iteration.
    Log.noticeln(LogController::LOOP_END);
}
