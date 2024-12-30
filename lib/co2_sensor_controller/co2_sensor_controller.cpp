#include <Arduino.h>
#include <SoftwareSerial.h>
#include <MHZ.h>
#include <co2_sensor_controller.h>
#include "pin_configuration.h"

namespace Co2SensorController
{
#define CO2_IN 4

  MHZ co2(CO2_IN, MHZ::MHZ19B);

  unsigned long previousMillis = 0;
  const unsigned long delayInterval = 5000;

  void initialize()
  {
    Serial.begin(9600);

    pinMode(CO2_IN, INPUT);
    delay(100);
    Serial.println("Initializing MHZ 19B sensor...");

    co2.setDebug(true);

    if (co2.isPreHeating())
    {
      Serial.println("Preheating");
      while (co2.isPreHeating())
      {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= delayInterval)
        {
          previousMillis = currentMillis;
          Serial.print(".");
        }
      }
      Serial.println("\nPreheating complete.");
    }
  }

  int get_measurement_in_ppm()
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= delayInterval)
    {
      previousMillis = currentMillis;

      Serial.print("\n----- Time from start: ");
      Serial.print(millis() / 1000);
      Serial.println(" s");

      int ppm_pwm = co2.readCO2PWM();

      if (ppm_pwm < 400 || ppm_pwm > 10000)
      {
        Serial.println("Error: Measurement out of range!");
        return -1;
      }

      Serial.print(", PPMpwm: ");
      Serial.print(ppm_pwm);

      Serial.println("\n------------------------------");

      return ppm_pwm;
    }
    return 0;
  }
}
