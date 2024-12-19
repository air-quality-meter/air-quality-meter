
#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

struct SystemState {
  volatile unsigned long last_co2_below_threshold_time_s;
  volatile int warning_counter;
};

extern SystemState system_state;

#endif //SYSTEM_STATE_H
