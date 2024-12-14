#include <Arduino.h>

/**
 * @file    co2_sensor.cpp
 * @brief   This file contains the function definitions for the CO2 sensor.
 */

#include "co2_sensor.h"
#include "pin_configuration.h"

void initialize_co2_sensor() {
    Serial1.begin(9600); // Initialize Serial communication on Serial1 (PINs 18 and 19) for CO2 sensor
    //TODO: This function needs to be finalized. (all the stuff, that should run on device startup)
}


int get_co2_measurement_in_ppm() {
    //TODO: This function needs to be written. (all the stuff that runs on every loop iteration)
    return 1500; //FIXME: this is a placeholder value. Fix when writing this function.
}
