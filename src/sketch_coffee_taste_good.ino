const int pinMotor = 13;  // 這裡設定所要閃爍的LED燈腳位
const int pinBtRX = 10;  // Bluetooth RX
const int pinBtTX = 11;  // Bluetooth TX


// Bluetooth (BEGIN)
#include  <SoftwareSerial.h>
SoftwareSerial BTSerial(pinBtRX, pinBtTX); // RX | TX
//#include <Wire.h>
#define MAX_BTCMDLEN 128  // the maximum received command length from an Android system (over the bluetooth)
byte cmdBT[MAX_BTCMDLEN];   // received 128 bytes from an Android system
int lenCmdBT = 0; // received command length
// Bluetooth (END)

// Weight Scales(BEGIN)
#include <HX711.h>   // https://github.com/bogde/HX711.git
HX711 scale(A1, A0);
// Weight Scales(END)

int coffeeStatus;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);   // Serial Monitor : Arduino起始鮑率：9600

  BTSerial.begin(115200);  // Bluetooth Baud Rate : 每個藍牙晶片的鮑率都不太一樣，請務必確認
  pinMode(pinMotor, OUTPUT);

  coffeeStatus = 0; 

  scale.set_scale(-415.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();     
}

void loop() {
  // put your main code here, to run repeatedly:
 
  if (BTSerial.available()) { // Keep reading from HC-05 and send to Arduino Serial Monitor
     
    char cmdBT = BTSerial.read();
    //  Serial.write(BTSerial.read());
    Serial.print("Command from Bluetooth :");Serial.write(cmdBT);Serial.println("");

    if(cmdBT == '1') {
      coffeeStatus = 1; // Start      
    }
  }

  if ( coffeeStatus == 1 ) {
      digitalWrite(pinMotor, HIGH); // 設定PIN13腳位為高電位 = 5V, Turn on LED
      delay(1000); // 設定延遲時間，1000 = 1秒

      coffeeStatus = 2;

  } else if ( coffeeStatus == 2 ) {
      int weights = scale.get_units(10);
       Serial.print("Weights :");Serial.println(weights);
      if ( weights > 50 ) {
         coffeeStatus = 3; 
      }

  } else if ( coffeeStatus == 3 ) {
     digitalWrite(pinMotor, LOW); // 設定PIN13腳位為低電位 = 0V, Turn off LED
      delay(1000); // 設定延遲時間，1000 = 1秒
      coffeeStatus = 0;
  }

//   delay(2000);
//  Serial.print("get units(5): \t\t");
//  Serial.println(scale.get_units(5), 1);        // print the average of 10 readings from the ADC minus tare weight, divided 


//  if (Serial.available())  // Keep reading from Arduino Serial Monitor and send to HC-05
//    BTSerial.write(Serial.read());

}


