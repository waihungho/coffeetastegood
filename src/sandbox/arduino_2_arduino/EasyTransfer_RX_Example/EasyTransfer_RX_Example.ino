#include <Wire.h>
#include <EasyTransferI2C.h>

//create object
EasyTransferI2C ET; 

struct RECEIVE_DATA_STRUCTURE{
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
RECEIVE_DATA_STRUCTURE mydata;

//define slave i2c address
#define I2C_SLAVE_ADDRESS 9

void setup(){
  Serial.begin(9600);
  Wire.begin(I2C_SLAVE_ADDRESS);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ET.begin(details(mydata), &Wire);
  //define handler function on receiving data
  Wire.onReceive(receive);

  Serial.println("Ready");
  //pinMode(13, OUTPUT);
  
}

void loop() {
  //check and see if a data packet has come in. 
  if(ET.receiveData()){
     Serial.print("temperatureC:");
     Serial.println(mydata.temperatureC);
     Serial.print("humidityPer:");
     Serial.println(mydata.humidityPer);
     Serial.print("pressure:");
     Serial.println(mydata.pressure);
     Serial.print("pm_1:");
     Serial.println(mydata.pm_1);   
     Serial.print("pm_2_5:");
     Serial.println(mydata.pm_2_5);  
     Serial.print("pm_10:");
     Serial.println(mydata.pm_10);   
     Serial.print("clockYear:");
     Serial.println(mydata.clockYear);  
     Serial.print("clockMonth:");
     Serial.println(mydata.clockMonth);  
     Serial.print("clockDay:");
     Serial.println(mydata.clockDay);  
     Serial.print("clockHour:");
     Serial.println(mydata.clockHour);  
     Serial.print("clockMinute:");
     Serial.println(mydata.clockMinute);  
     Serial.print("clockSeconds:");
     Serial.println(mydata.clockSeconds);  
//    
//    //this is how you access the variables. [name of the group].[variable name]
//    //since we have data, we will blink it out. 
//    for(int i = mydata.blinks; i>0; i--){
//      digitalWrite(13, HIGH);
//      delay(mydata.pause * 100);
//      digitalWrite(13, LOW);
//      delay(mydata.pause * 100);
//    }
  }
}

void receive(int numBytes) {}
