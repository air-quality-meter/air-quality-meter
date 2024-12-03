# air-quality-meter
Microcontroller board with sensors, display and audio module for measuring and displaying indoor air quality and issuing warnings

## logic
### loop:
- set the current timestamp
- get the current measurement from co2 sensor
- display the current co2 measurement on the display
- set the LEDs according to the CO2 measurement value
- check if reset button was pressed
  - reset timestamp

- check whether the current CO2 measurement is above the threshold value
  - check whether the CO2 threshold value has already been exceeded for longer than the maximum period of time
    - issue an audio warning
    - adjust the timestamp to wait until the next audio warning
    - increase the warning counter
    - reset timestamp when the maximum number of warnings has been reached
- else reset timestamp
