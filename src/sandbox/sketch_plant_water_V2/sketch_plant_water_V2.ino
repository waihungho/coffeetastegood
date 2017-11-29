#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 20 chars and 4 line display
//LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x20 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x27);  // Set the LCD I2C address  (This LCD address: 0x3F)
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address  (This LCD address: 0x3F)

// Clock PIN:
#define CLOCK_RST_PIN 8 //RST
#define CLOCK_DAT_PIN 6  //DAT  
#define CLOCK_CLK_PIN 7  //CLK
//  PMS3003     Arduino(UNO)
//  RST         PIN8
//  DAT         PIN6
//  CLK         PIN7  

// Clock Configuration (BEGIN)
//#include <stdio.h>
#include <DS1302.h> // https://github.com/msparks/arduino-ds1302
DS1302 clockDS1302(CLOCK_RST_PIN, CLOCK_DAT_PIN, CLOCK_CLK_PIN);
boolean isClockOK = false;
// Clock Configuration (END)

const int pinRelay = 2;  // Relay

const float PER_SEC =  1000.0;
const float PER_MIN =  PER_SEC * 60.0;
const float PER_HOUR = PER_MIN * 60.0;
const float PER_DAY =  PER_HOUR * 24.0;




const long WATER_FLOW_DURATION = PER_SEC * 60.0 ;

const int SHORT_DELAY  = 200;

int putWaterTimes = 0;
void putWater(){
  if ( putWaterTimes <=5 ) {
    lcd.clear();
    lcd.home();
    lcd.print("Watering.....");
    
    Serial.println("Put Water <BEGIN>");
    digitalWrite(pinRelay, HIGH);   // Power Off
    delay(WATER_FLOW_DURATION);
    digitalWrite(pinRelay, LOW);   // Power Off
    delay(SHORT_DELAY);
    Serial.println("Put Water <END>");

    lcd.clear();
    lcd.home();
    lcd.print("Watering DONE");  
  }else {
    Serial.println("Should not more than 5 times.");
  }
  putWaterTimes++;
}

int do20161121=1;
int do20161122=1;
int do20161123=1;
int do20161124=1;
int do20161125=1;
int do20161126=1;
int do20161127=1;
int do20161128=1;
int do20161129=1;
int do20161130=1;

#define BACKLIGHT_PIN     13

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); 
 
//  initClock(); // initialize Clock
  pinMode(pinRelay, OUTPUT); // Relay
  digitalWrite(pinRelay, LOW);   // Power Off


  // Turn on the blacklight and print a message.
 // lcd.begin(16,2);  


  //lcd.backlight();
  lcd.begin(20,4);
  lcd.backlight();
  lcd.home ();                   // go home
  lcd.print("Loading");


  
}

unsigned int rounds=0;
void loop() {
  //Time t = readClock();


   
 //digitalWrite(pinRelay, HIGH);   // Power Off
//
//  if ( t.mon == 11 && t.date == 21 && do20161121 ==1) {
//    putWater();
//    do20161121--;
//  } else if ( t.mon == 11 && t.date == 22  && do20161122 ==1) {
//    putWater();
//    do20161122--;
//  } else if ( t.mon == 11 && t.date == 23  && do20161123 ==1) {
//    putWater();
//    do20161123--;
//  } else if ( t.mon == 11 && t.date == 24  && do20161124 ==1) {
//    putWater();
//    do20161124--;
//  } else if ( t.mon == 11 && t.date == 25  && do20161125 ==1) {
//    putWater();
//    do20161125--;
//  } else if ( t.mon == 11 && t.date == 26  && do20161126 ==1) {
//    putWater();
//    do20161126--;
//  } else if ( t.mon == 11 && t.date == 27  && do20161127 ==1) {
//    putWater();
//    do20161127--;
// } else if ( t.mon == 11 && t.date == 28  && do20161128 ==1) {
//    putWater();
//    do20161128--;
//  
//  } else if ( t.mon == 11 && t.date == 29  && do20161129 ==1) {
//    putWater();
//    do20161129--;
//  } else if ( t.mon == 11 && t.date == 30  && do20161130 ==1) {
//    putWater();
//    do20161130--;
//  }

  
//  Serial.println(String("") +t.yr + "/" + t.mon + "/" + t.date + " " + t.hr + ":" + t.min);

  putWater();
   unsigned long minutes = 1000L * 60;
  for (int i=1; i <= 24; i++){
     for (int j=1; j <= 60; j++){
      //rounds++;
      lcd.clear();
      lcd.home();
    //  lcd.print(String("") +t.yr + "/" + t.mon + "/" + t.date + " " + t.hr + ":" + t.min);
      lcd.print(String("i:") + i + ",j:"+j);
      lcd.setCursor(0, 1);
      lcd.print(String("Water v1.9:") + putWaterTimes);

      delay(minutes);  
   } 
 }
  
}


void initClock(){
 
  clockDS1302.writeProtect(true); // 是否防止寫入 (日期時間設定成功後即可改成true)
  clockDS1302.halt(false);        // 是否停止計時
 
 
 // calibrate time function.
//
// clockDS1302.writeProtect(false); // 是否防止寫入 (日期時間設定成功後即可改成true)
//  clockDS1302.halt(true);        // 是否停止計時
// Time sett(2016, 11, 21, 16, 11, 00, Time::kMonday); //年 月 日 時 分 秒 星期幾 (日期時間設定成功後即可註解掉)
//  clockDS1302.time(sett);//設定日期時間 (日期時間設定成功後即可註解掉)
  
  //Serial.println("Clock OK");
  
//  Time t = clockDS1302.time();
//  if (t.yr==2000){
//    isClockOK = false; //If it always return 2000:01:01 00:00:00, set the time again.
//  } else {
//    isClockOK = true;
//  }

}

// ENABLE_CLOCK_DS1302 == 1 in order to use this function.
// Return Time object
Time readClock(){
//  if(!ENABLE_CLOCK_DS1302){
//    Serial.println("ERR: ENABLE_CLOCK_DS1302 must set to 1"); // Use readClock(), ENABLE_CLOCK_DS1302 must set to 1
//  }
  Time t = clockDS1302.time();
//  char buf[50];  
//  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
//           t.yr, t.mon, t.date,
//           t.hr, t.min, t.sec);
//  Serial.println(buf);
  return t;
}

