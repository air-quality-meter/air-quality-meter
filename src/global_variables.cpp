#include "global_variables.h"

unsigned long current_time_s = 0;
///< Current timestamp (time since board is powered on or since last overflow of millis()) (seconds)

int current_co2_measurement_ppm = 0;
///< Current CO2 measurement in parts per million (ppm)

volatile unsigned long last_co2_below_threshold_time_s = 0;
///< Timestamp of last CO2 measurement below threshold (seconds) to calculate the elapsed time, since CO2 concentration
///< is too high. Used to manage warnings and warning intervals

volatile int warning_counter = 0;
///< Counter for consecutive warnings
