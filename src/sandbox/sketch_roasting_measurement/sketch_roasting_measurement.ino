// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Arduino Software Version v1.6.12
// Arduino Board UNO  
//
// Sensors:
//  1. LCD (I2C 4x20)
//  2. PMS7003 (PM2.5 / PM1.0 / PM10.0)
//  3. BME280 (Temp, Humidity, Barometer) 
//  4. Clock (If the clock doesnt run, try to use "setClockTime()")
//  Will cause low memory for Arduino UNO //  5. SD Card
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------
//  PIN Configuration (BEGIN)
// ------------------------------------------
// LCD Display PIN:
//  LCD     Arduino(UNO)
//  VCC     5V
//  GND     GND
//  SDA     (Pin A4)     (Reference:Arduino Mega2560:Pin 21)
//  SCL     (Pin A5)     (Reference:Arduino Mega2560:Pin 20)

// PMS7003 (PM2.5 / PM1.0 / PM10.0) PIN:
#define PMS7003_TXD_PIN 8
#define PMS7003_RXD_PIN 9
//  PMS7003     Arduino(UNO)
//  TXD         Pin 8
//  RXD         Pin 9  

// BME280 PIN:
//  BME280     Arduino(UNO)
//  SDA         SDA (IIC)
//  SCL         SCL (IIC)

// Clock Pin
#define CLOCK_RST_PIN 4
#define CLOCK_DAT_PIN 5
#define CLOCK_CLK_PIN 6

// SD Card Pin
//#define SD_MOSI_PIN 11
//#define SD_MISO_PIN 12
//#define SD_SCK_PIN 13
//#define SD_CS_PIN 10
// ------------------------------------------
//  PIN Configuration (END)
// ------------------------------------------


// ------------------------------------------
//  Software Configuration (BEGIN)
// ------------------------------------------
#define SERIAL_BAUD_RATE 9600
//#define WELCOME_MSG_FIRST_LINE "Roast Meter."
//#define WELCOME_MSG_SECOND_LINE "v1.0 Loading......"
// ------------------------------------------
//  Software Configuration (END)
// ------------------------------------------

// LCD Display Configuration (BEGIN)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LCD_DIGITS_PER_LINE 20  // No. of Characters per LINE
#define LCD_LINES 4  // LCD Lines
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address  (This LCD address: 0x3F)
//LiquidCrystal_I2C lcd(0x27, DIGITS_PER_LINE, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display
// PIN
// LCD     ARDUINO
// SDA      (Pin A4)
// SCL      (Pin A5)
// LCD Display Configuration (END)

// BME280 Configuration (BEGIN)
#include "cactus_io_BME280_I2C.h"
BME280_I2C bme280(0x76);  // I2C using address 0x76
float temperatureC=0;
float temperatureF=0;
float humidityPer=0;
float pressure=0;
// Pin: SDA, SCL
// BME280 Configuration (END)

// PMS7003 Configuration (BEGIN)
//https://github.com/MartyMacGyver/PMS7003-on-Particle/blob/master/pms7003-photon-demo-1/pms7003-photon-demo-1.ino
//https://www.taiwaniot.com.tw/shop/module-sensor/%E7%A9%BA%E6%B0%A3%E7%B2%89%E5%A1%B5-pm2-5/%E6%94%80%E8%97%A4-g7-pms7003-pm1-0-pm2-5-pm10-%E7%B2%89%E5%A1%B5%E6%BF%83%E5%BA%A6%E6%84%9F%E6%B8%AC%E5%99%A8/
#include <SoftwareSerial.h>
#define START_1 0x42
#define START_2 0x4d
//-----------------------
#define DATA_LENGTH_H        0
#define DATA_LENGTH_L        1
#define PM1_0_CF1_H          2
#define PM1_0_CF1_L          3
#define PM2_5_CF1_H          4
#define PM2_5_CF1_L          5
#define PM10_CF1_H           6
#define PM10_CF1_L           7
#define PM1_0_ATMOSPHERE_H   8
#define PM1_0_ATMOSPHERE_L   9
#define PM2_5_ATMOSPHERE_H   10
#define PM2_5_ATMOSPHERE_L   11
#define PM10_ATMOSPHERE_H    12
#define PM10_ATMOSPHERE_L    13
#define UM0_3_H              14
#define UM0_3_L              15
#define UM0_5_H              16
#define UM0_5_L              17
#define UM1_0_H              18
#define UM1_0_L              19
#define UM2_5_H              20
#define UM2_5_L              21
#define UM5_0_H              22
#define UM5_0_L              23
#define UM10_H               24
#define UM10_L               25
#define VERSION              26
#define ERROR_CODE           27
#define CHECKSUM             29
unsigned char pms7003ChrRecv;
byte bytCount = 0;
SoftwareSerial myPMS7003(PMS7003_TXD_PIN, PMS7003_RXD_PIN); 

unsigned int pm_1 = 0;
unsigned int pm_2_5 = 0;
unsigned int pm_10 = 0;
// PMS7003 Configuration (END)

// CLOCK Configuration (BEGIN)
#include <stdio.h>
#include <DS1302.h> // https://github.com/msparks/arduino-ds1302
DS1302 rtc(CLOCK_RST_PIN, CLOCK_DAT_PIN, CLOCK_CLK_PIN);
//char longTime[20];
char shortTime[12];
// CLOCK Configuration (END)

// SD Card Configuration (BEGIN)
//#include <SPI.h>
//#include <SD.h>
//File myFile;
// SD Card Configuration (END)

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                    FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  initClock();
  initBme280();
  initPMS7003();
//  initSDCard();
  initLCD(); // initialize LCD
//  displayLCD(WELCOME_MSG_FIRST_LINE, WELCOME_MSG_SECOND_LINE, "","");  
  displayLCD("", "", "","");
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  readClock();
  readBme280();
  readPMS7003();
  
  displayDataOnLCD();
  
  delay(1000);
}

void displayDataOnLCD(){
  String firstLine="";
  String secondLine="";
  String thirdLine="";
  String fourthLine="";

  Serial.print(pressure); Serial.print(" Pa\t");    // Pressure in millibars
  Serial.print(humidityPer); Serial.print(" %\t");
  Serial.print(temperatureC); Serial.print(" *C\t");
  Serial.print(temperatureF); Serial.println(" *F\t");

  char temperatureStr[5]; // 4 characters + EOF == SIZE(5)
  char humidityStr[5];
  char pressureStr[5];

  memset(humidityStr, 0, sizeof(humidityStr));
  memset(temperatureStr, 0, sizeof(temperatureStr));
  memset(pressureStr, 0, sizeof(pressureStr));
  
  dtostrf(temperatureC, 2, 1, temperatureStr);  //format the display string (2 digits, 1 dp)
  dtostrf(humidityPer, 2, 1, humidityStr); 
  dtostrf(pressure, 4, 0, pressureStr); 
   
  firstLine = shortTime + String(" TMP:") +  temperatureStr + "c";
  secondLine = String("PRE:") +  pressureStr + "Pa " + String("HUM:") +  humidityStr + "%";
  thirdLine =  String("PM1.0:") +  pm_1 + " ug/m^3";
  fourthLine = String("PM2.5:") + pm_2_5 + String(" PM10:") + pm_10 + " ";
  displayLCD(firstLine, secondLine, thirdLine, fourthLine);
}
//void initSDCard(){
//  if (!SD.begin(SD_CS_PIN)) {
//    Serial.println("SD Card: initialization failed!");
//  } else {
//    Serial.println("SD Card: OK!");
//  }
//}
void initClock(){
  rtc.writeProtect(true);// 是否防止寫入 (日期時間設定成功後即可改成true)
  rtc.halt(false);// 是否停止計時
}
void setClockTime(){
  // Set the time function.
  //  rtc.writeProtect(false);// 是否防止寫入 (日期時間設定成功後即可改成true)
  //  rtc.halt(false);// 是否停止計時
  //  Time t(2017, 6, 16, 22, 19, 00, Time::kFriday); //年 月 日 時 分 秒 星期幾 (日期時間設定成功後即可註解掉)
  //  rtc.time(t);//設定日期時間 (日期時間設定成功後即可註解掉)
}
void readClock(){
  Time t = rtc.time();
  
//  snprintf(longTime, sizeof(longTime), "%04d-%02d-%02d %02d:%02d:%02d",
//           t.yr, t.mon, t.date,
//           t.hr, t.min, t.sec);
  
  snprintf(shortTime, sizeof(shortTime), "%02d%02d %02d:%02d",
           t.mon, t.date,
           t.hr, t.min);
//  Serial.println(longTime);
  Serial.println(shortTime);
}
void initBme280(){
  if (!bme280.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }  
  bme280.setTempCal(-1);
}

void readBme280(){
  bme280.readSensor(); 
  
  temperatureC=bme280.getTemperature_C();
  temperatureF=bme280.getTemperature_F();
  humidityPer=bme280.getHumidity();
  pressure=bme280.getPressure_MB();
  
}
void initPMS7003(){
  myPMS7003.begin(9600);
}

unsigned int getPMS7003Data(unsigned char chrSrc[], byte bytHigh, byte bytLow)
{
   return (chrSrc[bytHigh] << 8) + chrSrc[bytLow];
}
void readPMS7003(){
   unsigned char chrData[30];
   
   if (myPMS7003.available())
   {
      pms7003ChrRecv = myPMS7003.read();
      
      if (pms7003ChrRecv == START_1 && bytCount == 0)  bytCount = 1;
      if (pms7003ChrRecv == START_2 && bytCount == 1)  bytCount = 2;

      if (bytCount == 2)
      {
         bytCount = 0;
         
         for(int i = 0; i < 30; i++)
         {
            chrData[i] = myPMS7003.read();
            //Serial.print(String(chrData[i], HEX));
            //Serial.print("-");
         } // end for(bytCount = 0; bytCount < 30; bytCount++)
         //Serial.println("");
         
         //ShowTitle(chrData);
         Serial.println("===================================================");
         Serial.print("Data Length = ");
         Serial.print((unsigned int) (chrData[DATA_LENGTH_H] << 8) + chrData[DATA_LENGTH_L]);
         Serial.print(", Device Version = ");
         Serial.print((unsigned int) chrData[VERSION]);
         Serial.print(" (Src=");  Serial.print(chrData[VERSION]);   Serial.print(" HEX="); Serial.print(String(chrData[VERSION], HEX));
         Serial.print("), Error Code = ");
         Serial.println((unsigned int) chrData[ERROR_CODE]);
         Serial.println("");
         
         //ShowPM_ATMO(chrData);
         pm_1 = getPMS7003Data(chrData, PM1_0_ATMOSPHERE_H, PM1_0_ATMOSPHERE_L);
         pm_2_5 = getPMS7003Data(chrData, PM2_5_ATMOSPHERE_H, PM2_5_ATMOSPHERE_L);
         pm_10 = getPMS7003Data(chrData, PM10_ATMOSPHERE_H, PM10_ATMOSPHERE_L);
         Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
         Serial.println("                   Atmosphere (ug/m^3)");
         Serial.println("  PM 1.0     PM 2.5     PM 10");
         Serial.println("---------------------------------------------------");
         Serial.print("  ");
         Serial.print(pm_1);
         Serial.print("          ");
         Serial.print(pm_2_5);
         Serial.print("          ");
         Serial.println(pm_10);
         Serial.println("");

         //ShowPM_CF(chrData);
         Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
         Serial.println("                   CF = 1 (ug/m^3)");
         Serial.println("  PM 1.0     PM 2.5     PM 10");
         Serial.println("---------------------------------------------------");
         Serial.print("  ");
         Serial.print(getPMS7003Data(chrData, PM1_0_CF1_H, PM1_0_CF1_L));
         Serial.print("          ");
         Serial.print(getPMS7003Data(chrData, PM2_5_CF1_H, PM2_5_CF1_L));
         Serial.print("          ");
         Serial.println(getPMS7003Data(chrData, PM10_CF1_H, PM10_CF1_L));
         Serial.println("");       

         //ShowPM_Count(chrData);
         Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
         Serial.println("                   Dusty Count");
         Serial.println("  >um0.3     >0.5um     >1.0um     >2.5um     >5.0um     >10um");
         Serial.println("--------------------------------------------------------------");
         Serial.print("  ");
         Serial.print(getPMS7003Data(chrData, UM0_3_H, UM0_3_L));
         Serial.print("        ");
         Serial.print(getPMS7003Data(chrData, UM0_5_H, UM0_5_L));
         Serial.print("        ");
         Serial.print(getPMS7003Data(chrData, UM1_0_H, UM1_0_L));
         Serial.print("        ");
         Serial.print(getPMS7003Data(chrData, UM2_5_H, UM2_5_L));
         Serial.print("        ");
         Serial.print(getPMS7003Data(chrData, UM5_0_H, UM5_0_L));
         Serial.print("        ");
         Serial.print(getPMS7003Data(chrData, UM10_H, UM10_L));
         Serial.print("        ");
         
         Serial.println("");

         //Serial.print("PM 1.0 Atmosphere = ");
         //Serial.println(getPMS7003Data(chrData, PM1_0_ATMOSPHERE_H, PM1_0_ATMOSPHERE_L));
         //Serial.print("PM 2.5 Atmosphere = ");
         //Serial.println(getPMS7003Data(chrData, PM2_5_ATMOSPHERE_H, PM2_5_ATMOSPHERE_L));
         //Serial.print("PM 10 Atmosphere = ");
         //Serial.println(getPMS7003Data(chrData, PM10_ATMOSPHERE_H, PM10_ATMOSPHERE_L));

      } // end if (bytCount == 2)
      
   }
}


void initLCD(){
  lcd.begin(LCD_DIGITS_PER_LINE, LCD_LINES); // initialize the LCD
  lcd.backlight(); // Turn on the blacklight and print a message.
  //Serial.println("LCD OK");
}

// firstLine: LCD First Line
// secondLine: LCD Second Line
// thirdLine: LCD Third Line
// fourthLine: LCD Fourth Line
void displayLCD(String firstLine, String secondLine, String thirdLine, String fourthLine) {
 // Serial.println("LCD<BEGIN>");
//  Serial.println(firstLine);
//  Serial.println(secondLine);
//  Serial.println(thirdLine);
//  Serial.println(fourthLine);
//  Serial.println("LCD<END>");
  lcd.clear();
  if (firstLine.length()>0) {
    lcd.setCursor(0, 0);
    lcd.print(firstLine);
  }
  if ( secondLine.length()>0) {
    lcd.setCursor(0, 1);
    lcd.print(secondLine);
  }
  if ( thirdLine.length()>0) {
    lcd.setCursor(0, 2);
    lcd.print(thirdLine);
  }
  if ( fourthLine.length()>0) {
    lcd.setCursor(0, 3);
    lcd.print(fourthLine);
  }
}
