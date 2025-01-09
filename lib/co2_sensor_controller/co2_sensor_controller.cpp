/**
 * @file    co2_sensor_controller.cpp
 * @brief   Implementation of the CO2 sensor controller functions.
 * @details This file contains the internal logic and helper functions to initialize and retrieve
 *          data from the MH-Z19B sensor, in addition to handling errors and edge cases.
 */

#include <co2_sensor_controller.h>
#include <pin_configuration.h>
#include <../lib/display_controller/display_controller.h>
#include <MHZ.h>
#include <state.h>
#include <ArduinoLog.h>
#include "../log_controller/log_controller.h"
#include <error_messages.h>
#include <../led_array/led_array.h>
#include <led_patterns.h>
#include <not_blocking_time_handler.h>


namespace Co2SensorController {
    /**
     * @brief   Sets the timestamp for the last sensor use.
     * @details Updates the global state with the current time, ensuring accurate tracking for timing-related operations.
     */
    void set_sensor_use_time_stamp();

    /**
     * @brief   Waits until a specific time has elapsed.
     * @details This function blocks the execution of the program until the required time interval has passed.
     * @param   time_stamp_since_time_has_to_pass_ms The starting timestamp to measure the interval.
     * @param   time_to_pass_ms The duration (in milliseconds) that must elapse.
     */
    void wait_until_time_passed(unsigned long time_stamp_since_time_has_to_pass_ms, unsigned long time_to_pass_ms);

    /**
     * @brief   Combines two strings into a single buffer with a space separating them.
     * @param   buffer The destination buffer to hold the concatenated string.
     * @param   buffer_size The size of the buffer (to avoid overflows).
     * @param   string_1 The first string to concatenate.
     * @param   string_2 The second string to concatenate.
     * @note    If the buffer size is insufficient, the contents may be truncated.
     */
    void concat_strings(char *buffer, size_t buffer_size, const char *string_1, const char *string_2);

    /**
     * @brief   Handles the preheating process of the CO2 sensor.
     * @details Preheats the sensor as per the manufacturer's recommendations. During this process:
     *          - A progress bar is displayed on the screen to indicate preheating progress.
     *          - The function ensures the sensor is ready before proceeding.
     * @note    This function will block execution while waiting for the sensor to complete preheating.
     */
    void preheat_sensor();

    /**
     * @brief   Renders a progress bar for the sensor preheating process.
     * @details Updates the display to show the progress of the sensor preheating, adding a symbol for each completed
     *          unit of preheating time.
     * @param   row_1 The first row text to display on the screen.
     * @param   row_2_buffer A buffer that holds the second-row progress bar text.
     * @param   bar_with The width of the progress bar (usually corresponds to the display's width in characters).
     * @param   progress_bar_counter A pointer to the counter that tracks completed progress bar steps.
     */
    void display_preheat_progress_bar(const char *row_1, char *row_2_buffer, uint8_t bar_with,
                                      int *progress_bar_counter);

    /**
     * @brief   Handles errors related to invalid sensor measurements.
     * @details This function is triggered when the sensor provides measurements outside the expected or valid range.
     *          It performs the following actions:
     *          - Logs an error message.
     *          - Displays an error on the LED array and screen.
     *          - Waits for a short delay to allow users time to notice the error displayed on the screen.
     */
    void invalid_measurement_error_handler();

    constexpr char SENSOR_NAME[] = "MHZ 19B"; ///< Name of the CO2 sensor module used in this implementation.
    constexpr char INIT[] = "Initializing"; ///< Status message for the sensor initialization process
    constexpr char PREHEAT[] = "Preheating"; ///< Status message displayed during sensor preheating.
    constexpr char PROGRESS_BAR_SYMBOL[] = "#"; ///< Symbol used to display progress in the preheating progress bar.
    constexpr char PREHEAT_COMPLETE[] = "Preheating complete.";
    ///< Message shown after the sensor has completed preheating.
    constexpr size_t SENSOR_NAME_LENGTH = sizeof(SENSOR_NAME) - 1;
    ///< Length of the sensor's name, excluding the null-terminator.
    constexpr size_t INIT_LENGTH = sizeof(INIT) - 1;
    ///< Length of the initialization message, excluding the null-terminator.
    constexpr size_t PREHEAT_LENGTH = sizeof(PREHEAT) - 1;
    ///< Length of the preheating message, excluding the null-terminator.
    constexpr size_t INIT_MESSAGE_LENGTH = SENSOR_NAME_LENGTH + INIT_LENGTH + 1;
    ///< Combined length of the sensor name and initialization message, including a space.
    constexpr size_t PREHEAT_MESSAGE_LENGTH = SENSOR_NAME_LENGTH + PREHEAT_LENGTH + 1;
    ///< Combined length of the sensor name and preheating message, including a space.
    constexpr unsigned long RESPONSE_TIME_MS = 2000;
    ///< Waiting period between readings
    constexpr unsigned long PREHEATING_TIME_MS = 180000;
    ///< Preheating duration for MH-Z19B sensor in milliseconds (3 minutes as per the datasheet).
    constexpr unsigned long WAITING_PERIOD_FOR_DISPLAY_MESSAGES_MS = 2000;
    ///< Time to show error or status messages on the display (in milliseconds).
    constexpr unsigned long PREHEAT_PROGRESS_BAR_UNIT_PROGRESS_MS =
            PREHEATING_TIME_MS / DisplayController::DISPLAY_WIDTH;
    ///< Duration (in milliseconds) for one step in the preheating progress bar.
    constexpr uint8_t MAX_FAULTY_MEASUREMENT_ATTEMPTS = 3;
    ///< Maximum number of retries allowed for sensor CO2 measurements before declaring an invalid result.
    constexpr int MIN_VALID_CO2_VALUE_PPM = 400;
    ///< The minimum acceptable CO2 measurement value for MH-Z19B sensor in ppm (400 as per the datasheet).
    constexpr int MAX_VALID_CO2_VALUE_PPM = 5000;
    ///< The maximum acceptable CO2 measurement value for MH-Z19B sensor in ppm (5'000 as per the used library).


    MHZ co2_sensor(PWM_PIN, MHZ::MHZ19B);
    ///< The CO2 sensor object instance initialized with the appropriate pin and sensor type.

    void initialize() {
        pinMode(PWM_PIN, INPUT); // Set pin Mode for sensor.
        set_sensor_use_time_stamp(); // Set time stamp, for sensor use.
        char init_message[INIT_MESSAGE_LENGTH] = "";
        ///< Buffer to store the initialization message that combines the sensor name and status.
        concat_strings(init_message, INIT_MESSAGE_LENGTH, SENSOR_NAME, INIT);
        TRACE_LN_s(init_message);
        DisplayController::output(init_message, ""); // Display init message.
        wait_until_time_passed(AirQualityMeter::state.last_co2_sensor_used_time_stamp_ms, RESPONSE_TIME_MS);
        preheat_sensor();
    }

    int get_measurement_in_ppm() {
        for (int attempt = 0; attempt < MAX_FAULTY_MEASUREMENT_ATTEMPTS; attempt++) {
            ///< `attempt` is the current retry count for fetching a valid measurement from the sensor.
            TRACE_LN_d(attempt);

            // Wait for the minimum cycle time to ensure valid readings
            wait_until_time_passed(AirQualityMeter::state.last_co2_sensor_used_time_stamp_ms, RESPONSE_TIME_MS);

            // Read CO2 value through PWM and return if valid, otherwise retry
            const int ppm_pwm = co2_sensor.readCO2PWM();
            ///< The CO2 reading in ppm retrieved using the PWM interface of the sensor.
            set_sensor_use_time_stamp();
            if (ppm_pwm >= MIN_VALID_CO2_VALUE_PPM && ppm_pwm <= MAX_VALID_CO2_VALUE_PPM) {
                return ppm_pwm; // Return valid value.
            }
            TRACE_LN_d(ppm_pwm);
        }
        invalid_measurement_error_handler();
        return MEASUREMENT_NOT_VALID_ERROR; // Return error code, if no valid value was measured.
    }

    void set_sensor_use_time_stamp() {
        AirQualityMeter::state.last_co2_sensor_used_time_stamp_ms = millis();
        TRACE_LN_u(AirQualityMeter::state.last_co2_sensor_used_time_stamp_ms);
    }

    void wait_until_time_passed(const unsigned long time_stamp_since_time_has_to_pass_ms,
                                const unsigned long time_to_pass_ms) {
        const unsigned long current_time = millis(); ///< Current time in milliseconds since the system started.
        const unsigned long time_passed_ms = current_time - time_stamp_since_time_has_to_pass_ms;
        ///< Time elapsed since the specified timestamp.
        TRACE_LN_u(time_passed_ms);
        TRACE_LN_u(time_to_pass_ms);
        if (time_passed_ms < time_to_pass_ms) {
            const unsigned long time_to_wait_ms = time_to_pass_ms - time_passed_ms;
            ///< Remaining time to wait (in milliseconds) if the required interval has not yet passed.
            Log.traceln("%s%u", LogController::DELAY_TIME, time_to_wait_ms);
            NotBlockingTimeHandler::wait_ms(time_to_wait_ms);
        }
    }

    void concat_strings(char *buffer, const size_t buffer_size, const char *string_1,
                        const char *string_2) {
        snprintf(buffer, buffer_size, "%s %s", string_1, string_2);
    }

    void preheat_sensor() {
        if (co2_sensor.isPreHeating()) {
            set_sensor_use_time_stamp();
            char preheat_message[PREHEAT_MESSAGE_LENGTH];
            ///< Buffer to store the preheating status message displayed to the user.
            concat_strings(preheat_message, PREHEAT_MESSAGE_LENGTH, SENSOR_NAME, PREHEAT);
            TRACE_LN_s(preheat_message);
            int progress_bar_counter = 0; ///< Counter to track the progress bar's current position during preheating.
            char display_row_2[DisplayController::DISPLAY_WIDTH + 1] = "";
            ///< Buffer to hold the content of the second row of the display (progress bar).
            do {
                set_sensor_use_time_stamp();
                display_preheat_progress_bar(preheat_message, display_row_2, DisplayController::DISPLAY_WIDTH,
                                             &progress_bar_counter);
                wait_until_time_passed(AirQualityMeter::state.last_co2_sensor_used_time_stamp_ms,
                                       PREHEAT_PROGRESS_BAR_UNIT_PROGRESS_MS);
            } while (co2_sensor.isPreHeating());
            set_sensor_use_time_stamp();
        }
    }

    void display_preheat_progress_bar(const char *row_1, char *row_2_buffer, const uint8_t bar_with,
                                      int *progress_bar_counter) {
        TRACE_LN_d(*progress_bar_counter);
        if (*progress_bar_counter > 0 && *progress_bar_counter <= bar_with) {
            ///< Start showing progress only, when there is a progress (> 0)
            ///< Show progress until progress bar is 'full' (<= bar_with)
            row_2_buffer[*progress_bar_counter - 1] = *PROGRESS_BAR_SYMBOL;
            ///< Updates the progress bar buffer with the next progress symbol.
        }
        (*progress_bar_counter)++; ///< Increments the progress bar counter by one for the next step.
        DisplayController::output(row_1, row_2_buffer);
        TRACE_LN_s(row_1);
        TRACE_LN_s(row_2_buffer);
    }

    void invalid_measurement_error_handler() {
        Log.errorln(SensorError::MEASUREMENT_NOT_VALID);
        LedArray::output(LedErrorPatterns::SENSOR_ERROR_MEASUREMENT_NOT_VALID);
        Log.verboseln(LogController::LED_UPDATED);
        DisplayController::output(GeneralError::ERROR_MESSAGE_ROW_ONE, SensorError::MEASUREMENT_NOT_VALID);
        Log.verboseln(LogController::DISPLAY_UPDATED);
        NotBlockingTimeHandler::wait_ms(WAITING_PERIOD_FOR_DISPLAY_MESSAGES_MS);
    }
}
