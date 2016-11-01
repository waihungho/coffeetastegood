#include <Servo.h> 


Servo myservo;
Servo myservo2;



void setup() 
{ 

  Serial.begin(9600);

  myservo.attach(9, 500, 2400); // 修正脈衝寬度範圍
  myservo2.attach(4, 500, 2400); // 修正脈衝寬度範圍

  myservo.write(90); // 一開始先置中90度
  myservo2.write(90); // 一開始先置中90度

  delay(3000);
    Serial.println("Ready and Go!");
} 

void goVertical(){  // 直線移動
    // Serial.println("loop");
  int delayInterval=100;
  int left=0;
  int right=0;
  Serial.println("First");
  int startInt = 10;//0;
  int endInt = 15;//19;
  for(int i = startInt; i < endInt; i++){ // 16
      Serial.println(i);
    left=i*100+500;
    right=(19-i)*100+500;
    Serial.println("Vertical#1 Left[leftServo]" + String(left) + "[rightServo]" + String(right));
    myservo.writeMicroseconds(left); // 直接以脈衝寬度控制
    myservo2.writeMicroseconds(right); // 直接以脈衝寬度控制
        delay(delayInterval);
  }
  Serial.println("Second");
  for(int i = endInt;  i >startInt; i--){ // 10
    Serial.println(i);
    left=i*100+500;
    right=(19-i)*100+500;
    Serial.println("Vertical#2 Left[leftServo]" + String(left) + "[rightServo]" + String(right));
    myservo.writeMicroseconds(left); // 直接以脈衝寬度控制
    myservo2.writeMicroseconds(right); // 直接以脈衝寬度控制
        delay(delayInterval);
  }
  
}

void goHorizontal(){
  int delayInterval=100;
  int left=0;
  int right=0;
  Serial.println("First");
  int startInt = 4;//0;
  int endInt = 15;//19;
  for(int i = startInt; i < endInt; i++){ // 16
      Serial.println(i);
    left=i*100+500;
    right=(19-i)*100+500;
    Serial.println("Horizontal#1 Left[leftServo]" + String(left) + "[rightServo]" + String(left));
    myservo.writeMicroseconds(left); // 直接以脈衝寬度控制
    myservo2.writeMicroseconds(left); // 直接以脈衝寬度控制
        delay(delayInterval);
  }
  Serial.println("Second");
  for(int i = endInt;  i >startInt; i--){ // 10
    Serial.println(i);
    left=i*100+500;
    right=(19-i)*100+500;
    Serial.println("Horizontal#2 Left[leftServo]" + String(left) + "[rightServo]" + String(left));
    myservo.writeMicroseconds(left); // 直接以脈衝寬度控制
    myservo2.writeMicroseconds(left); // 直接以脈衝寬度控制
        delay(delayInterval);
  }
  
}

// 2100 --> 1500 --> 900
 int leftServoLeft = 2100;
 int leftServoCenter = 1500;
 int leftServoRight = 900;
 int rightServoLeft = 2100;
 int rightServoCenter = 1500;
 int rightServoRight = 900;
 int leftServoCenterToCenter = leftServoCenter+250;
 int rightServoCenterToCenter = rightServoCenter-250;
int delaySec = 3000;
void go2Center(){
  Serial.println("Center[leftServo]" + String(leftServoCenterToCenter) + "[rightServo]" + String(rightServoCenterToCenter));
  myservo.writeMicroseconds(leftServoCenterToCenter); 
  myservo2.writeMicroseconds(rightServoCenterToCenter); 
  delay(delaySec);
}
void go2Top(){
  Serial.println("Top[leftServo]" + String(leftServoCenter) + "[rightServo]" + String(rightServoCenter));
  myservo.writeMicroseconds(leftServoCenter);
  myservo2.writeMicroseconds(rightServoCenter);
  delay(delaySec);
}
void go2Bottom(){
  int leftServoMoveto = leftServoLeft-50;
  int rightServoMoveto = rightServoRight-50;
  Serial.println("Bottom[leftServo]" + String(leftServoMoveto) + "[rightServo]" + String(rightServoMoveto));
  myservo.writeMicroseconds(leftServoLeft-50); 
  myservo2.writeMicroseconds(rightServoRight+50);
  delay(delaySec);
}
void go2Left(){
  int leftServoMoveto = leftServoLeft-100;
  int rightServoMoveto = rightServoLeft-600;
  Serial.println("Left[leftServo]" + String(leftServoMoveto) + "[rightServo]" + String(rightServoMoveto));
  myservo.writeMicroseconds(leftServoMoveto); 
  myservo2.writeMicroseconds(rightServoMoveto); 
  delay(delaySec);
}

void go2Right(){
  int leftServoMoveto = leftServoRight+500;
  int rightServoMoveto = rightServoRight+150;
  Serial.println("Right[leftServo]" +  String(leftServoMoveto) + "[rightServo]" +  String(rightServoMoveto));
  myservo.writeMicroseconds(leftServoMoveto); 
  myservo2.writeMicroseconds(rightServoMoveto); 
  delay(delaySec);
}

void loop() 
{
 int mode=3;
 if (mode==1) {
   goVertical();
   delay(2000);
   goHorizontal();
   delay(2000);
 }else if( mode == 2) {
  go2Center();
  go2Bottom();  
  go2Left();
  go2Top();
  go2Right();
  go2Bottom();
 } else {
    int delayInterval = 50;
    
    #define MOVE_TO_ARRAY_SIZE 13
    int leftServoTo[MOVE_TO_ARRAY_SIZE] =  {2000, 2000, 2000, 2000, 2000, 2000, 2100, 2100, 2100, 2100, 2100, 2100, 2100 };  //Bottom to Left
    int rightServoTo[MOVE_TO_ARRAY_SIZE] = {900 , 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100 };
    for(int i = 0; i < MOVE_TO_ARRAY_SIZE ; i++){ 
      Serial.println("Bottom to Left[i]" + String(i) + "[leftServo]" +  String(leftServoTo[i]) + "[rightServo]" +  String(rightServoTo[i]));
      myservo.writeMicroseconds(leftServoTo[i]);
      myservo2.writeMicroseconds(rightServoTo[i]);
      delay(delayInterval);
    }
    
    #define MOVE_TO_ARRAY_SIZE_2 7
    int leftServoTo2[MOVE_TO_ARRAY_SIZE_2] =  {2000, 2000, 1900, 1800, 1700, 1600, 1500 };  //Left to Top
    int rightServoTo2[MOVE_TO_ARRAY_SIZE_2] = {2000, 2000, 1900, 1800, 1700, 1600, 1500 };
    for(int i = 0; i < MOVE_TO_ARRAY_SIZE_2 ; i++){ 
      Serial.println("Left to Top[i]" + String(i) + "[leftServo]" +  String(leftServoTo2[i]) + "[rightServo]" +  String(rightServoTo2[i]));
      myservo.writeMicroseconds(leftServoTo2[i]);
      myservo2.writeMicroseconds(rightServoTo2[i]);
      delay(delayInterval);
    }

    #define MOVE_TO_ARRAY_SIZE_3 6
    int leftServoTo3[MOVE_TO_ARRAY_SIZE_3] =  {1400, 1300, 1200, 1100, 1000, 900};  //Top to Right
    int rightServoTo3[MOVE_TO_ARRAY_SIZE_3] = {1400, 1300, 1200, 1100, 1000, 900};
    for(int i = 0; i < MOVE_TO_ARRAY_SIZE_3 ; i++){ 
      Serial.println("Top to Right[i]" + String(i) + "[leftServo]" +  String(leftServoTo3[i]) + "[rightServo]" +  String(rightServoTo3[i]));
      myservo.writeMicroseconds(leftServoTo3[i]);
      myservo2.writeMicroseconds(rightServoTo3[i]);
      delay(delayInterval);
    }
    
    #define MOVE_TO_ARRAY_SIZE_4 11
    int leftServoTo4[MOVE_TO_ARRAY_SIZE_4] =  {1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};  //Right to Bottom
    int rightServoTo4[MOVE_TO_ARRAY_SIZE_4] = {900 , 900 , 900 , 900 , 900 , 900 , 900 , 900 , 900 , 900 , 900 };
    for(int i = 0; i < MOVE_TO_ARRAY_SIZE_4 ; i++){ 
      Serial.println("Top to Right[i]" + String(i) + "[leftServo]" +  String(leftServoTo4[i]) + "[rightServo]" +  String(rightServoTo4[i]));
      myservo.writeMicroseconds(leftServoTo4[i]);
      myservo2.writeMicroseconds(rightServoTo4[i]);
      delay(delayInterval);
    }
    

//    for(int i = 1; i < 6; i++){ 
//      int a = 1; 
//      myservo.writeMicroseconds(a);
//    }


//    for(int i = 0;  i <6; i++){ // 10
//      myservo.writeMicroseconds(leftServoTo[i]); 
//      myservo2.writeMicroseconds(rightServoTo[i]); 
//      delay(delayInterval);
//    } 
    
 }
}
