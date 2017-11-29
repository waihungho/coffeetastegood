
// On/Off Switch PIN:
#define SWITCH_PIN 13  
// Circuit:
// 5V <--->  SWITCH 
//              | <-------> PIN 13
//           RESISTOR <---> GND

#define SWITCH_ON 0       // Press down is ON.
#define SWITCH_OFF 1

// ------------------------------------------
//  Switch (BEGIN)
// ------------------------------------------
int switch_status;
// ------------------------------------------
//  Switch (END)
// ------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  
  initSwitch();

}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
 

  // -------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //  Detect: Press switch
  // -------------------------------------------------------------------------------------------------------------------------------------------------------------------
  int thisStatus=readSwitch();  // Check for pressing switch
  boolean changeStatus = false;
  if ( thisStatus != switch_status ) {
    switch_status = thisStatus;
    changeStatus = true;
    Serial.print("SWITCH[1:OFF,0:ON]:");Serial.println(switch_status);
    
    delay(200); // for preventing bounce
  }
  //Serial.print("SWITCH[1:OFF,0:ON]:");Serial.println(switch_status);

  if (switch_status == SWITCH_ON  && changeStatus) {
     Serial.println("WoW");
  }
  
}

void initSwitch(){
  pinMode(SWITCH_PIN,INPUT);
  switch_status = SWITCH_OFF;
}
int readSwitch(){
  int switchState=0;
  switchState = digitalRead(SWITCH_PIN);
  return switchState;
}


