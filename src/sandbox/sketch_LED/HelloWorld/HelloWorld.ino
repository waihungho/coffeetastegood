#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x20 for a 16 chars and 2 line display


void setup()
{
	// initialize the LCD
	lcd.begin(20,4);

	// Turn on the blacklight and print a message.
	lcd.backlight();
  lcd.home();

  lcd.print("PM2.5: 13 ug/m3");
  lcd.setCursor(0, 1);
  //lcd.print("PM1.0:9 ug/m3");
//PM10:  13  ug/m3
  lcd.print("PM1: 9  PM10: 13");

//  lcd.print("i ");
//  lcd.write(3);
//  lcd.print(" you!");



  
}

void loop()
{
	// Do nothing here...
}
