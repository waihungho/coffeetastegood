#include <LiquidCrystal.h>
#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

LiquidCrystal lcd(RS,E,D4,D5,D6,D7); //建立 LCD 物件

void setup() { //初始設定 (一次性)
lcd.begin(16,2); //定義 LCD 為 2 列 16 行顯示器
lcd.clear(); //清除螢幕
lcd.setCursor(0,0); //游標移到左上角
lcd.print("Hello World!"); //在第一列印出 Hello World!
}

void loop() { //無限迴圈
lcd.setCursor(0,1); //游標移到第 2 列第 1 行
lcd.print(millis()/1000); //印出秒數
}
