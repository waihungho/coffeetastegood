#include <Servo.h> 

Servo myservo;
Servo myservo2;

void setup() 
{ 

 // myservo.attach(9, 550, 2450); // 修正脈衝寬度範圍 (Pin 9: Orange; 5V:Red; GND: Brown)
  //myservo.write(90); // 一開始先置中90度
 
  myservo.attach(3);
  myservo2.attach(4);
} 

void loop() {


 myservo.write(10);
delay(3000);
   myservo.write(90);

delay(3000);
   myservo.write(180);  
delay(3000);


 myservo2.write(10);
delay(3000);
   myservo2.write(90);

delay(3000);
   myservo2.write(180);  
delay(3000);

//  for(int i = 500; i <= 2400; i+=100){
//    myservo.writeMicroseconds(i); // 直接以脈衝寬度控制
//
//    delay(300);
//  }
//  for(int i = 2400; i >= 500; i-=100){
//    myservo.writeMicroseconds(i);
//
//    delay(300);
//  }




// int angle;
//  for(angle = 0; angle < 180; angle += 1)    // command to move from 0 degrees to 180 degrees 
//  {                                  
//    myservo.write(angle);                 //command to rotate the servo to the specified angle
//    delay(15);                       
//  } 
// 
//  delay(1000);
//  
//  for(angle = 180; angle>=1; angle-=1)     // command to move from 180 degrees to 0 degrees 
//  {                                
//    myservo.write(angle);              //command to rotate the servo to the specified angle
//    delay(15);                       
//  } 
//
//    delay(1000);
  
}
