const int pinBtTX = 5;  // Bluetooth TX (RED)
const int pinBtRX = 4;  // Bluetooth RX (BROWN)
const int pinRelay = 2;  // Relay
const int pinLED = 13; // LED

// Bluetooth Kick start
// LED indicate START / STOP
// Relay control water
// Timer control interval of water flow

const unsigned int STATUS_ERR = 999;
const unsigned int STATUS_OFF = 0;
const unsigned int STATUS_ON = 1;
const unsigned int STATUS_DOING = 2;
unsigned int statusMap = STATUS_OFF;

// Bluetooth (BEGIN)
#include  <SoftwareSerial.h>
SoftwareSerial BTSerial(pinBtTX, pinBtRX); // TX | RX

#include <Timer.h>
Timer timerClock;
int timerEvent;
const float PER_SEC =  1000.0;
const float PER_MIN =  PER_SEC * 60.0;
const float PER_HOUR = PER_MIN * 60.0;
const float PER_DAY =  PER_HOUR * 24.0;

const int SHORT_DELAY  = 200;
// *************************************************************************************************************************************************************************************************
//   MAIN CONFIGURATION
// ************************************************************************************************************************************************************************************************* 
const int WATER_FLOW_DURATION = PER_SEC * 5.0 ;
const float WATER_FLOW_INTERVAL = PER_SEC * 30.0 ;
// *************************************************************************************************************************************************************************************************

void logStatus(){
  String statusStr;
  switch (statusMap) {
    case STATUS_OFF:
      statusStr = "STATUS_OFF";
      break;
    case STATUS_ON:
      statusStr = "STATUS_ON";
      break;
    case STATUS_DOING:
      statusStr = "STATUS_DOING";
      break;
    case STATUS_ERR:
      statusStr = "STATUS_ERR";
      break;
    default: 
       statusStr = "STATUS_UNKNOWN";
      break;
  }
  Serial.println(statusStr);
}

void putWater(){
  Serial.println("Put Water <BEGIN>");
  digitalWrite(pinRelay, HIGH);   // Power Off
  delay(WATER_FLOW_DURATION);
  digitalWrite(pinRelay, LOW);   // Power Off
  delay(SHORT_DELAY);
  Serial.println("Put Water <END>");
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); 
 
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);

  pinMode(pinRelay, OUTPUT); // Relay
  digitalWrite(pinRelay, LOW);   // Power Off
  
  BTSerial.begin(115200);     // Bluetooth Baud Rate : 每個藍牙晶片的鮑率都不太一樣，請務必確認

  // Check Configuration 
  if ( WATER_FLOW_INTERVAL <= WATER_FLOW_DURATION + SHORT_DELAY ) {
    Serial.println("Check Configuration: FAIL! <WATER_FLOW_INTERVAL > WATER_FLOW_DURATION + SHORT_DELAY>. Should adjust WATER_FLOW_INTERVAL.");
    statusMap == STATUS_ERR;
  } else {
    statusMap == STATUS_OFF;
    Serial.println("Check Configuration: OK!");
  }

  if (!statusMap == STATUS_ERR ) 
    Serial.println("System Up and Ready!");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( statusMap == STATUS_OFF ) {
    if (BTSerial.available()) { // Keep reading from HC-05 and send to Arduino Serial Monitor     
      char cmdBT = BTSerial.read();
      Serial.print("Command from Bluetooth :");Serial.write(cmdBT);Serial.println("");
      if(cmdBT == '1') {
        statusMap = STATUS_ON; // Start   
        logStatus();   
        digitalWrite(pinLED, HIGH);
      } else if(cmdBT== '3' ) {
        // Trial Run
        putWater();
      }
    } 
  } else if ( statusMap == STATUS_ON ) {
    statusMap = STATUS_DOING;
    logStatus();
    timerEvent = timerClock.every(WATER_FLOW_INTERVAL, putWater); 
  } else if ( statusMap == STATUS_DOING) {
     timerClock.update();
     if (BTSerial.available()) { // Keep reading from HC-05 and send to Arduino Serial Monitor     
      char cmdBT = BTSerial.read();
      Serial.print("Command from Bluetooth :");Serial.write(cmdBT);Serial.println("");
      if(cmdBT == '2') {
        statusMap = STATUS_OFF; // Start     
        logStatus(); 
        timerClock.stop(timerEvent);
        digitalWrite(pinLED, LOW);
      }
    } 
  }
}
