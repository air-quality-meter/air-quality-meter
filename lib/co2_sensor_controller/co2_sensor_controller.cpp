#include <co2_sensor_controller.h>
#include <pin_configuration.h>
#include <../lib/display_controller/display_controller.h>
#include <MHZ.h>
#include <state.h>

void set_sensor_use_time_stamp();

void wait_until_time_passed(unsigned long time_stamp_since_time_has_to_pass_ms, unsigned long time_to_pass_ms);

constexpr char SENSOR_NAME[] = "MHZ 19B";
constexpr char INIT[] = "Initializing";
constexpr char PREHEAT[] = "Preheating";
constexpr char PROGRESS_BAR_SYMBOL[] = "#";
constexpr char PREHEAT_COMPLETE[] = "Preheating complete.";
constexpr size_t SENSOR_NAME_LENGTH = sizeof(SENSOR_NAME) - 1;
constexpr size_t INIT_LENGTH = sizeof(INIT) - 1;
constexpr size_t PREHEAT_LENGTH = sizeof(PREHEAT) - 1;
constexpr size_t INIT_MESSAGE_LENGTH = SENSOR_NAME_LENGTH + INIT_LENGTH + 1;
constexpr size_t PREHEAT_MESSAGE_LENGTH = SENSOR_NAME_LENGTH + PREHEAT_LENGTH + 1;
constexpr unsigned long PREHEATING_TIME_MS = 180000; // 3 minutes. See data sheet.
constexpr unsigned long CYCLE_TIME_MS = 1004; // See data sheet.
constexpr uint8_t CYCLE_TIME_MARGIN_PERCENT = 5; // See data sheet.
constexpr unsigned long MIN_CYCLE_WAIT_TIME_MS = CYCLE_TIME_MS + (CYCLE_TIME_MS * CYCLE_TIME_MARGIN_PERCENT) / 100;
constexpr unsigned long WAITING_PERIOD_AFTER_PWM_INIT_MS = 500;
constexpr unsigned long PREHEAT_PROGRESS_BAR_UNIT_PROGRESS_MS =
        PREHEATING_TIME_MS / DisplayController::DISPLAY_WIDTH;
constexpr uint8_t MAX_FAULTY_MEASUREMENT_ATTEMPTS = 3;
constexpr int MIN_VALID_CO2_VALUE_PPM = 400; // See data sheet.
constexpr int MAX_VALID_CO2_VALUE_PPM = 10000; // See data sheet.

namespace Co2SensorController {
    MHZ co2_sensor(PWM_PIN, MHZ::MHZ19B);

    void initialize() {
        pinMode(PWM_PIN, INPUT); // Set pin Mode for sensor.
        co2_sensor.setAutoCalibrate(false);
        set_sensor_use_time_stamp(); // Set time stamp, for sensor use.
        char init_message[INIT_MESSAGE_LENGTH] = "";
        snprintf(init_message, INIT_MESSAGE_LENGTH, "%s %s", SENSOR_NAME, INIT); // Format init message
        DisplayController::output(init_message, ""); // Display init message.

        wait_until_time_passed(AirQualityMeter::state.last_co2_sensor_used_time_stamp_ms, MIN_CYCLE_WAIT_TIME_MS);
        // Wait for Sensor to be ready for use.
        if (co2_sensor.isPreHeating()) {
            set_sensor_use_time_stamp();
            char preheat_message[PREHEAT_MESSAGE_LENGTH];
            snprintf(preheat_message, PREHEAT_MESSAGE_LENGTH, "%s %s", SENSOR_NAME, PREHEAT);
            uint8_t progress_bar_counter = 0;
            char display_row_2[DisplayController::DISPLAY_WIDTH + 1] = "";
            do {
                set_sensor_use_time_stamp();
                if (progress_bar_counter < DisplayController::DISPLAY_WIDTH) {
                    display_row_2[progress_bar_counter] = *PROGRESS_BAR_SYMBOL;
                }
                DisplayController::output(preheat_message, display_row_2);
                progress_bar_counter++;
                wait_until_time_passed(AirQualityMeter::state.last_co2_sensor_used_time_stamp_ms,
                                       PREHEAT_PROGRESS_BAR_UNIT_PROGRESS_MS);
            } while (co2_sensor.isPreHeating());
            set_sensor_use_time_stamp();
        }
    }

    int get_measurement_in_ppm() {
        for (int i = 0; i < MAX_FAULTY_MEASUREMENT_ATTEMPTS; i++) {
            wait_until_time_passed(AirQualityMeter::state.last_co2_sensor_used_time_stamp_ms, MIN_CYCLE_WAIT_TIME_MS);
            const int ppm_pwm = co2_sensor.readCO2PWM();
            set_sensor_use_time_stamp();
            if (ppm_pwm >= MIN_VALID_CO2_VALUE_PPM && ppm_pwm <= MAX_VALID_CO2_VALUE_PPM) {
                return ppm_pwm;
            }
        }
        return -1;
    }
}

void set_sensor_use_time_stamp() {
    AirQualityMeter::state.last_co2_sensor_used_time_stamp_ms = millis();
}

void wait_until_time_passed(const unsigned long time_stamp_since_time_has_to_pass_ms,
                            const unsigned long time_to_pass_ms) {
    unsigned long current_time = millis();
    while (current_time - time_stamp_since_time_has_to_pass_ms < time_to_pass_ms) {
        current_time = millis();
    }
}
