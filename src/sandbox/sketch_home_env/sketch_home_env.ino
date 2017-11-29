// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Arduino Software Version v1.6.12
// Arduino Board UNO  
//
// Sensors:
//  1. LCD (I2C 4x20)
//  2. BME280 (Temp, Humidity, Barometer) 
//  3. DS3231 Clock (Optional)    [#define ENABLE_CLOCK_DS3231 1]   <<Clock & SD Card Module must use together>>
//  4. SD Card Module (Optional)  [#define ENABLE_SD_CARD 1]        <<Clock & SD Card Module must use together>>
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Program Specification 
//    1. setup()
//        initialize all sensors（LCD,  BME280, Clock, SD Card)        
//    2. loop()
//        a. Read data from DHT     [readDHT()]
//        b. Read BME280
//        c. Display data on LCD    [displayDataOnLCD()]
//
//    Problem Solving History: 
//      Arduino: If you got "Low Memory Available" error when compiling this program, comment out all Serial.println("xxxx") code.
//
//    Reset the clock time:
//      rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
//      rtc.setTime(23, 00, 0);     // Hh:mn:ss   : Set the time to 12:00:00 (24hr format)
//      rtc.setDate(21, 7, 2017);   // DD,MM,YYYY : Set the date to January 1st, 2014
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------
//  Software Configuration (BEGIN)
// ------------------------------------------
#define SERIAL_BAUD_RATE 9600
#define WELCOME_MSG_FIRST_LINE "AV Home"
#define WELCOME_MSG_SECOND_LINE "v1.0 Loading......"
#define READING_SENSOR_INTERVAL 10000     // Interval to read ALL sensors. 10s interval.
#define ENABLE_CLOCK_DS3231 1             // 1: Enable Clock, 0; Disable Clock.
#define DISPLAY_CLOCK_DS3231_ON_LED 1     // 1: Display time on LED; 0: Dont display.
#define ENABLE_SD_CARD 1                 // 1: Enable SD Card, 0; Disable.
#define SD_CARD_FILENAME "MONITOR.TXT"    // Filename "FAT" 8.3 format (XXXXXXXX.XXX) You must use the 8.3 format, so that file names look like “NAME001.EXT”, where “NAME001” is an 8 character or fewer string, and “EXT” is a 3 character extension.
                                          // SD Card must be formatted as the "FAT" filesystem first. 
// ------------------------------------------
//  Software Configuration (END)
// ------------------------------------------


// ------------------------------------------
//  PIN Configuration (BEGIN)
// ------------------------------------------
// BME280 PIN:
//  BME280     Arduino(UNO)
//  SDA         SDA (IIC)
//  SCL         SCL (IIC)

// LCD Display PIN:
//  LCD     Arduino(UNO)
//  VCC     5V
//  GND     GND
//  SDA     SDA(Pin A4)     (Reference:Arduino Mega2560:Pin 21)
//  SCL     SCL(Pin A5)     (Reference:Arduino Mega2560:Pin 20)

// Clock PIN:
//#define CLOCK_RST_PIN 6 //RST
//#define CLOCK_DAT_PIN 5  //DAT  
//#define CLOCK_CLK_PIN 4  //CLK
#define CLOCK_SDA_PIN A1
#define CLOCK_SCL_PIN A2

// SD Card PIN:
#define SD_CARD_CS_PIN 10  // CS
//  SD Card Module     Arduino(UNO)
//  CS                 PIN10
//  MOSI               PIN11   <-- No Configuration for this library
//  MISO               PIN12   <-- No Configuration for this library 
//  CLK                PIN13   <-- No Configuration for this library 
// ------------------------------------------
//  PIN Configuration (END)
// ------------------------------------------


// LCD Display Configuration (BEGIN)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LCD_DIGITS_PER_LINE 20  // No. of Characters per LINE
#define LCD_LINES 4  // LCD Lines
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address  (This LCD address: 0x3F)
//LiquidCrystal_I2C lcd(0x27, DIGITS_PER_LINE, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display
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


// Clock Configuration (BEGIN)
//#include <stdio.h>
//#include <DS3231.h> // https://github.com/msparks/arduino-DS3231
//DS3231 clockDS3231(CLOCK_RST_PIN, CLOCK_DAT_PIN, CLOCK_CLK_PIN);
boolean isClockOK = false;

#include <DS3231.h>     // library from http://www.rinkydinkelectronics.com/library.php?id=73
DS3231  clockDS3231(CLOCK_SDA_PIN, CLOCK_SCL_PIN);
// Clock Configuration (END)


// SD Card Module Configuration (BEGIN)
//#include <SPI.h>
//#include <SD.h>

//#include <SPI.h>    
//#include "SdFat.h"
//SdFat sd;
//SdFile sdCardFile;
#include <SD.h>
File sdCardFile;
boolean isSuccesToInitSD = false;  // true: Succes to initialize SD Card.
#define SD_FILE_DATA_HEADER "YYYY/MM/DD HH:MN:SS\tTEMP\tHUM"
// SD Card Module Configuration (END)

// Software variables(BEGIN)


boolean writeSDHeader = false;
#define TIME_STR_SIZE 20
#define TEMPERATURE_STR_SIZE 5
#define HUMIDITY_STR_SIZE 5
char timeStr[TIME_STR_SIZE];
char temperatureStr[TEMPERATURE_STR_SIZE];
char humidityStr[HUMIDITY_STR_SIZE];
// Software variables (BEGIN)

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                    FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  
  initClock(); // initialize Clock
  initSDCard(); // initialzie SD Card Module
  
  initLCD(); // initialize LCD
  displayLCD(WELCOME_MSG_FIRST_LINE, WELCOME_MSG_SECOND_LINE, "","");
 
  initBme280();

}


void loop() { // put your main code here, to run repeatedly:

  readBme280();
 
  
  displayDataOnLCD();  // Display message on LCD.

  writeToSDCard();
  
  delay(READING_SENSOR_INTERVAL);

}


void initLCD(){
  lcd.begin(LCD_DIGITS_PER_LINE, LCD_LINES); // initialize the LCD
  lcd.backlight(); // Turn on the blacklight and print a message.
  //Serial.println("LCD OK");
}


void initClock(){
  if(ENABLE_CLOCK_DS3231){
//    clockDS.writeProtect(true); // 是否防止寫入 (日期時間設定成功後即可改成true)
//    clockDS.halt(false);        // 是否停止計時
//    // calibrate time function.
//    //rtc.writeProtect(false);
//    //    Time tt(2017, 7, 18, 23, 57, 00, Time::kTuesday); //年 月 日 時 分 秒 星期幾 (日期時間設定成功後即可註解掉)
//    //    clockDS.time(tt);//設定日期時間 (日期時間設定成功後即可註解掉)
//    //   Serial.println("Clock OK");
  
    clockDS3231.begin();
    
    Time t = clockDS3231.getTime();
    if (t.year==2000){
      isClockOK = false; //If it always return 2000:01:01 00:00:00, set the time again.
    } else {
      isClockOK = true;
    }
  }
}

void initSDCard(){
  if ( ENABLE_SD_CARD ){
    //if (!sd.begin(SD_CARD_CS_PIN, SPI_HALF_SPEED)) {
    if (!SD.begin(SD_CARD_CS_PIN)) {
      //sd.initErrorHalt(); //SdFat specified
      isSuccesToInitSD = false;
      Serial.println("SD Card initialization failed!");
      return;
    } else {
      isSuccesToInitSD = true;
      Serial.println("SD OK");
    }
  }
}


void writeToSDCard(){
  if ( ENABLE_SD_CARD && isSuccesToInitSD ){  // 2016.11.11: Rule of Thumb: dont log first data, which it is often inaccurate.

    //if ( sdCardFile.open(SD_CARD_FILENAME, O_RDWR | O_CREAT | O_AT_END) ) {
    sdCardFile = SD.open(SD_CARD_FILENAME, FILE_WRITE);
    if ( sdCardFile ) { 
      //Serial.println(String("Writing to ") + SD_CARD_FILENAME);
      Time currentTime = readClock();   
      memset(timeStr, ' ', TIME_STR_SIZE);
      snprintf(timeStr, sizeof(timeStr), "%04d/%02d/%02d %02d:%02d:%02d", currentTime.year, currentTime.mon, currentTime.date, currentTime.hour, currentTime.min, currentTime.sec); // timeStr[20]
      memset(temperatureStr, ' ', TEMPERATURE_STR_SIZE);
      memset(humidityStr, ' ', HUMIDITY_STR_SIZE);
      dtostrf(temperatureC, 2, 1, temperatureStr);  //format the display string (2 digits, 1 dp)  // temperatureStr[4]
      dtostrf(humidityPer, 2, 1, humidityStr);  // humidityStr[4]
      if (!writeSDHeader){
        sdCardFile.println(SD_FILE_DATA_HEADER);  // Write Header
        writeSDHeader = true;
      }
      // Modify SD_FILE_DATA_HEADER, if modify this data format

        sdCardFile.println(timeStr + String("\t") +temperatureStr + "\t" +humidityStr);  

      sdCardFile.close();   // flush(), if keep opening file, use flush() to write data immediately.
    } else {
       //Serial.println("ERR: Cannot open ENV_MONITORING.txt...");
    }
  }
}

// ENABLE_CLOCK_DS3231 == 1 in order to use this function.
// Return Time object
Time readClock(){
//  if(!ENABLE_CLOCK_DS3231){
//    Serial.println("ERR: ENABLE_CLOCK_DS3231 must set to 1"); // Use readClock(), ENABLE_CLOCK_DS3231 must set to 1
//  }
  Time t = clockDS3231.getTime();
//  char buf[50];  
//  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
//           t.yr, t.mon, t.date,
//           t.hr, t.min, t.sec);
//  Serial.println(buf);
  return t;
}



void displayDataOnLCD(){
  String firstLine;
  firstLine = WELCOME_MSG_FIRST_LINE;
  if ( ENABLE_CLOCK_DS3231 && !isClockOK ) {
    firstLine = "Clock Failed.";
  } else if ( ENABLE_SD_CARD && !isSuccesToInitSD ) {
    firstLine = "SD Failed.";
  } else {
    firstLine = WELCOME_MSG_FIRST_LINE;
  }
  if(ENABLE_CLOCK_DS3231 && DISPLAY_CLOCK_DS3231_ON_LED && isSuccesToInitSD && (!ENABLE_CLOCK_DS3231 || (ENABLE_CLOCK_DS3231 && isClockOK)) ) {
    Time clockTime = readClock();
    memset(timeStr, ' ', TIME_STR_SIZE);
    //snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",clockTime.yr, clockTime.mon, clockTime.date, clockTime.hr, clockTime.min, clockTime.sec);
    snprintf(timeStr, sizeof(timeStr), " %02d/%02d %02d:%02d",clockTime.mon, clockTime.date, clockTime.hour, clockTime.min);
    firstLine += timeStr;
  }
  memset(temperatureStr, ' ', TEMPERATURE_STR_SIZE);
  memset(humidityStr, ' ', HUMIDITY_STR_SIZE);
  dtostrf(temperatureC, 2, 1, temperatureStr);  //format the display string (2 digits, 1 dp)
  dtostrf(humidityPer, 2, 1, humidityStr); 
  String secondLine ="";
  secondLine = String("TMP:") +  temperatureStr + "c " + String("HUM:") + humidityStr + "%";
  
  String thirdLine = "";
  String fourthLine = "";

  displayLCD(firstLine, secondLine, thirdLine, fourthLine);
}



// firstLine: LCD First Line
// secondLine: LCD Second Line
// thirdLine: LCD Third Line
// fourthLine: LCD Fourth Line
void displayLCD(String firstLine, String secondLine, String thirdLine, String fourthLine) {
  Serial.println("LCD<BEGIN>");
  Serial.println(firstLine);
  Serial.println(secondLine);
  Serial.println(thirdLine);
  Serial.println(fourthLine);
  Serial.println("LCD<END>");
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

