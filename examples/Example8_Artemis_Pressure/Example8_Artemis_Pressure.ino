/*
  Reading barometric pressure from the MS8607
  By: PaulZC

  This example demonstrates how to use the alternate I2C ports on the Artemis family

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

//Define the Artemis TwoWire port for the MS8607
//See the Wire/Example2_MoreI2CPorts example for more details
//TwoWire myWire(1); //Will use Artemis pads 8/9
//TwoWire myWire(2); //Will use Artemis pads 25/27
TwoWire myWire(3); //Will use Artemis pads 42/43, SCL1/SDA1 on the Artemis Thing Plus
//TwoWire myWire(4); //Will use Artemis pads 39/40
//TwoWire myWire(5); //Will use Artemis pads 48/49

//Create an instance of the object
MS8607 barometricSensor;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Qwiic PHT Sensor MS8607 Example");

  myWire.begin();

  if (barometricSensor.begin(myWire) == false)
  {
    Serial.println("MS8607 sensor did not respond. Please check wiring.");
    while(1);
  }
}

void loop(void) {

  float temperature = barometricSensor.getTemperature();
  float pressure = barometricSensor.getPressure();

  Serial.print("Temperature=");
  Serial.print(temperature, 1);
  Serial.print("(C)");

  Serial.print(" Pressure=");
  Serial.print(pressure, 3);
  Serial.print("(hPa or mbar)");

  Serial.println();

  delay(10);
}
