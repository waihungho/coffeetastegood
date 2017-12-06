// master_sender.ino
// Refer to the "slave_receiver" example for use with this
#include <Wire.h>

const int SLAVE_ADDRESS = 1;
char incomingByte = 0;

void setup() {  
  Wire.begin();         // join I2C bus as a Master
  
  Serial.begin(9600);
  Serial.println("Type something to send:");
}

void loop() {
  // send the received data to slave
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write("Victor01234567890,342.0,2342,234,234,234,234,23,4,6364,5,435,43,534,5,34,534,5,6,34,599999999,999");
  Wire.endTransmission();  
  delay(5000);
}

//void serialEvent()
//{
//  // read one byte from serial port
//  incomingByte = Serial.read();
//
//  // send the received data to slave
//  Wire.beginTransmission(SLAVE_ADDRESS);
//  Wire.write(incomingByte);
//  Wire.endTransmission();
//}
