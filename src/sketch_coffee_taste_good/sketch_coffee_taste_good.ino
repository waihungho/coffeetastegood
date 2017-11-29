// Arduino PIN settings 
const int pinGrinder = 13;  // 這裡設定所要閃爍的LED燈腳位.
const int pinBtTX = 5;  // Bluetooth TX (RED)
const int pinBtRX = 4;  // Bluetooth RX (BROWN)
const int pinRelay = 2;  // Relay

#include "myStepper.h"
#define STEPS 2048 // 这里设置步进电机旋转一圈是多少步
Stepper stepper(STEPS,8,9,10,11);  //设置步进电机的每转步数、每分钟转速和管脚  ( PIN 8: IN1 , etc)

// Bluetooth (BEGIN)
#include  <SoftwareSerial.h>
SoftwareSerial BTSerial(pinBtTX, pinBtRX); // TX | RX
//#include <Wire.h>
//#define MAX_BTCMDLEN 128  // the maximum received command length from an Android system (over the bluetooth)
//byte cmdBT[MAX_BTCMDLEN];   // received 128 bytes from an Android system
//int lenCmdBT = 0; // received command length
// Bluetooth (END)

// Weight Scales(BEGIN)
#include <HX711.h>
//HX711 scale(6, 7, 128, 0.00246500); // 6 (WHITE) | 7 (BLACK)
HX711 scale(A1, A0); // A1 : DT (BLACK) | A0 : SCK (WHITE)
// Weight Scales(END)

// Coffee Status (BEGIN)
int coffeeStatus;
const int COFFEE_STATUS_INIT = 0;
const int COFFEE_STATUS_START = 1;
const int COFFEE_STATUS_GRIND = 2;
const int COFFEE_STATUS_PREPARE_WATER = 3;
const int COFFEE_STATUS_BLOOM = 4;
const int COFFEE_STATUS_END = 5;
const int COFFEE_WEIGHTS = 100;
// Coffee Status (END)

void setup() {  // put your setup code here, to run once:
  coffeeStatus = COFFEE_STATUS_INIT; 
  pinMode(pinGrinder, OUTPUT);  // LED 
  pinMode(pinRelay, OUTPUT); // Relay
  Serial.begin(9600);          // Serial Monitor : Arduino起始鮑率：9600
  BTSerial.begin(115200);     // Bluetooth Baud Rate : 每個藍牙晶片的鮑率都不太一樣，請務必確認
  //scale.set_scale(415.f);    // Weight Scales : this value is obtained by calibrating the scale with known weights; see the README for details
  //scale.tare();               // Weight Scales : Tare
  scale.set_offset(41562);
  scale.tare();  

  stepper.SetSpeed(5);
  
  Serial.println("READY!");
}

void loop() {  // put your main code here, to run repeatedly:

  if ( coffeeStatus == COFFEE_STATUS_INIT ) {
    if (BTSerial.available()) { // Keep reading from HC-05 and send to Arduino Serial Monitor     
      char cmdBT = BTSerial.read();
      //  Serial.write(BTSerial.read());
      Serial.print("Command from Bluetooth :");Serial.write(cmdBT);Serial.println("");
      if(cmdBT == '1') {
        coffeeStatus = COFFEE_STATUS_START; // Start      
      }
    }  
  } else if ( coffeeStatus == COFFEE_STATUS_START ) {
      digitalWrite(pinGrinder, HIGH); // 設定PIN13腳位為高電位 = 5V, Turn on LED
      coffeeStatus = COFFEE_STATUS_GRIND;
  } else if ( coffeeStatus == COFFEE_STATUS_GRIND ) {
      //double weights = scale.get_units(10);
      double weights = 0;
      for (int i = 0; i < 10; i++) {
//        weights += scale.bias_read();
      }
      weights = weights / 10;
       Serial.print("Weights :");Serial.println(weights);
      if ( weights > COFFEE_WEIGHTS  ) {
         coffeeStatus = COFFEE_STATUS_PREPARE_WATER; 
      }
  
  } else if ( coffeeStatus == COFFEE_STATUS_PREPARE_WATER ) {
      digitalWrite(pinRelay, HIGH);  // Power ON
      delay(5000);
      digitalWrite(pinRelay, LOW);   // Power Off
      delay(10);
      coffeeStatus = COFFEE_STATUS_BLOOM; 
  } else if ( coffeeStatus == COFFEE_STATUS_BLOOM ) {
      stepper.Step(1024);
      delay(10);
      coffeeStatus = COFFEE_STATUS_END; 
  } else if ( coffeeStatus == COFFEE_STATUS_END ) {
     digitalWrite(pinGrinder, LOW); // 設定PIN13腳位為低電位 = 0V, Turn off LED
      coffeeStatus = COFFEE_STATUS_INIT;
  }
}


