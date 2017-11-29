/*
 Stepper Motor Control

 by Grahame MacKugler, 7/18/2016

 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // the number of steps per revolution for stepper motor.
const int numberRevolution = 5; // the number of revolutions required to move the stage the desired
// linear distance. There are roughly 5 revolutions per inch of linear travel.
const int rpm=5; // revolutions per minute of the stepper motor. Modify to achieve desired linear speed of stage.
const int steps=stepsPerRevolution*numberRevolution*-1; // total number of steps in one direction.

//const int ButtonOnePin = 2;
//const int ButtonTwoPin = 3;
//const int ledPin = 13;

// variables will change:
//int ButtonOneStatus = 0;         // variable for reading the pushbutton status
//int ButtonTwoStatus = 0;         // variable for reading the pushbutton status

// initialize the stepper library on pins 8 and 9
Stepper myStepper(stepsPerRevolution,8, 9);
Stepper myStepper2(stepsPerRevolution,10, 11);
void setup() {
  // set the speed. 
 // myStepper.setSpeed(rpm);
  // initialize the serial port:
  Serial.begin(9600);
//  pinMode(ButtonOnePin, INPUT);
//  pinMode(ButtonTwoPin, INPUT);
//  pinMode(ledPin, OUTPUT);
//  digitalWrite(ButtonOnePin, HIGH);
//  digitalWrite(ButtonTwoPin, HIGH);
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 
}

int count=0;
int dir=-1;
void loop() {
//  count++;
//  
//  if ( count> 1000) {
//    count=0;
//    dir=dir*-1;
//  }
 myStepper.step(steps*dir);
 //myStepper2.step(steps*dir);
 
  delay(5);
  
//  ButtonOneStatus = digitalRead(ButtonOnePin);
//  if (ButtonOneStatus == LOW){ // If the Button #1 is pressed, perform the following:
//  // step in one direction.
//  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
//  Serial.println("clockwise");
//  myStepper.step(steps);
//  delay(500);
//  }
//  ButtonTwoStatus = digitalRead(ButtonTwoPin);
//  if (ButtonTwoStatus == LOW){ // If the Button #2 is pressed, perform the following:
//  // step in the other direction:
//  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
//  Serial.println("counterclockwise");
//  myStepper.step(-1*steps);
//  delay(500);
//  }
//  else {
//    // turn LED off:
//    digitalWrite(ledPin, LOW);
//  }
}
