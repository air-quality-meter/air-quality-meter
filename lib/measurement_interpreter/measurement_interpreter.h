#ifndef MEASUREMENT_INTERPRETER_H
#define MEASUREMENT_INTERPRETER_H

#include <air_quality.h>

/**
 * @brief   Determines the air quality level based on the provided CO2 measurement in ppm.
 *
 * @details This function evaluates the given CO2 measurement against predefined air quality levels
 *          and returns the corresponding level. The levels define thresholds, descriptions, and
 *          LED indicator states for various air quality levels.
 *
 * @param   co2_measurement_ppm The CO2 concentration measurement in parts per million (ppm).
 *
 * @return  The air quality level corresponding to the given CO2 measurement.
 */
AirQuality::Level get_air_quality_level(int co2_measurement_ppm);

#endif //MEASUREMENT_INTERPRETER_H
