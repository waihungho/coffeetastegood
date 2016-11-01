#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	// initialize the LCD
	lcd.begin();

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
