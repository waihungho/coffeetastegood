// http://maker.tn.edu.tw/modules/tad_book3/page.php?tbdsn=71

#include "MQ135.h"
//#define ANALOGPIN A1    //  Define Analog PIN on Arduino Board
// Modify RZERO value in C:\Users\vfire\Documents\Arduino\libraries\MQ135\MQ135.h
//#define RZERO 6619    //  Define RZERO Calibration Value

MQ135 gasSensor = MQ135(A1);

void setup()
{
  Serial.begin(9600);
  //float rzero = gasSensor.getRZero();
//  delay(3000);
  //Serial.print("MQ135 RZERO Calibration Value : ");
  //Serial.println(rzero);
}

void loop() {
  float ppm = gasSensor.getPPM();

digitalWrite(13,HIGH);
  Serial.print("CO2 ppm value : ");
  Serial.println(ppm);
    delay(1000);
}

