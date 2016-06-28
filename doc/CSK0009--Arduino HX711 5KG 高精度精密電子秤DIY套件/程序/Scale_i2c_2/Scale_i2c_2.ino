#include <HX711.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
HX711 hx(9, 10, 128, 0.00127551);
LiquidCrystal_I2C lcd(0x27,16,2); 
void setup() {
  Serial.begin(9600);
  hx.set_offset(41562);
    hx.tare();
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.begin(16,2);

}
void loop() {

  delay(500);
  double sum0 = 0;
  double sum1 = 0;
  for (int i = 0; i < 10; i++) {
    sum0 += hx.read();
    sum1 += hx.bias_read();
  }
  lcd.clear();  
  lcd.setCursor(2,0);
  lcd.print("keyes-scale");
  lcd.setCursor(5, 1);
  lcd.print(sum1/10);
  lcd.print("g");
    Serial.println(sum1/10);
  delay(10);

}
