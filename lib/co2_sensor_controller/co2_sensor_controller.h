#include <MHZ.h>

/**
 * @file    co2_sensor_controller.h
 * @brief   This file contains the function declarations for the CO2 sensor.
 */

#ifndef CO2_SENSOR_CONTROLLER_H
#define CO2_SENSOR_CONTROLLER_H

namespace Co2SensorController
{

#define CO2_IN 4

	extern MHZ co2;

	/**
	 * @brief   Initializes the CO2 sensor module.
	 */
	void initialize();

	/**
	 * @brief   Retrieves a CO2 measurement.
	 * @details Reads the CO2 value from the sensor and provides the measurement in parts per million (ppm).
	 *          Sensor used: MH-Z19B Infrared CO2 Sensor Module.
	 * @return  The current CO2 measurement in ppm.
	 */
	int get_measurement_in_ppm();
}

#endif // CO2_SENSOR_CONTROLLER_H
