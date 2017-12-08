#include <Wire.h>
#include <EasyTransferI2C.h>

//create object
EasyTransferI2C ET; 

struct SEND_DATA_STRUCTURE{
  float temperatureC = 0;
  float humidityPer = 0;
  unsigned int  pressure = 0;
  unsigned int pm_1 = 0;
  unsigned int pm_2_5 = 0;
  unsigned int pm_10 = 0;
  unsigned int clockYear =0;
  unsigned int clockMonth =0;
  unsigned int clockDay = 0;
  unsigned int clockHour = 0;
  unsigned int clockMinute = 0;
  unsigned int clockSeconds = 0;
};

//give a name to the group of data
SEND_DATA_STRUCTURE mydata;

//define slave i2c address
#define I2C_SLAVE_ADDRESS 9

void setup(){
  Wire.begin();
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Wire);
  
  
  randomSeed(analogRead(0));
  
}

void loop(){
  //this is how you access the variables. [name of the group].[variable name]
  
  mydata.temperatureC = 23.56;
  mydata.humidityPer = 70.32;
  mydata.pressure = 12345;
  mydata.pm_1 = 1212;
  mydata.pm_2_5 = 2323;
  mydata.pm_10 = 2345;
  mydata.clockYear =2018;
  mydata.clockMonth =12;
  mydata.clockDay = 7;
  mydata.clockHour = 23;
  mydata.clockMinute = 15;
  mydata.clockSeconds = 59;
  
  //send the data
  ET.sendData(I2C_SLAVE_ADDRESS);
 
  delay(5000);
}
