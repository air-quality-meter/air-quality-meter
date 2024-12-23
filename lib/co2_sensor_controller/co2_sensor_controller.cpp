/**
 * @file    co2_sensor_controller.cpp
 * @brief   This file contains the function definitions for the CO2 sensor.
 */

#include <Arduino.h>
#include <co2_sensor_controller.h>
#include "pin_configuration.h"

void initialize_co2_sensor() {
    Serial1.begin(9600);
    ///< Initialize Serial communication on Serial1 (PINs 18 and 19) for CO2 sensor with baud rate 9600.
    //TODO: This function needs to be finalized. (all the stuff, that should run on device startup)
}


int get_co2_measurement_in_ppm() {
    //TODO: This function needs to be written. (all the stuff that runs on every loop iteration)
    return 1500; //FIXME: this is a placeholder value. Fix when writing this function.
}
