/**
 * @file    co2_sensor_controller.cpp
 * @brief   This file contains the function definitions for the CO2 sensor.
 */

#include <Arduino.h>
#include <co2_sensor_controller.h>
#include "pin_configuration.h"

namespace Co2SensorController {
    //TODO: declare variables and objects, that are only used in this file here.

    void initialize() {
        //TODO: This function needs to be finalized. (all the stuff, that should run on device startup)
    }


    int get_measurement_in_ppm() {
        //TODO: This function needs to be written. (all the stuff that runs on every loop iteration)
        return 1500; //FIXME: this is a placeholder value. Fix when writing this function.
    }
}
