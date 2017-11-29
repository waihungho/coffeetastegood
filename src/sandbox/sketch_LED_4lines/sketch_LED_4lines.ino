/* YourDuino.com Example Software Sketch
 16 character 2 line I2C Display
 Backpack Interface labelled "A0 A1 A2" at lower right.
 ..and
 Backpack Interface labelled "YwRobot Arduino LCM1602 IIC V1"
 MOST use address 0x27, a FEW use 0x3F
 terry@yourduino.com */

#define LED_DIGITS_PER_LINE 20  // No. of Characters per LINE


/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads 
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// A FEW use address 0x3F
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/*-----( Declare Variables )-----*/
//NONE

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);  // Used to type in characters

  lcd.begin(20,4);   // initialize the lcd for 16 chars 2 lines, turn on backlight

// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on  

//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Hello, world!");
  //delay(1000);
  lcd.setCursor(0,1);
  lcd.print("HI!YourDuino.com");
  //delay(1000);  

  lcd.setCursor(0,2);
  lcd.print("33333333");
  //delay(1000);  
  lcd.setCursor(0,3);
  lcd.print("4444444");
  //delay(1000); 


 displayLED("111111111","222222222","333333333","444444444") ;

 displayLED("","","AA","ccB") ;



}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
 

}/* --(end main loop )-- */


void displayLED(String firstLine, String secondLine, String thirdLine, String fourthLine) {
  int i;
  lcd.clear();
  if (firstLine.length()>0) {
    
    Serial.println("1:" + firstLine);
    String printFirstLine = firstLine;
    for ( i = sizeof(printFirstLine); i <= LED_DIGITS_PER_LINE; i++) // Clearing the previous message on LED.
      printFirstLine += " ";
    lcd.setCursor(0, 0);

    lcd.print(printFirstLine);
  }
  if ( secondLine.length()>0) {
     Serial.println("2:" + secondLine);
    String printSecondLine = secondLine;
    for ( i = sizeof(printSecondLine); i <= LED_DIGITS_PER_LINE; i++)
      printSecondLine += " ";
    //lcd.home();
    lcd.setCursor(0, 1);
    lcd.print(printSecondLine);
  }
  if ( thirdLine.length()>0) {
     Serial.println("3:" + thirdLine);
    String printThirdLine = thirdLine;
    for ( i = sizeof(printThirdLine); i <= LED_DIGITS_PER_LINE; i++){
      printThirdLine += " ";
    }
    Serial.println(String("3sizeof(printThirdLine):") + sizeof(printThirdLine));
    Serial.println(String(":") + printThirdLine);
    //lcd.home();
    lcd.setCursor(0, 2);
    lcd.print(printThirdLine);
  }
  if ( fourthLine.length()>0) {
    Serial.println("4:" + fourthLine);
    String printFourthLine = fourthLine;
    for ( i = sizeof(printFourthLine); i <= LED_DIGITS_PER_LINE; i++)
      printFourthLine += " ";
    //lcd.home();
    lcd.setCursor(0, 3);
    lcd.print(printFourthLine);
  }
}

/* ( THE END ) */
