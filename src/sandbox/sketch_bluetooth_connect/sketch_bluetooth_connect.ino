

int ledPin = 13; // 這裡設定所要閃爍的LED燈腳位
//const int  buttonPin = 2;
//
//int buttonPushCounter = 0;   // counter for the number of button presses
//int buttonState = 0;         // current state of the button
//int lastButtonState = 0;     // previous state of the button
//
#include  <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX | TX
//
//
#include <Wire.h>
//
//// the maximum received command length from an Android system (over the bluetooth)
//#define MAX_BTCMDLEN 128
//
//byte cmd[MAX_BTCMDLEN]; // received 128 bytes from an Android system
//int len = 0; // received command length
//
//// https://github.com/bogde/HX711.git
//#include <HX711.h>
//HX711 scale(A1, A0);
////HX711 scale(A0, A1);

void setup() {
  // put your setup code here, to run once:
//
pinMode(ledPin, OUTPUT);
//  pinMode(buttonPin, INPUT);
//  Serial.begin(9600);

   pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH);
//  Serial.begin(9600);
//  Serial.println("Enter AT commands:");
//  BTSerial.begin(38400);  // HC-05 default speed in AT command more

  Serial.begin(9600);   // Arduino起始鮑率：9600

    //BTSerial.begin(38400); // HC-06 出廠的鮑率：每個藍牙晶片的鮑率都不太一樣，請務必確認
BTSerial.begin(115200);




//
//Serial.println("Before setting up the scale:");
//  Serial.print("read: \t\t");
//  Serial.println(scale.read());      // print a raw reading from the ADC
//
//  Serial.print("read average: \t\t");
//  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC
//
//  Serial.print("get value: \t\t");
//  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)
//
//  Serial.print("get units: \t\t");
//  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided 
//            // by the SCALE parameter (not set yet)  
//
//  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
//  scale.tare();               // reset the scale to 0
//
//  Serial.println("After setting up the scale:");
//
//  Serial.print("read: \t\t");
//  Serial.println(scale.read());                 // print a raw reading from the ADC
//
//  Serial.print("read average: \t\t");
//  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
//
//  Serial.print("get value: \t\t");
//  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()
//
//  Serial.print("get units: \t\t");
//  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
//            // by the SCALE parameter set with set_scale
//
//  Serial.println("Readings:");


}

void loop() {

//  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());
//  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());

  
//   put your main code here, to run repeatedly:
//  digitalWrite(ledPin, HIGH); // 設定PIN13腳位為高電位 = 5V
//  delay(1000); // 設定延遲時間，1000 = 1秒
//  digitalWrite(ledPin, LOW); // 設定PIN13腳位為低電位 = 0V
//  delay(1000); // 設定延遲時間
//  buttonState = digitalRead(buttonPin);
 
// Serial.println(buttonState );
//  delay(50); 
//  if (buttonState != lastButtonState) {
//    // if the state has changed, increment the counter
//    if (buttonState == HIGH) {
//      // if the current state is HIGH then the button
//      // wend from off to on:
//      buttonPushCounter++;
//      Serial.println("on");
//      Serial.print("number of button pushes:  ");
//      Serial.println(buttonPushCounter);
//    } else {
//      // if the current state is LOW then the button
//      // wend from on to off:
//      Serial.println("off");
////      digitalWrite(ledPin, HIGH); // 設定PIN13腳位為高電位 = 5V
////      delay(1000); // 設定延遲時間，1000 = 1秒
////      digitalWrite(ledPin, LOW); // 設定PIN13腳位為低電位 = 0V
//    }
//    // Delay a little bit to avoid bouncing
//    delay(50);
//  }
//  // save the current state as the last state,
//  //for next time through the loop
//  lastButtonState = buttonState;





//    char str[MAX_BTCMDLEN];
//    int insize, ii;  
//    int tick=0;
//
//    while ( tick<MAX_BTCMDLEN ) { // 因為包率同為9600, Android送過來的字元可能被切成數份
//        if ( (insize=(BTSerial.available()))>0 ){ // 讀取藍牙訊息
//            for ( ii=0; ii<insize; ii++ ){
//                cmd[(len++)%MAX_BTCMDLEN]=char(BTSerial.read());
//            }
//        } else {
//            tick++;
//        }
//    }
//
//    if ( len ) { // 用串列埠顯示從Android手機傳過來的訊息
//        sprintf(str,"%s",cmd);
//        Serial.println(str);
//        Serial.println(char(BTSerial.read()));
//        cmd[0] = '\0';
//    }
//    len = 0;



//  byte cmmd[20]; 
//  int insize; 
//  while(1){ 
//  if ((insize=(BTSerial.available()))>0)
//  {  //判斷有沒有訊息接收 
//    Serial.print("input size = "); 
//    Serial.println(insize);  //顯示接收多少訊息 
//    for (int i=0; i<insize; i++) {
//      Serial.print(cmmd[i]=char(BTSerial.read()));//將接收的訊息顯示出來
//       Serial.print(cmmd[i]);
//      Serial.println(" ");  
//    }//if
//  } //for 
//  }//while


//
//    char str[MAX_BTCMDLEN];
//    int insize, ii;  
//    int tick=0;
//    while ( tick<MAX_BTCMDLEN ) { // 因為包率同為9600, Android送過來的字元可能被切成數份
//        if ( (insize=(BTSerial.available()))>0 ){ // 讀取藍牙訊息
//            for ( ii=0; ii<insize; ii++ ){
//                cmd[(len++)%MAX_BTCMDLEN]=char(BTSerial.read());
//            }
//        } else {
//            tick++;
//        }
//    }
//    if ( len ) { // 用串列埠顯示從Android手機傳過來的訊息
//        sprintf(str,"%s",cmd);
//        Serial.println(str);
//        cmd[0] = '\0';
//    }
//    len = 0;



//  Serial.print(scale.get_value(), 1);
//  Serial.println(" g");
//  delay(200);
//  
//  Serial.print("one reading:\t");
//  Serial.print(scale.get_units(), 1);
//  Serial.print("\t| average:\t");
//  Serial.println(scale.get_units(10), 1);
//
//  scale.power_down();              // put the ADC in sleep mode
//  delay(5000);
//  scale.power_up();
    
}
