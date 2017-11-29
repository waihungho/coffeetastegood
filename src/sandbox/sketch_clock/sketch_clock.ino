#include <stdio.h>
#include <DS1302.h> // https://github.com/msparks/arduino-ds1302

const int kCePin   = 1;  //RST
const int kIoPin   = 2;  //DAT
const int kSclkPin = 3;  //CLK

// DS1302 rtc([RST], [DAT], [CLOCK]); 三個pin的接法
DS1302 rtc(kCePin, kIoPin, kSclkPin);

void printTime() {//顯示日期時間的函式

  
  Time t = rtc.time();
  char buf[50];
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  Serial.println(buf);
}

void setup() {
  Serial.begin(9600);
  
  rtc.writeProtect(true);// 是否防止寫入 (日期時間設定成功後即可改成true)
  rtc.halt(false);// 是否停止計時
 
 // Set the time function.
// rtc.writeProtect(false);// 是否防止寫入 (日期時間設定成功後即可改成true)
//    Time tt(2017, 7, 18, 23, 59, 00, Time::kTuesday); //年 月 日 時 分 秒 星期幾 (日期時間設定成功後即可註解掉)
//    rtc.time(tt);//設定日期時間 (日期時間設定成功後即可註解掉)
//   Serial.println("Clock OK");
}
void loop() {
  printTime();
  delay(1000);
}
