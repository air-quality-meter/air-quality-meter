# Air quality meter

This project implements a CO2 monitoring device using an Arduino Mega 2560. The device measures CO2 concentration in ppm, displays the value on an LCD screen, and provides visual and audio warnings when CO2 levels exceed a predefined threshold.

## Functionality

The device operates as follows:

1. **CO2 Measurement:** The device continuously measures the CO2 concentration in the surrounding environment using a MH-Z19B CO2 sensor.

2. **Display:** The measured CO2 value is displayed on an LCD1602 LCD screen.

3. **LED Indicators:** Two LEDs provide a visual indication of the CO2 level:
  - Green: Good air quality (CO2 ≤ 800 ppm)
  - Yellow: Moderate air quality (800 ppm < CO2 ≤ 1400 ppm)
  - Red: Poor air quality (CO2 > 1400 ppm)

4. **Audio Warning:** If the CO2 level exceeds the threshold (1400 ppm) for a prolonged period, the device triggers an audio warning using a Gravity UART MP3 Voice Module and a 3W 8Ω Stereo Enclosed Speaker. The warning is repeated at set intervals until the CO2 level falls below the threshold or the device is reset.

5. **Reset Button:** A reset button allows the user to manually silence the audio warning and reset the warning counter.

## Hardware Components

* **Microcontroller:** Arduino Mega 2560
* **CO2 Sensor:** MH-Z19B Infrared CO2 Sensor Module
* **Display:** LCD1602 Module (with pin header)
* **Audio Module:** Gravity UART MP3 Voice Module
* **Speaker:** Stereo Enclosed Speaker - 3W 8Ω
* **LEDs:** 2x Green, 2x Yellow, 2x Red
* **Reset Button:** Push button

## Software Logic

The Arduino code implements the following logic:

1. **Initialization:** Sets up the pins, initializes the starting values, and configures the interrupt for the reset button.

2. **Measurement:** Continuously reads the CO2 sensor and updates the displayed value.

3. **LED Control:** Sets the appropriate LED colors based on the CO2 level.

4. **Warning Logic:**
  - Monitors the CO2 level and the time spent above the threshold.
  - Triggers an audio warning if the threshold is exceeded for a prolonged period.
  - Implements a waiting period between warnings to avoid continuous alarms.
  - Resets the warning counter after a predefined number of consecutive warnings or when the CO2 level falls below the threshold.

5. **Reset Button:**  An interrupt service routine resets the warning counter and the timer when the reset button is pressed.

## License

This project is licensed under the MIT License.


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
| GND                         | Analog-Eingang, Digitaler I/O              | LCD 1602 (2x), Potentiometer (1x) |
