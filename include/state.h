
#ifndef STATE_H
#define STATE_H


namespace AirQualityMeter {
  struct State {
    volatile unsigned long last_co2_below_threshold_time_s;
    volatile int warning_counter;
  };

  extern State state;
}

#endif //STATE_H
