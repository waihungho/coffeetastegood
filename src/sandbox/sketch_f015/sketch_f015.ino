#include "MQ135.h"

int sensorValue;
int digitalValue;

MQ135 gasSensor = MQ135(A0);

// http://microcontrollerslab.com/interfacing-mq-135-gas-sensor-arduino/
//On serial monitor you can see values of analog pin being detected. Currently in my case they are around about 150 which indicate normal air.
//Normal air returns approximately 100-150
//Alcohol returns approximately 700
//Lighter gas returns approximately 750

void setup()

{
  Serial.begin(9600);      // sets the serial port to 9600

  pinMode( A0, INPUT);

}


void loop()

{
  float rzero = gasSensor.getRZero();
  float ppm = gasSensor.getPPM();
   Serial.println(rzero);
 Serial.println(ppm);
 
  delay(5000);
//  sensorValue = analogRead(A0);       // read analog input pin 0
//
//  digitalValue = digitalRead(A0); 
//
//  Serial.print("A1:"); Serial.println(sensorValue, DEC);  // prints the value read
//
//  Serial.print("Dig1:"); Serial.println(digitalValue, DEC);
//
//  delay(2000);                        // wait 100ms for next reading

}


//
//MQ135 gasSensor = MQ135(A1);
//
//int ppm = gasSensor.getPPM();
//
//void setup() {
//  Serial.begin(9600);
// }
// 
//void loop() {
//  float rzero = gasSensor.getRZero();
//  float ppm = gasSensor.getPPM();
//  Serial.println(ppm);
// 
//  delay(5000);
//
//}
