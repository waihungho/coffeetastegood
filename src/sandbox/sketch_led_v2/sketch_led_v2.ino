#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 20 chars and 4 line display
//LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x20 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x27);  // Set the LCD I2C address  (This LCD address: 0x3F)
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address  (This LCD address: 0x3F)


void setup() {
  lcd.begin(20,4);
  lcd.backlight();
  lcd.home ();                   // go home
  lcd.print("Loading");
}

void loop() {
  // put your main code here, to run repeatedly:

}

