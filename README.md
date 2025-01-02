# Air Quality Meter

The **Air Quality Meter** is an Arduino-based project that monitors **CO2 levels** in the air and provides **visual**,
**textual**, and **audible feedback** to alert users when air quality drops.

## ✨ Features

- ✅ **CO2 Measurement**: Using the **MH-Z19B sensor**, the device continuously measures CO2 levels in ppm (parts
  per million).
- ✅ **LCD Display**: The real-time CO2 levels and air-quality messages are displayed on a **16x2 LCD display**.
- ✅ **LED Indicators**:
    - **Green LEDs**: High air quality.
    - **Yellow LEDs**: Moderate air quality.
    - **Red LEDs**: Poor air quality.
- ✅ **Audio Alerts**: A **pre-recorded voice warning** is activated when CO2 levels stay above a dangerous threshold for
  too long.
- ✅ **Acknowledgment Button**: A manual button to acknowledge the alert and reset the warning system.

## 🛠️ Hardware Requirements

| **Component**                       | **Quantity** | **Description**                                            |
|-------------------------------------|--------------|------------------------------------------------------------|
| **Arduino Mega 2560**               | 1            | Main microcontroller for running the system.               |
| **MH-Z19B CO2 Sensor Module**       | 1            | CO2 sensor providing ppm measurements.                     |
| **LCD1602 Display Module**          | 1            | 16x2 LCD display for showing CO2 levels and user messages. |
| **Gravity UART MP3 Voice Module**   | 1            | Audio playback for voice alerts.                           |
| **Stereo Enclosed Speaker (3W 8Ω)** | 1            | Small speaker to output the alert sounds.                  |
| **LEDs (Green, Yellow, Red)**       | 6 (2 each)   | Visual indicators for air quality levels.                  |
| **Push Button (Acknowledgment)**    | 1            | Manual button to acknowledge alarms or reset warnings.     |
| **10K Potentiometer (B103)**        | 1            | Brightness adjustment for the LCD1602 display.             |
| Resistors (_e.g., 1KΩ or 220Ω_)     | As Needed    | For safely operating LEDs and other modules.               |
| **Jumper Wires + Breadboard**       | As Needed    | For wiring all components on a prototyping circuit.        |

## 🚦 LED Indicator System

The **Air Quality Meter** uses six LEDs to visually represent the current air quality or error states. The LEDs are as
follows:

- **Green LED 1** (G1) and **Green LED 2** (G2)
- **Yellow LED 1** (Y1) and **Yellow LED 2** (Y2)
- **Red LED 1** (R1) and **Red LED 2** (R2)

Each LED pattern signifies a specific air quality level or an error condition. Below is the list of all possible
patterns:

| **G1** | **G2** | **Y1** | **Y2** | **R1** | **R2** | **Pattern Name**                   | **Range**        | **DIN EN 13779 level** |
|--------|--------|--------|--------|--------|--------|------------------------------------|------------------|------------------------|
| 🟢     | 🟢     | ⚫️     | ⚫️     | ⚫️     | ⚫️     | **High indoor air quality**        | `400-800 ppm`.   | IDA 1                  |
| ⚫️     | 🟢     | 🟡     | ⚫️     | ⚫️     | ⚫️     | **Medium indoor air quality**      | `800-1100 ppm`.  | IDA 2                  |
| ⚫️     | ⚫️     | 🟡     | 🟡     | ⚫️     | ⚫️     | **Moderate indoor air quality I**  | `1100-1300 ppm`. | IDA 3                  |
| ⚫️     | ⚫️     | ⚫️     | 🟡     | 🔴     | ⚫️     | **Moderate indoor air quality II** | `1300-1400 ppm`. | IDA 3                  |
| ⚫️     | ⚫️     | ⚫️     | ⚫️     | 🔴     | 🔴     | **Poor indoor air quality**        | `>1400 ppm`.     | IDA 4                  |

### ⛔ Error Conditions

If the sensor encounters a problem, specific LED patterns indicate the type of error:

| **G1** | **G2** | **Y1** | **Y2** | **R1** | **R2** | **Error Pattern Name**    | **Description**                                                              |
|--------|--------|--------|--------|--------|--------|---------------------------|------------------------------------------------------------------------------|
| ⚫️     | ⚫️     | 🟡     | 🟡     | 🔴     | 🔴     | **Sensor Not Connected**  | Indicates the sensor is not physically connected to the system.              |
| 🟢     | 🟢     | 🟡     | 🟡     | 🔴     | 🔴     | **Measurement Not Valid** | The system is unable to retrieve a valid measurement from the sensor module. |

### 💡 Legend for LED Colors

| **Color** | **Meaning** |
|-----------|-------------|
| 🟢🟡🔴    | LED is ON   |
| ⚫️ Grey   | LED is OFF  |

This classification ensures users can quickly interpret the air quality status or diagnose sensor errors visually.

## 🔌 Connections

### 🖼️ Wiring Diagram

![Arduino Air Quality Meter Wiring.jpg](img/Arduino%20Air%20Quality%20Meter%20Wiring.jpg)

### 📌 Arduino Pin Connections Table

This table shows all the **pins used** in the project, including their roles and connected components. Each pin plays a
specific role in enabling the functionality of the air quality meter.

| **Pin Number** | **Connected Component**                   | **Description**                                 |
|----------------|-------------------------------------------|-------------------------------------------------|
| `2 (INT0)`     | 🔘 **Acknowledge Button**                 | (-) Used for acknowledging or stopping alerts.  |
| `4`            | 💨 **CO2 Sensor (MH-Z19B)** (PWM)         | Connected to the CO2 sensor's PWM pin.          |
| `7`            | 📟 **LCD1602 Display** (RS)               | Register Select for the LCD Display.            |
| `8`            | 📟 **LCD1602 Display** (E)                | Enable Pin for the LCD Display.                 |
| `9`            | 📟 **LCD1602 Display** (D4)               | Data line 4 for the LCD Display.                |
| `10`           | 📟 **LCD1602 Display** (D5)               | Data line 5 for the LCD Display.                |
| `11`           | 📟 **LCD1602 Display** (D6)               | Data line 6 for the LCD Display.                |
| `12`           | 📟 **LCD1602 Display** (D7)               | Data line 7 for the LCD Display.                |
| `14 (TX3)`     | 🎵 **Gravity UART MP3 Voice Module** (TX) | Serial communication TX pin for the MP3 Module. |
| `15 (RX3)`     | 🎵 **Gravity UART MP3 Voice Module** (RX) | Serial communication RX pin for the MP3 Module. |
| `22`           | 🟢 **Green LED 1**                        | Anode (+) through ➡️〰️ 1KΩ resistor             |
| `24`           | 🟢 **Green LED 2**                        | Anode (+) through ➡️〰️ 1KΩ resistor             |                                               |
| `26`           | 🟡 **Yellow LED 1**                       | Anode (+) through ➡️〰️ 1KΩ resistor             |                                               |
| `28`           | 🟡 **Yellow LED 2**                       | Anode (+) through ➡️〰️ 1KΩ resistor             |                                               |
| `30`           | 🔴 **Red LED 1**                          | Anode (+) through ➡️〰️ 1KΩ resistor             |                                               |
| `32`           | 🔴 **Red LED 2**                          | Anode (+) through ➡️〰️ 1KΩ resistor             |    the components used in the project. Ensuring correct power

### ⚡ Power and Ground Connections Table

This table provides a detailed overview of the **power and ground connections** for the components used in the project.
Proper wiring ensures stability and optimal performance of the system.

| **Arduino Pin**  | **Component**                         | **Connection**  | **Notes**                                     |
|------------------|---------------------------------------|-----------------|-----------------------------------------------|
| `5V`             | 💨  **CO2 Sensor (MH-Z19B)**          | Vin             | Provides operating power to the CO2 sensor.   |
| `GND`            | 💨  **CO2 Sensor (MH-Z19B)**          | GND             | Ground connection for the CO2 sensor.         |
| `GND`            | 📟  **LCD1602 Display**               | VSS (Ground)    | Ground pin for the LCD module.                |
| `5V`             | 📟  **LCD1602 Display**               | VDD (Power)     | Supply power pin for the LCD module.          |
| `GND`            | 📟  **LCD1602 Display**               | RW (Read/Write) | Set to GND for write-only operation.          |
| `5V`             | 📟  **LCD1602 Backlight**             | A (Anode +)     | Backlight power through a ➡️〰️ 220Ω resistor. |
| `GND`            | 📟  **LCD1602 Backlight**             | K (Cathode -)   | Ground connection for the LCD backlight.      |
| `GND`            | 🔘  **Acknowledge Button**            | -               | Connected to ground for button functionality. |
| `GND`            | 🎚️ **10K Potentiometer (B103)**      | Outer Pin 1     | First pin connected to ground.                |
| `5V`             | 🎚️ **10K Potentiometer (B103)**      | Outer Pin 2     | Second pin connected to power.                |
| `GND`            | 🟢  **Green LED 1**                   | Cathode (-)     | Ground for the first green LED.               |
| `GND`            | 🟢  **Green LED 2**                   | Cathode (-)     | Ground for the second green LED.              |
| `GND`            | 🟡  **Yellow LED 1**                  | Cathode (-)     | Ground for the first yellow LED.              |
| `GND`            | 🟡  **Yellow LED 2**                  | Cathode (-)     | Ground for the second yellow LED.             |
| `GND`            | 🔴  **Red LED 1**                     | Cathode (-)     | Ground for the first red LED.                 |
| `GND`            | 🔴  **Red LED 2**                     | Cathode (-)     | Ground for the second red LED.                |
| `3.3V`           | 🎵  **Gravity UART MP3 Voice Module** | + (Power)       | Operates with 3.3V power.                     |
| `GND` (separate) | 🎵  **Gravity UART MP3 Voice Module** | - (Ground)      | Use a separate ground pin for reliability.    |

### 🔗 Other Component Connections Table

These components require additional connections between one another for proper functionality:

| **Component 1**                | **Connection** | **Component 2**                | **Connection** | **Notes**                               |
|--------------------------------|----------------|--------------------------------|----------------|-----------------------------------------|
| 🎚️ **10K Potentiometer**      | Middle Pin     | 📟 **LCD1602 Display**         | VO             | Adjusts the contrast of the LCD.        |
| 🎵 **Gravity UART MP3 Module** | SPK            | 🔊 **Stereo Enclosed Speaker** | SPK            | Provides audio output for voice alerts. |

### 💡 Notes and Recommendations

- **Backlight Resistor**: Always use a ➡️〰️ **220Ω resistor** for the LCD backlight (between pin `A` and `5V`) to
  control current and extend its lifespan.
- **LED Resistors**: Add ➡️〰️ **1kΩ resistors** in series with each LED to prevent damage to the LED and the Arduino
  pins.
- **Button Resistor**: Use a ➡️〰️ **10kΩ pull-down resistor** for the push button to avoid floating states and
  unreliable behavior.
- **Pre-check Wiring**: Double-check all power, ground, and resistor connections before powering on to prevent damage to
  components.

## 💻 Software Requirements

| **Tool**       | **Version** | **Notes**                          |
|----------------|-------------|------------------------------------|
| **PlatformIO** | Latest      | E.g. to use with VS Code or CLion. |

### Library Dependencies

Install these libraries (dependencies) in your PlatformIO project (should happen automatically during build process)

```ini
lib_deps =
    featherfly/SoftwareSerial@^1.0
    arduino-libraries/LiquidCrystal@^1.0.7
    https://github.com/thijse/Arduino-Log.git
    tobiasschuerg/MH-Z CO2 Sensors@^1.6.0
```

## 🌟 Getting Started

### 1. Clone the Repository

```shell
git clone https://github.com/air-quality-meter/air-quality-meter.git
cd air-quality-meter
```

### 2. Open the Project

Open the project in your preferred IDE (with PlatformIO plugin installed).

### 3. Upload the Code

1. Connect your Arduino Mega 2560 to the PC.
2. Upload the code using PlatformIO:

```shell
pio run --target upload
```

### 4. (optional) Monitor Serial Output

Launch the Serial Monitor for feedback:

```shell
pio device monitor
```

## 🚀 Operational Flow

### 1. System Startup

- The system initializes all modules and displays `Initializing...` on the LCD.

### 2. CO2 Monitoring

- Real-time CO2 levels are displayed on the LCD.
- LEDs light up based on the current **air quality range**.

### 3. Audio Alert

- If the CO2 level remains `>1400 ppm` for >30 seconds, the voice module warns users to ventilate.
- Press the **acknowledgment button** to stop alarms and reset LEDs.

## 🤝 Contribute

Want to enhance this project? Contributions are welcome! Please file **issues** for bugs or feature requests and submit
**pull requests** for improvements.

## 📝 License

This project is licensed under the **MIT License**.
Feel free to use, modify, or distribute this project.