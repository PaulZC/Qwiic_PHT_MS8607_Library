/*
  Reading humidity from the MS8607
  By: PaulZC

  Based extensively on:
  Reading barometric pressure from the MS5637
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 13th, 2018
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  The original library and example code was written by TEConnectivity,
  the company that made the sensor. Way to go TE! May other companies
  learn from you.

  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/14688

  This example prints the current pressure in hPa and temperature in C.

  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the sensor onto the shield
  Serial.print it out at 9600 baud to serial monitor.
*/

#include <Wire.h>

#include "MS8607_Library.h"

MS8607 barometricSensor;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Qwiic PHT Sensor MS8607 Example");

  Wire.begin();

  if (barometricSensor.begin() == false)
  {
    Serial.println("MS8607 sensor did not respond. Please check wiring.");
    while(1);
  }

  // Example: set the humidity resolution to 10 bits
  int err = barometricSensor.set_humidity_resolution(MS8607_humidity_resolution_10b);
  if (err != MS8607_status_ok)
  {
    Serial.println("Problem setting the MS8607 sensor humidity resolution.");
    Serial.print("Error code = ");
    Serial.println(err);
    Serial.println("Freezing.");
    while(1);
  }
  
  // Turn the humidity sensor heater OFF
  // The TE examples say that get_compensated_humidity and get_dew_point will only work if the heater is OFF
  err = barometricSensor.disable_heater();
  if (err != MS8607_status_ok)
  {
    Serial.println("Problem disabling the MS8607 humidity sensor heater.");
    Serial.print("Error code = ");
    Serial.println(err);
    Serial.println("Freezing.");
    while(1);
  }
}

void loop(void) {

  float humidity = barometricSensor.getHumidity();
  float temperature = barometricSensor.getTemperature();

  Serial.print("Humidity=");
  Serial.print(humidity, 1);
  Serial.print("(%RH)");

  Serial.print("  Temperature=");
  Serial.print(temperature, 1);
  Serial.println("(C)");

  float compensated_RH;
  int err = barometricSensor.get_compensated_humidity(temperature, humidity, &compensated_RH);
  if (err != MS8607_status_ok)
  {
    Serial.println("Problem getting the MS8607 compensated humidity.");
    Serial.print("Error code = ");
    Serial.println(err);
    return;
  }
  
  Serial.print("Compensated humidity=");
  Serial.print(compensated_RH, 1);
  Serial.print("(%RH)");
  
  float dew_point;
  err = barometricSensor.get_dew_point(temperature, humidity, &dew_point);
  if (err != MS8607_status_ok)
  {
    Serial.println("Problem getting the MS8607 dew point.");
    Serial.print("Error code = ");
    Serial.println(err);
    return;
  }
  
  Serial.print("Dew point=");
  Serial.print(dew_point, 1);
  Serial.println("(C)");

  delay(10);
}
