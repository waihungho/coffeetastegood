#include "myStepper.h"
#define STEPS 2048 // 这里设置步进电机旋转一圈是多少步
Stepper stepper(STEPS,8,9,10,11);  //设置步进电机的每转步数、每分钟转速和管脚  ( PIN 9: IN1 , etc)
void setup() {
  stepper.SetSpeed(40);
} 
void loop() {
  stepper.Step(2048);
//  delay(5000);
//  stepper.Step(-2048);
//  delay(5000);
  //for(int i=0;i<2048;i++) stepper.Step(1);
}


//int Pin0 = 8;
//int Pin1 = 9;
//int Pin2 = 10;
//int Pin3 = 11;
//
//int _step = 0;
//
//boolean dir = true;
//
////#include <Stepper.h>
////#define STEPS 200  //定義步進馬達每圈的步數
//////steps:代表馬達轉完一圈需要多少步數。如果馬達上有標示每步的度數，
//////將360除以這個角度，就可以得到所需要的步數(例如：360/3.6=100)。(int)
////Stepper stepper(STEPS, 8, 9, 10, 11);
//
//void setup() {
//  // put your setup code here, to run once:
//  pinMode(Pin0, OUTPUT);
//  pinMode(Pin1, OUTPUT);
//  pinMode(Pin2, OUTPUT);
//  pinMode(Pin3, OUTPUT);
//  Serial.begin(9600);
//  Serial.println("READY");
////  stepper.setSpeed(140);     // 將馬達的速度設定成140RPM 最大  150~160
//  
//}
//
//void loop() {
//
////stepper.setSpeed(140);     // 將馬達的速度設定成140RPM 最大  150~160
////stepper.step(100);//正半圈
////delay(1000);
////stepper.step(-100);//反半圈
////delay(1000);
////stepper.step(200);//正1圈
////delay(1000);
////stepper.step(-200);//反1圈
////delay(1000);
////stepper.step(300);//正1圈半
////delay(1000);
////stepper.step(-300);//反1圈半
////delay(1000);
////stepper.step(1600);//正8圈
////delay(1000);
////stepper.step(-1600);//反8圈
////delay(1000);
//
//  Serial.println(_step);
//
//  switch(_step){
//  case 0:
//    digitalWrite(Pin0, LOW);
//    digitalWrite(Pin1, LOW);
//    digitalWrite(Pin2, LOW);
//    digitalWrite(Pin3, HIGH);
//    break;
//  case 1:
//    digitalWrite(Pin0, LOW);
//    digitalWrite(Pin1, LOW);
//    digitalWrite(Pin2, HIGH);
//    digitalWrite(Pin3, HIGH);
//    break;
//  
//  case 2:
//    digitalWrite(Pin0, LOW);
//    digitalWrite(Pin1, LOW);
//    digitalWrite(Pin2, HIGH);
//    digitalWrite(Pin3, LOW);
//    break;
//  
//  case 3:
//    digitalWrite(Pin0, LOW);
//    digitalWrite(Pin1, HIGH);
//    digitalWrite(Pin2, HIGH);
//    digitalWrite(Pin3, LOW);
//    break;
//  
//  case 4:
//    digitalWrite(Pin0, LOW);
//    digitalWrite(Pin1, HIGH);
//    digitalWrite(Pin2, LOW);
//    digitalWrite(Pin3, LOW);
//    break;
//  
//  case 5:
//    digitalWrite(Pin0, HIGH);
//    digitalWrite(Pin1, HIGH);
//    digitalWrite(Pin2, LOW);
//    digitalWrite(Pin3, LOW);
//    break;
//  
//  case 6:
//    digitalWrite(Pin0, HIGH);
//    digitalWrite(Pin1, LOW);
//    digitalWrite(Pin2, LOW);
//    digitalWrite(Pin3, LOW);
//    break;
//  
//  case 7:
//    digitalWrite(Pin0, HIGH);
//    digitalWrite(Pin1, LOW);
//    digitalWrite(Pin2, LOW);
//    digitalWrite(Pin3, HIGH);
//    break;
//  
//  default:
//    digitalWrite(Pin0, LOW);
//    digitalWrite(Pin1, LOW);
//    digitalWrite(Pin2, LOW);
//    digitalWrite(Pin3, LOW);
//    break;
//  
//  }
//
//  if(dir){
//    _step++;
//  }else{
//    _step--;
//  }
//  if(_step>7){
//   _step=0;
//  }
//  if(_step<0){
//    _step=7;
//  }
//  delay(1);
//}
