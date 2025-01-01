# Air quality meter

This project builds a CO2 monitoring device using an Arduino Mega 2560. The device measures the CO2 concentration in
ppm, displays the value on an LCD display (LCD1602 Module (with pin header) and gives visual and acoustic warnings when
the CO2 concentration exceeds a predefined threshold.

## Functionality

The device operates as follows:

1. **CO2 Measurement:** The device continuously measures the CO2 concentration in the surrounding environment using a
   MH-Z19B Infrared CO2 Sensor Module.

2. **Display:** The measured CO2 value is displayed on an LCD1602 display.

3. **LED Indicators:** Six LEDs (2x Green, 2x Yellow, 2x Red) provide a visual indication of the CO2 level based on DIN
   EN 13779 see: https://www.umweltbundesamt.de/sites/default/files/medien/publikation/long/4113.pdf (Table 3):
    - **High air quality (IDA 1):** Both green LEDs light up (CO2 ≤ 800 ppm).
    - **Medium air quality (IDA 2):** One green and one yellow LED light up (800 ppm < CO2 ≤ 1000 ppm).
    - **Moderate air quality (IDA 3):**  Both yellow LEDs light up (1000 ppm < CO2 ≤ 1200 ppm), or one yellow and one
      red LED light up (1200 ppm < CO2 ≤ 1400 ppm).
    - **Poor air quality (IDA 4):** Both red LEDs light up (CO2 > 1400 ppm).

4. **Audio Warning:** If the CO2 level exceeds the threshold for poor air quality (1400 ppm) for a prolonged period, the
   device triggers an audio warning using a Gravity UART MP3 Voice Module and a 3W 8Ω Stereo Enclosed Speaker. The
   warning is repeated at set intervals until the CO2 level falls below the threshold, the max number of consecutive
   warning is reached, or the warning is acknowledged.

5. **Acknowledge Button:** A acknowledge button allows the user to manually silence the audio warning and reset the
   warning counter.

## Hardware Components

* **Microcontroller:** Arduino Mega 2560
* **CO2 Sensor:** MH-Z19B Infrared CO2 Sensor Module
* **Display:** LCD1602 Module (with pin header)
* **Audio Module:** Gravity UART MP3 Voice Module
* **Speaker:** Stereo Enclosed Speaker - 3W 8Ω
* **LEDs:** 2x Green, 2x Yellow, 2x Red
* **Acknowledge Button:** Push button

## Software Logic

The Arduino code implements the following logic:

1. **Initialization:** Sets up the pins, initializes the starting values, and configures the interrupt for the
   acknowledge
   button.

2. **Measurement:** Continuously reads the CO2 sensor and updates the displayed value.

3. **LED Control:** Sets the appropriate LED colors based on the CO2 level.

4. **Warning Logic:**

- Monitors the CO2 level and the time spent above the threshold.
- Triggers an audio warning if the threshold is exceeded for a prolonged period.
- Implements a waiting period between warnings to avoid continuous alarms.
- Resets the warning counter after a predefined number of consecutive warnings or when the CO2 level falls below the
  threshold.

5. **Acknowledge Button:**  An interrupt service routine resets the warning counter and the timer when the acknowledge
   button is pressed.

## Arduino Pin Configuration

This table details the pin connections for the Arduino Mega 2560 in this project.

| Pin Number | Pin Info | Serial Port | Connected Device                   | Device Connection              |
|------------|----------|-------------|------------------------------------|--------------------------------|
| 2          | INT0     |             | Acknowledge Button                 | "-"                            | 
| 4          | Digital  |             | MH-Z19B Infrared CO2 Sensor Module |                                |
| 7          | Digital  |             | LCD1602                            | RS                             |
| 8          | Digital  |             | LCD1602                            | E                              |
| 9          | Digital  |             | LCD1602                            | D4                             |
| 10         | Digital  |             | LCD1602                            | D5                             |
| 11         | Digital  |             | LCD1602                            | D6                             |
| 12         | Digital  |             | LCD1602                            | D7                             |
| 14         | TX3      | Serial3     | Gravity UART MP3 Voice Module      | TX                             |
| 15         | RX3      | Serial3     | Gravity UART MP3 Voice Module      | RX                             |
| 22         | Digital  |             | Green LED 1                        | Anode (+) through 1KΩ resistor |
| 24         | Digital  |             | Green LED 2                        | Anode (+) through 1KΩ resistor |
| 26         | Digital  |             | Yellow LED 1                       | Anode (+) through 1KΩ resistor |
| 28         | Digital  |             | Yellow LED 2                       | Anode (+) through 1KΩ resistor |
| 30         | Digital  |             | Red LED 1                          | Anode (+) through 1KΩ resistor |
| 32         | Digital  |             | Red LED 2                          | Anode (+) through 1KΩ resistor |

## Component Power and Ground Connections

This table shows the power and ground connections for the various components in the project.

| Component                          | Connection  | Arduino Pin    | Notes                                         |
|------------------------------------|-------------|----------------|-----------------------------------------------|
| MH-Z19B Infrared CO2 Sensor Module | Vin         | 5V             |                                               |
| MH-Z19B Infrared CO2 Sensor Module | GND         | GND            |                                               |
| LCD1602                            | VSS         | GND            |                                               |
| LCD1602                            | VDD         | 5V             |                                               |
| LCD1602                            | RW          | GND            |                                               |
| LCD1602                            | A           | 5V             | Through 220Ω resistor                         |
| LCD1602                            | K           | GND            |                                               |
| B103 (10K Potentiometer)           | Outer Pin 1 | GND            |                                               |
| B103 (10K Potentiometer)           | Outer Pin 2 | 5V             |                                               |
| Acknowledge Button                 | "-"         | GND            |                                               |
| Green LED 1                        | Cathode (-) | GND            |                                               |
| Green LED 2                        | Cathode (-) | GND            |                                               |
| Yellow LED 1                       | Cathode (-) | GND            |                                               |
| Yellow LED 2                       | Cathode (-) | GND            |                                               |
| Red LED 1                          | Cathode (-) | GND            |                                               |
| Red LED 2                          | Cathode (-) | GND            |                                               |
| Gravity UART MP3 Voice Module      | "+"         | 3.3V           |                                               |
| Gravity UART MP3 Voice Module      | "-"         | GND (separate) | Use a different GND pin than other components |

## Other Connections

| Component 1                   | Connection 1 | Component 2                     | Connection 2 |
|-------------------------------|--------------|---------------------------------|--------------|
| B103 (10K Potentiometer)      | Middle Pin   | LCD1602                         | VO           |
| Gravity UART MP3 Voice Module | SPK          | Stereo Enclosed Speaker - 3W 8Ω |              |

## License

This project is licensed under the MIT License.