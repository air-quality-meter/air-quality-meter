/**
   * @file state.h
   * @brief Defines the state structure and global state instance for the air quality meter.
   *
   * @details This file contains the `State` structure used to track time-dependent and
   * warning-related system metrics, along with a global state instance to be shared
   * across the application.
   */

#ifndef STATE_H
#define STATE_H


namespace AirQualityMeter {
  struct State {
    volatile unsigned long last_co2_below_threshold_time_ms; ///< Last time (in ms) when CO2 was below threshold.
    volatile int warning_counter; ///< Counter tracking the number of warnings triggered.
    volatile unsigned long last_co2_sensor_used_time_stamp_ms; ///< Last time (in ms) the CO2 sensor was activated.
  };

  extern State state; ///< Global state instance to manage runtime metrics and warnings.
}

#endif //STATE_H
