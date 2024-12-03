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



## Pin-Tabelle: Zuweisung

| **Pin/Port**                | **Erläuterung**                            | **Zuweisung**                     |
|-----------------------------|--------------------------------------------|---------------                    |
| Digital Pin 0 (RX0)         | Digitaler I/O, UART RX (Serial0)           |                                   |
| Digital Pin 1 (TX0)         | Digitaler I/O, UART TX (Serial0)           |                                   |                                    
| Digital Pin 2               | Digitaler I/O                              |                                   |
| Digital Pin 3 (PWM)         | Digitaler I/O, PWM                         |                                   |
| Digital Pin 4               | Digitaler I/O                              |                                   |
| Digital Pin 5 (PWM)         | Digitaler I/O, PWM                         |                                   |
| Digital Pin 6 (PWM)         | Digitaler I/O, PWM                         |                                   |
| Digital Pin 7               | Digitaler I/O                              | LCD 1602                          |
| Digital Pin 8               | Digitaler I/O                              | LCD 1602                          |
| Digital Pin 9 (PWM)         | Digitaler I/O, PWM                         | LCD 1602                          |
| Digital Pin 10 (PWM)        | Digitaler I/O, PWM                         | LCD 1602                          |
| Digital Pin 11 (PWM)        | Digitaler I/O, PWM                         | LCD 1602                          |
| Digital Pin 12              | Digitaler I/O                              | LCD 1602                          |
| Digital Pin 13 (LED_BUILTIN)| Digitaler I/O, Onboard LED                 |                                   |
| Digital Pin 14 (TX3)        | Digitaler I/O, UART TX (Serial3)           |                                   |
| Digital Pin 15 (RX3)        | Digitaler I/O, UART RX (Serial3)           |                                   |
| Digital Pin 16 (TX2)        | Digitaler I/O, UART TX (Serial2)           |                                   |
| Digital Pin 17 (RX2)        | Digitaler I/O, UART RX (Serial2)           |                                   |
| Digital Pin 18 (TX1)        | Digitaler I/O, UART TX (Serial1)           |                                   |
| Digital Pin 19 (RX1)        | Digitaler I/O, UART RX (Serial1)           |                                   |
| Digital Pin 20 (SDA)        | Digitaler I/O, I2C-Datenleitung (SDA)      |                                   |
| Digital Pin 21 (SCL)        | Digitaler I/O, I2C-Taktleitung (SCL)       |                                   |
| Digital Pin 22              | Digitaler I/O                              |                                   |
| Digital Pin 23              | Digitaler I/O                              |                                   |
| Digital Pin 24              | Digitaler I/O                              |                                   |
| Digital Pin 25              | Digitaler I/O                              |                                   |
| Digital Pin 26              | Digitaler I/O                              |                                   |
| Digital Pin 27              | Digitaler I/O                              |                                   |
| Digital Pin 28              | Digitaler I/O                              |                                   |
| Digital Pin 29              | Digitaler I/O                              |                                   |
| Digital Pin 30              | Digitaler I/O                              |                                   |
| Digital Pin 31              | Digitaler I/O                              |                                   |
| Digital Pin 32              | Digitaler I/O                              |                                   |
| Digital Pin 33              | Digitaler I/O                              |                                   |
| Digital Pin 34              | Digitaler I/O                              |                                   |
| Digital Pin 35              | Digitaler I/O                              |                                   |
| Digital Pin 36              | Digitaler I/O                              |                                   |
| Digital Pin 37              | Digitaler I/O                              |                                   |
| Digital Pin 38              | Digitaler I/O                              |                                   |
| Digital Pin 39              | Digitaler I/O                              |                                   |
| Digital Pin 40              | Digitaler I/O                              |                                   |
| Digital Pin 41              | Digitaler I/O                              |                                   |
| Digital Pin 42              | Digitaler I/O                              |                                   |
| Digital Pin 43              | Digitaler I/O                              |                                   |
| Digital Pin 44 (PWM)        | Digitaler I/O, PWM                         |                                   |
| Digital Pin 45 (PWM)        | Digitaler I/O, PWM                         |                                   |
| Digital Pin 46 (PWM)        | Digitaler I/O, PWM                         |                                   |
| Digital Pin 47              | Digitaler I/O                              |                                   |
| Digital Pin 48              | Digitaler I/O                              |                                   |
| Digital Pin 49              | Digitaler I/O                              |                                   |
| Digital Pin 50 (MISO)       | Digitaler I/O, SPI-Datenleitung (MISO)     |                                   |
| Digital Pin 51 (MOSI)       | Digitaler I/O, SPI-Datenleitung (MOSI)     |                                   |
| Digital Pin 52 (SCK)        | Digitaler I/O, SPI-Taktleitung             |                                   |
| Digital Pin 53 (SS)         | Digitaler I/O, SPI-Slave-Select            |                                   |
| Analog Pin 0 (A0)           | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 1 (A1)           | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 2 (A2)           | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 3 (A3)           | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 4 (A4)           | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 5 (A5)           | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 6 (A6)           | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 7 (A7)           | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 8 (A8)           | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 9 (A9)           | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 10 (A10)         | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 11 (A11)         | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 12 (A12)         | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 13 (A13)         | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 14 (A14)         | Analog-Eingang, Digitaler I/O              |                                   |
| Analog Pin 15 (A15)         | Analog-Eingang, Digitaler I/O              |                                   |
| V3.3                        | Analog-Eingang, Digitaler I/O              |                                   |
| V5                          | Analog-Eingang, Digitaler I/O              | LCD 1602 (2x), Potentiometer (1x) |
| GND                         | Analog-Eingang, Digitaler I/O              | LCD 1602 (2x)                     |
