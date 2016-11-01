// Red (+)
// Black (-)
// Yellow (Signal)

#include <VarSpeedServo.h> 
 
VarSpeedServo myservo;  // create servo object to control a servo 
                        // a maximum of eight servo objects can be created 
 
const int servoPin = 9; // the digital pin used for the servo
 
void setup() { 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  myservo.write(0,255,true); // set the intial position of the servo, as fast as possible, wait until done
} 

void loop() {
  myservo.write(180,255,true);        // move the servo to 180, max speed, wait until done
                                      // write(degrees 0-180, speed 1-255, wait to complete true-false)
  myservo.write(0,25,true);           // move the servo to 180, slow speed, wait until done
} 




//
//#include <Servo.h>
//#include <math.h>
//
////servo object
//Servo myservo;
//
////servo position
//int pos = 0;
////positions (in degrees) to send to the servo
//int positions[] = {0, 45, 90, 135, 180};
//
//int numPositions = 5;
//
//int numMeasurements = 5;
//
////HS-311 servo parameters
//int zero_degrees = 98;  // HS-311 New version: 94; Old version: 98
//double one_degree = 1.5111;//HS-311 New Version: 1.4889; Old version: 1.51111;
//
//void setup()
//{
//  //control servo via pin 9
//  myservo.attach(9, 650, 2350);
//  //start serial comm. for debugging
//  Serial.begin(9600);
//}
//
//void loop()
//{
//  int i = 0;
//  //iterate over positions
//  for(i = 0; i < numPositions; i++)
//  { 
//    pos = positions[i];
//    int j = 0;
//    double sum = 0;
//    double sensorValue = 0;
//   
//    Serial.println("SETTING:");
//    Serial.println(pos);
//    myservo.write(pos);
//   
//    //wait a bit, to give the servo time to reach the requested position
//    delay(800);
//   
//    //read the feedback via A0, once or multiple times
//    for(j = 0; j<numMeasurements; j++){ 
//      sum += analogRead(A0);
//    }
//   
//    //calculate average if numMeasurements > 1
//    sensorValue = (sum/numMeasurements);
//    Serial.println("READ:");
//    Serial.println(calcH311ServoPosition(sensorValue));
//   
//    //wait for three seconds
//    delay(3000);
//  }
//
//}
//
//double calcH311ServoPosition(double val){
//  val -= zero_degrees;
//  val /= one_degree;
//  val = floor(val);
// 
//  return val;
//}
