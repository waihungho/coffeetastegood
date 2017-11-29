// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Arduino Software Version v1.6.12
// Board  
//  Mega 2560
//
// Sensors:
//  1. LED (I2C)
//  2. PMS3003 (PM2.5 / PM1.0 / PM10.0)
//  3. DHT 溫濕度
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------
//  PIN Configuration (BEGIN)
// ------------------------------------------
// DHT 溫濕度 PIN 2:
#define DHT_PIN 2 

// LED Display PIN:
//  LED     Arduino(MEGA2560)
//  VCC     5V
//  GND     GND
//  SDA     SDA(Pin 21)
//  SCL     SCL(Pin 20)

// PMS3003 (PM2.5 / PM1.0 / PM10.0) PIN:
//  PMS3003     Arduino(MEGA2560)
//  PIN1        5V
//  PIN2        GND
//  PIN4        TX1 (Pin 18)
//  PIN5        RC1 (Pin 19)   // 如需修改, 需修改 Serial1 轉為 SerialX
// ------------------------------------------
//  PIN Configuration (END)
// ------------------------------------------

// ------------------------------------------
//  Software Configuration (BEGIN)
// ------------------------------------------
#define SERIAL_BAUD_RATE 9600
#define WELCOME_MSG_FIRST_LINE "Welcome!"
#define WELCOME_MSG_SECOND_LINE "Loading......"
#define PMS3003_DISPLAY_DURATION 10000  // The duration to display PM2.5 message on LED
#define DHT_DISPLAY_DURATION 10000      // The duration to display DHT message on LED
// ------------------------------------------
//  Software Configuration (END)
// ------------------------------------------


// LED Display Configuration (BEGIN)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DIGITS_PER_LINE 16  // 16 Characters per LINE
LiquidCrystal_I2C lcd(0x27, DIGITS_PER_LINE, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display
// LED Display Configuration (END)

// PMS3003 Configuration (BEGIN)
// http://www.icshop.com.tw/product_info.php/products_id/20460
//首先，它可以採樣測定的空氣懸浮微粒有三種規格 0.3-1.0um/1.0-2.5um/2.5-10um，
//也就是說我們可以拿到 PM1.0/PM2.5/PM10 的測定資料(ug/m3)。
//而且PMS3003 的 datasheet 寫到他有兩套檢定空氣品質濃度的方法，
//分別是可以獲得「大氣環境下」和「標準顆粒物」兩組資料值，所以程式裡面每一次從 sensor 那邊得到的資料就會有2組，6個測定值。（這裡我會在意的是「大氣環境下」測得的這組）
long pmcf10 = 0; // PM1.0  標準顆粒物
long pmcf25 = 0; // PM2.5  標準顆粒物
long pmcf100 = 0; // PM10.0 標準顆粒物
long pmat10 = 0; // PM1.0  大氣環境下
long pmat25 = 0; // PM2.5  大氣環境下
long pmat100 = 0; // PM10.0 大氣環境下
char buf[50]; 
// PMS3003 Configuration (BEGIN)

// DHT 溫度和濕度 Configuration (BEGIN)
#include <dht.h>   
#define DHT_INIT_WAIT 1000 
dht DHT;   
// DHT Configuration (BEGIN)

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial1.begin(SERIAL_BAUD_RATE);  // Mega 2560: Pin 19 (Blue) --> PMS3003

  initLED(); // initialize LED
  displayLED(WELCOME_MSG_FIRST_LINE, WELCOME_MSG_SECOND_LINE);
  
  initDHT(); // initialize DHT
}

void loop() { // put your main code here, to run repeatedly:
 
  // Show DHT
  showDHTonLED();

  // Show PMS3003
  int count = 0;
  unsigned char c;
  unsigned char high;
  while (Serial1.available()) {
    c = Serial1.read();
    if ((count == 0 && c != 0x42) || (count == 1 && c != 0x4d)) {
      Serial.println("check failed");
      break;
    }
    if (count > 15) {
      Serial.println("complete");
      showPMS3003onLED();
      break;
    }
    else if (count == 4 || count == 6 || count == 8 || count == 10 || count == 12 || count == 14) {
      high = c;
    }
    else if (count == 5) {
      pmcf10 = 256 * high + c;
      Serial.print("CF=1, PM1.0=");
      Serial.print(pmcf10);
      Serial.println(" ug/m3");
    }
    else if (count == 7) {
      pmcf25 = 256 * high + c;
      Serial.print("CF=1, PM2.5=");
      Serial.print(pmcf25);
      Serial.println(" ug/m3"); // 微克/立方公尺

      lcd.home();
      lcd.print("PM2.5: ");
      lcd.print(pmcf25);
      lcd.print(" ug/m3");
    }
    else if (count == 9) {
      pmcf100 = 256 * high + c;
      Serial.print("CF=1, PM10=");
      Serial.print(pmcf100);
      Serial.println(" ug/m3");
    }
    else if (count == 11) {
      pmat10 = 256 * high + c;
      Serial.print("atmosphere, PM1.0=");
      Serial.print(pmat10);
      Serial.println(" ug/m3");
    }
    else if (count == 13) {
      pmat25 = 256 * high + c;
      Serial.print("atmosphere, PM2.5=");
      Serial.print(pmat25);
      Serial.println(" ug/m3");
    }
    else if (count == 15) {
      pmat100 = 256 * high + c;
      Serial.print("atmosphere, PM10=");
      Serial.print(pmat100);
      Serial.println(" ug/m3");
    }
    count++;
  }
  while (Serial1.available()) Serial1.read(); // Must do this here, otherwise it may cause "Check Failed" problem.
  Serial.println();
  delay(PMS3003_DISPLAY_DURATION);
}

void initLED(){
  lcd.begin(); // initialize the LCD
  lcd.backlight(); // Turn on the blacklight and print a message.
}

void initDHT(){
  delay(DHT_INIT_WAIT);  //Wait rest of 1000ms recommended delay before accessing DHT sensor   
}

void showPMS3003onLED() {
  // PM2.5:XXX ug/m3
  // PM1:XXX PM10:XXX
//long pmcf10 = 0; // PM1.0  標準顆粒物
//long pmcf25 = 0; // PM2.5  標準顆粒物
//long pmcf100 = 0; // PM10.0 標準顆粒物
//long pmat10 = 0; // PM1.0  大氣環境下
//long pmat25 = 0; // PM2.5  大氣環境下
//long pmat100 = 0; // PM10.0 大氣環境下
  if (pmat25!=0 && pmat10!=0 && pmat100!=0 ) {
    String firstLine = String("PM2.5: ") +  pmat25 + " ug/m3";
    String secondLine  = String("PM1:") + pmat10 + " PM10:" + pmat100;
    displayLED(firstLine, secondLine);
//    delay(PMS3003_DISPLAY_DURATION);  
  } else {
     Serial.println("PMS3003 is not ready. ");   
  }
}

void showDHTonLED() {
  DHT.read11(DHT_PIN);   //去library裡面找DHT.read11 
  if (DHT.humidity!=0 && DHT.temperature!=0 && DHT.humidity!=255 && DHT.temperature!=255){
    Serial.print("Humidity = ");   
    Serial.print(DHT.humidity);   
    Serial.print("% ");   
    Serial.print("temperature = ");   
    Serial.print(DHT.temperature);   
    Serial.println("C ");   
    String firstLine = String("Temp: ") +  DHT.humidity + "C";
    String secondLine  = String("Humidity:") + DHT.temperature + "%";
    displayLED(firstLine, secondLine);
    delay(DHT_DISPLAY_DURATION);           
  } else {
     Serial.println("DHT sensor is not ready.");   
  }
}


// firstLine: LED First Line
// secondLine: LED Second Line
void displayLED(String firstLine, String secondLine) {
  int i;
  String printFirstLine = firstLine;
  for ( i = sizeof(printFirstLine); i <= DIGITS_PER_LINE; i++) // Clearing the previous message on LED.
    printFirstLine += " ";
  lcd.home();
  lcd.print(printFirstLine);

  String printSecondLine = secondLine;
  for ( i = sizeof(printSecondLine); i < DIGITS_PER_LINE; i++)
    printSecondLine += " ";
  lcd.home();
  lcd.setCursor(0, 1);
  lcd.print(printSecondLine);
}
