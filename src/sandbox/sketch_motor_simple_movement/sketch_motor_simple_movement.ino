#include <Servo.h>

// MG966R Servo PIN
// Red: 5V (Middle)
// Brown: GND
// Orange : Data pin


Servo servoLeft; // Define our Servo
Servo servoRight; // Define our Servo

void setup()
{
  Serial.begin(9600);
//   servoLeft.attach(9);
//     servoRight.attach(4); 

 // Hardware 
 //    /     \
 //   |       |
 //   --      --
 //   LEFT   RIGHT
 
  servoLeft.attach(9, 500, 2400); // 修正脈衝寬度範圍  LEFT servo
  servoRight.attach(4, 500, 2400); // 修正脈衝寬度範圍 RIGHT servo

//
//     Serial.println("write 0");
//   servoLeft.write(0);   // Turn Servo Left to 0 degrees
//   servoRight.write(0);   // Turn Servo Left to 0 degrees
//   delay(5000);



}

void loop()
{
int delays=5000;
Serial.println("write 90");
   servoLeft.write(90);   // Turn Servo Left to 0 degrees
   servoRight.write(90);   // Turn Servo Left to 0 degrees
   delay(delays);
//
//     Serial.println("write 180");
//   servoLeft.write(180);   // Turn Servo Left to 0 degrees
//   servoRight.write(180);   // Turn Servo Left to 0 degrees
//   delay(5000);

Serial.println("Got to Left: Left: 2100 Right: 2100");
      servoLeft.writeMicroseconds(2100);
      servoRight.writeMicroseconds(2100);
   
delay(delays);
Serial.println("Got to Top Left: 1500 Right: 1500");
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);

delay(delays);
Serial.println("Got to Right Left: 900 Right: 900");
      servoLeft.writeMicroseconds(900);
      servoRight.writeMicroseconds(900);

delay(delays);
Serial.println("Got to Bottom Left: 2000 Right: 900");
      servoLeft.writeMicroseconds(1900);
      servoRight.writeMicroseconds(900);
delay(delays);







  
//int interval = 5000;
//Serial.println("write(45)");
//servoLeft.write(45);  // Turn Servo Left to 45 degrees
//servoRight.write(45);  // Turn Servo Left to 45 degrees
//delay(interval);  
//Serial.println("write(0)");
//servoLeft.write(0);   // Turn Servo Left to 0 degrees
//servoRight.write(0);   // Turn Servo Left to 0 degrees
//delay(interval);          // Wait 1 second
//Serial.println("write(90)");
//servoLeft.write(90);  // Turn Servo back to center position (90 degrees)
//servoRight.write(90);  // Turn Servo back to center position (90 degrees)
//delay(interval);          // Wait 1 second
//Serial.println("write(135)");
//servoLeft.write(135); // Turn Servo Right to 135 degrees
//servoRight.write(135); // Turn Servo Right to 135 degrees
//delay(interval);          // Wait 1 second
//Serial.println("write(180)");
//servoLeft.write(180); // Turn Servo Right to 180 degrees
//servoRight.write(180); // Turn Servo Right to 180 degrees
//delay(interval);          // Wait 1 second
//Serial.println("write(90)");
//servoLeft.write(90);  // Turn Servo back to center position (90 degrees)
//servoRight.write(90);  // Turn Servo back to center position (90 degrees)
//delay(interval);          // Wait 1 second   
}
