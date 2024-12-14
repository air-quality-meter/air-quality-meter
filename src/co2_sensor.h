/**
 * @file    co2_sensor.h
 * @brief   This file contains the function declarations for the CO2 sensor.
 */

#ifndef CO2_SENSOR_H
#define CO2_SENSOR_H

/**
 * @brief   Initializes the CO2 sensor module.
 */
void initialize_co2_sensor();

/**
 * @brief   Retrieves a CO2 measurement.
 * @details Reads the CO2 value from the sensor and provides the measurement in parts per million (ppm).
 *          Sensor used: MH-Z19 Infrared CO2 Sensor Module MH-Z19B
 * @return  The current CO2 measurement in ppm.
 */
int get_co2_measurement_in_ppm();

#endif //CO2_SENSOR_H
