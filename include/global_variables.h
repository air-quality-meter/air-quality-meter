/**
 * @file    global_variables.h
 * @brief   This file contains the global variables used in the program.
 */

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

extern unsigned long current_time_s;
///< Current timestamp (time since board is powered on or since last overflow of millis()) (seconds)

extern int current_co2_measurement_ppm;
///< Current CO2 measurement in parts per million (ppm)

extern volatile unsigned long last_co2_below_threshold_time_s;
///< Timestamp of last CO2 measurement below threshold (seconds) to calculate the elapsed time, since CO2 concentration
///< is too high. Used to manage warnings and warning intervals

extern volatile int warning_counter;
///< Counter for consecutive warnings

#endif //GLOBAL_VARIABLES_H
