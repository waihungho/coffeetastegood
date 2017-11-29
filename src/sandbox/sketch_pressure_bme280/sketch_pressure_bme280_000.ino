// http://cactus.io/hookups/sensors/barometric/bme280/hookup-arduino-to-bme280-barometric-pressure-sensor

/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor
  Designed specifically to work with the BME280 Breakout board
  ----> http://www.adafruit.com/products/2650
  This sketch only supports the I2C bus for connection.
 ***************************************************************************/

#include <Wire.h>
#include "cactus_io_BME280_I2C.h"

// Create the BME280 object
//BME280_I2C bme;              // I2C using default 0x77 
// or BME280_I2C bme(0x76);  // I2C using address 0x76
BME280_I2C bme(0x76);  // I2C using address 0x76

// PIN
// BME280     ARDUINO
// SDA        SDA (Pin 20)
// SCL        SCL (Pin 21)

void setup() {
  Serial.begin(9600);
  Serial.println("Bosch BME280 Barometric Pressure - Humidity - Temp Sensor | cactus.io"); 

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

 bme.setTempCal(-1);
  
  Serial.println("Pressure\tHumdity\t\tTemp\t\tTemp");
  
}

void loop() {

    bme.readSensor(); 
  
    Serial.print(bme.getPressure_MB()); Serial.print("\t\t");    // Pressure in millibars
    Serial.print(bme.getHumidity()); Serial.print("\t\t");
    Serial.print(bme.getTemperature_C()); Serial.print(" *C\t");
    Serial.print(bme.getTemperature_F()); Serial.println(" *F\t");

    // add a 2 second delay to slow down the output
    delay(2000);
}
