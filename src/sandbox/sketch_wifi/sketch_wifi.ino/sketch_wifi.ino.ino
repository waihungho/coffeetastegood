// WIFI PIN (From the upper side)
// 1(RX)      5(GND)
// 2(3.3V)    6
// 3          7(for update firmware)
// 4(3.3V)    8(TX)

// Update ESP8266 firware : (http://lets-make-games.blogspot.tw/2015/04/wifi-esp8266-wifi.html)
// Step1. Connect ESP8266 to computer USB using CP2101(USB to TTL)
// Step2. Connect ESP8266[PIN#7] to Arduino GND
// Step3. Turn On the arduino and connect USB
// Step4. Update firmware to v0.9.2.2 (v0.9.2.2 AT Firmware.bin) using esp8266_flasher.exe
// Step5. Turn Off the arduino and disconnect USB
// Step6. Disconnect ESP8266[PIN#7] to Arduino GND

// Update ESP8266 Configuration using Realterm: (http://lets-make-games.blogspot.tw/2015/04/wifi-esp8266-wifi.html)
// AT+GMR       --> 印出 firmware: 0018000902
// AT+CIOBAUD?   --> Check Baud Rate:9600
// AT+CWMODE=1
// AT+CIPMUX=1  
// AT+CWJAP="vahome","0958816994"  --> connect WIFI
// AT+CIFSR       --> Check IP:

// Use this program to try 
// Library used: ITEADLIB_Arduino_WeeESP8266 
// sample code : https://mlwmlw.org/2015/07/%E6%B7%B1%E5%85%A5%E6%B7%BA%E5%87%BA-wifi-%E6%99%B6%E7%89%87-esp8266-with-arduino/


#include "ESP8266.h"

#include <SoftwareSerial.h>

#define SSID        "vahome"
#define PASSWORD    "0958816994"

SoftwareSerial mySerial(3, 2); /* RX:D3, TX:D2 */
ESP8266 wifi(mySerial);

void setup(void)
{
    Serial.begin(9600);
    Serial.print("setup begin\r\n");

    Serial.print("FW Version: ");
    Serial.println(wifi.getVersion().c_str());
    
    
    if (wifi.setOprToStation()) {
        Serial.print("to station ok\r\n");
    } else {
        Serial.print("to station err\r\n");
    }

    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");       
        Serial.println(wifi.getLocalIP().c_str());
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    Serial.print("setup end\r\n");
}

void loop(void)
{
}

