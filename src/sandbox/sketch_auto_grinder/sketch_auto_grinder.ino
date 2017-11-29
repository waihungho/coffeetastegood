// ------------------------------------------
//  PIN Configuration (BEGIN)
// ------------------------------------------
// Relay PIN:
#define RELAY_PIN 11 

// On/Off Switch PIN:
#define SWITCH_PIN 7    
// Circuit:
// 5V <--->  SWITCH 
//              | <-------> PIN 7
//           RESISTOR <---> GND

// Weight PIN: 
//  Weight      Keyes 234
//  RED         E+
//  BLACK       E-
//  GREEN       A+
//  WHITE       A-
//  N/A         B+
//  N/A         B-
#define WEIGHER_SCK_PIN 9
#define WEIGHER_DOUT_PIN 10 

// Rotary Encoder PIN:
#define ROTARY_CLK_PIN 2        // IMPORTANT: Only Pin2 and Pin3 have interrupt for UNO
#define ROTARY_CLK_INTERRUPT 0  // NOT PIN number, 0 for Pin2 interrupt
#define ROTARY_DATA_PIN 1       

#define ROTARY_2_CLK_PIN 3        // IMPORTANT: Only Pin2 and Pin3 have interrupt for UNO
#define ROTARY_2_CLK_INTERRUPT 1  // NOT PIN number, 0 for Pin2 interrupt
#define ROTARY_2_DATA_PIN 4   

#define BUTTON_PANEL_1_PIN A0
#define BUTTON_PANEL_2_PIN A1
#define BUTTON_PANEL_3_PIN A5
#define BUTTON_PANEL_4_PIN A4
#define BUTTON_PANEL_5_PIN A3
#define BUTTON_PANEL_6_PIN A2
#define BUTTON_PANEL_7_PIN A1
#define BUTTON_PANEL_8_PIN A0


// LCD    Arduino
//  SDA     SDA
//  SCL     SCL
// ------------------------------------------
//  PIN Configuration (END)
// ------------------------------------------

// ------------------------------------------
//  Software Configuration (BEGIN)
// ------------------------------------------
#define SERIAL_BAUD_RATE 9600
#define RELAY_ON 1
#define RELAY_OFF 0
#define SWITCH_ON 0       // Press down is ON.
#define SWITCH_OFF 1
#define PRODUCTION 0      // 0: dont print message to Serial.print for performance.
// ------------------------------------------
//  Software Configuration (END)
// ------------------------------------------

// ------------------------------------------
//  Software Status (BEGIN)
// ------------------------------------------
int softwareStatus;
const int STATUS_INIT = 0;
const int STATUS_START = 1;
//const int STATUS_END = 2;
// ------------------------------------------
//  Software Status (END)
// ------------------------------------------


// ------------------------------------------
//  Switch (BEGIN)
// ------------------------------------------
int switch_status;
// ------------------------------------------
//  Switch (END)
// ------------------------------------------

// ------------------------------------------
//  WEIGHER (BEGIN)
// ------------------------------------------
#include <HX711.h>    // https://github.com/bogde/HX711  White Line seems not that OK.
//HX711 hx(WEIGHER_SCK_PIN, WEIGHER_DOUT_PIN, 128, 0.00127851); // NEW MEDAL
//HX711 weigher(WEIGHER_SCK_PIN, WEIGHER_DOUT_PIN, 128, 0.00246500); // OLD ONE
//const unsigned int WEIGHER_READ_TIMES  = 3;
HX711 weigher(WEIGHER_SCK_PIN, WEIGHER_DOUT_PIN);   // parameter "gain" is ommited; the default value 128 is used by the library
#define WEiGHER_SCALE 409.05  // Different medal , different scale. (usually decrease this value if the weight is under-estimated)
                               // 1588.05 : small grey scale.
                               // 395.05 : the small medal one.
const unsigned int WEIGHER_READ_TIMES  = 3; // Read 3 times for taking average value.
#define BASE_TARGET_WEIGTH 15
#define WEIGHT_ADJUST_ZERO true
double target_weight = BASE_TARGET_WEIGTH;
double final_weight = 0;
#define FINAL_WEIGHT_STR_SIZE 5
#define TARGET_WEIGHT_STR_SIZE 5
char finalWeightStr[FINAL_WEIGHT_STR_SIZE];
char targetWeightStr[TARGET_WEIGHT_STR_SIZE];

#define WEIGHER_DIFF 50 // 50g difference, then start
double this_weight = 0;
// ------------------------------------------
//  WEIGHER (END)
// ------------------------------------------

// ------------------------------------------
//  Rotary Encoder (BEGIN)
// ------------------------------------------
static long rotary_count = 0;      
volatile boolean rotary_turnDetected=false;
volatile boolean rotary_up=false;

static long rotary_2_count = 0;      
volatile boolean rotary_2_turnDetected=false;
volatile boolean rotary_2_up=false;
// ------------------------------------------
//  Rotary Encoder (END)
// ------------------------------------------

// ------------------------------------------
//  8-Button Panel (END)
// ------------------------------------------
boolean buttonOn1 = false; // true: button clicked
boolean buttonOn2 = false;
boolean buttonOn3 = false;
boolean buttonOn4 = false;
boolean buttonOn5 = false;
boolean buttonOn6 = false;
boolean buttonOn7 = false;
boolean buttonOn8 = false;
// ------------------------------------------
//  8-Button Panel (END)
// ------------------------------------------

// ------------------------------------------
//  LCD (BEGIN)
// ------------------------------------------
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 20 chars and 4 line display
//LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x20 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x27);  // Set the LCD I2C address  (This LCD address: 0x3F)
#define DIGITS_PER_LINE 16
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address  (This LCD address: 0x27/0x3F)
// ------------------------------------------
//  LCD (END)
// ------------------------------------------

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  initLCD();
  initRelay();
  initButtonPanel();
  initSwitch();
  initRotaryEncoder();
  initWeigher();
  softwareStatus = STATUS_INIT;
  displayLCD();
  Serial.println("AUTO-WEIGHER READY");
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
  if ( softwareStatus == STATUS_INIT ){ 
    // -------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //  Detect: Rotary Encoder (set the target weight only in the initial state)
    // -------------------------------------------------------------------------------------------------------------------------------------------------------------------    
    readRotaryEncoder();
    readButtonPanel();
//    if (buttonOn1)
//      Serial.println("Button 1 clicked");
//    if (buttonOn2)
//      Serial.println("Button 2 clicked");
//    if (buttonOn3)
//      Serial.println("Button 3 clicked");
//    if (buttonOn4)
//      Serial.println("Button 4 clicked");
//    if (buttonOn5)
//      Serial.println("Button 5 clicked");
//    if (buttonOn6)
//      Serial.println("Button 6 clicked");
//    if (buttonOn7)
//      Serial.println("Button 7 clicked");
//    if (buttonOn8)
//      Serial.println("Button 8 clicked");
              
    delay(500);
  }

  // -------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //  Detect: Press switch
  // -------------------------------------------------------------------------------------------------------------------------------------------------------------------
  int thisStatus=readSwitch();  // Check for pressing switch
  boolean changeStatus = false;
  //if ( thisStatus != switch_status || buttonOn8) {
  if ( thisStatus != switch_status ) {   
    switch_status = thisStatus;
//    if ( buttonOn8 ) 
//      switch_status = SWITCH_ON;
    
    changeStatus = true;

    Serial.println("Change status");
    delay(100); // for preventing bounce
  }
  if ( softwareStatus == STATUS_INIT && !changeStatus) {
    
    final_weight = readWeigher();
    printToSerialMsg();
    displayLCD();
        
    if ( final_weight - this_weight > WEIGHER_DIFF ) {
      changeStatus = true;
    } else { 
      this_weight = final_weight;
    }
    

  }
//  if (  softwareStatus == STATUS_START && buttonOn7 ) {
//    switch_status = SWITCH_OFF;
//     delay(100); // for preventing bounce
//  }
    
  
  //Serial.print("SWITCH[1:OFF,0:ON]:");Serial.println(switch_status);
  
  // -------------------------------------------------------------------------------------------------------------------------------------------------------------------    
  //  Switch ON: Turn on Relay 
  // -------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //if ( softwareStatus == STATUS_INIT &&  (switch_status == SWITCH_ON || buttonOn8) && changeStatus) {
  if ( softwareStatus == STATUS_INIT &&  (switch_status == SWITCH_ON ) && changeStatus) {
    printToSerialMsg();
    softwareStatus = STATUS_START;
    tareWeigher(); //weigher.tare();
    controlRelay(RELAY_ON);
  // -------------------------------------------------------------------------------------------------------------------------------------------------------------------    
  //  After Turn on Relay: Measure the weight
  //  Once the weight >= Target Weight: Turn off Relay
  // ------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
  } else if ( softwareStatus == STATUS_START && switch_status == SWITCH_ON ) {
    final_weight = readWeigher();
    printToSerialMsg();
    if ( final_weight > target_weight ) {
      controlRelay(RELAY_OFF);
      softwareStatus = STATUS_INIT;
    } 
    displayLCD();
  // -------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //  Switch Off: All Stop.
  // -------------------------------------------------------------------------------------------------------------------------------------------------------------------
  } else if ( changeStatus && switch_status == SWITCH_OFF ) {
  // } else if ( switch_status == SWITCH_OFF ) {
    controlRelay(RELAY_OFF);
    softwareStatus = STATUS_INIT;
    resetFinalWeight();
  }
  
}



// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void initButtonPanel(){
//  pinMode(BUTTON_PANEL_1_PIN, INPUT);     
//  pinMode(BUTTON_PANEL_2_PIN, INPUT);     
//  pinMode(BUTTON_PANEL_3_PIN, INPUT);     
//  pinMode(BUTTON_PANEL_4_PIN, INPUT);   
//  pinMode(BUTTON_PANEL_5_PIN, INPUT);     
//  pinMode(BUTTON_PANEL_6_PIN, INPUT);      
//    pinMode(BUTTON_PANEL_7_PIN, INPUT);      
//    pinMode(BUTTON_PANEL_8_PIN, INPUT);     
}
void readButtonPanel(){
  buttonOn1 = false; // true: button clicked
  buttonOn2 = false;
  buttonOn3 = false;
  buttonOn4 = false;
  buttonOn5 = false;
  buttonOn6 = false;
  buttonOn7 = false;
  buttonOn8 = false;  
//  if ( analogRead(BUTTON_PANEL_1_PIN) != 0)
//    buttonOn1=true;
//  if ( analogRead(BUTTON_PANEL_2_PIN) != 0)
//    buttonOn2=true;
//  if ( analogRead(BUTTON_PANEL_3_PIN) != 0)
//    buttonOn3=true;
//  if ( analogRead(BUTTON_PANEL_4_PIN) != 0)
//    buttonOn4=true;
//  if ( analogRead(BUTTON_PANEL_5_PIN) != 0)
//    buttonOn5=true;
//  if ( analogRead(BUTTON_PANEL_6_PIN) != 0)
//    buttonOn6=true;
//  if ( analogRead(BUTTON_PANEL_7_PIN) != 0)
//    buttonOn7=true;
//  if ( analogRead(BUTTON_PANEL_8_PIN) != 0)
//    buttonOn8=true;           
}

void initRelay(){
  pinMode(RELAY_PIN, OUTPUT);
  controlRelay(RELAY_OFF);
}
void controlRelay(int onOrOff){
  if ( onOrOff == RELAY_ON) {
    digitalWrite(RELAY_PIN, HIGH);  // Power ON
  }else{
    digitalWrite(RELAY_PIN, LOW);   // Power Off
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

void initWeigher(){
//  weigher.set_offset(41562);
  weigher.set_scale(WEiGHER_SCALE);  //  this value is obtained by calibrating the scale with known weights; see the README for details
  tareWeigher();
}
void tareWeigher(){
  //weigher.power_up();
  weigher.tare();
  //weigher.power_down(); 
}
double readWeigher(){
//  double sum0 = 0;
//  double sum1 = 0;
//  double each;
//  double each2;
//  double result = 0; 
//  for (int i = 0; i < WEIGHER_READ_TIMES; i++) { // read several times and take averages for accuracy.
//    //each = weigher.read();
//    // sum0 += each;
//    each2 = weigher.bias_read();
//    sum1 += each2;
//    //Serial.print("EACH:");Serial.println(each2);
//  }
//  result = sum1/WEIGHER_READ_TIMES;
//  return result;

  double result =0 ;
  //weigher.power_up(); // dont use power_up and power_down, the read value will frustrate.
  
  result = weigher.get_units(WEIGHER_READ_TIMES);
  if ( WEIGHT_ADJUST_ZERO && result >=-0.1 && result <=0.1 )
    result = 0;
  
  //weigher.power_down(); 
  return result;
  
}


void interruptRotaryEncoder ()  { // Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK
  rotary_up = (digitalRead(ROTARY_CLK_PIN) == digitalRead(ROTARY_DATA_PIN));
  rotary_turnDetected = true;
}
void interruptRotary2Encoder ()  { // Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK
  rotary_2_up = (digitalRead(ROTARY_2_CLK_PIN) == digitalRead(ROTARY_2_DATA_PIN));
  rotary_2_turnDetected = true;
}
void initRotaryEncoder(){
  pinMode (ROTARY_CLK_PIN,INPUT);  // setup the pins as inputs
  pinMode (ROTARY_DATA_PIN,INPUT);
  attachInterrupt (ROTARY_CLK_INTERRUPT,interruptRotaryEncoder,CHANGE);   // interrupt 0 is always connected to pin 2 on Arduino UNO
  rotary_count = 0;

  pinMode (ROTARY_2_CLK_PIN,INPUT);  // setup the pins as inputs
  pinMode (ROTARY_2_DATA_PIN,INPUT);
  attachInterrupt (ROTARY_2_CLK_INTERRUPT,interruptRotary2Encoder,CHANGE);   // interrupt 0 is always connected to pin 2 on Arduino UNO
  rotary_2_count = 0;  
}

void readRotaryEncoder(){
  if (rotary_turnDetected)  {        // do this only if rotation was detected
    if (rotary_up)
      rotary_count--;
    else
      rotary_count++;
    rotary_turnDetected = false;          // do NOT repeat IF loop until new rotation detected
    calcTargetWeigth();
    //Serial.println(rotary_count);
    //Serial.print("[c]");Serial.println(c);
    //Serial.print("[d]");Serial.println(d);
    
    //resetFinalWeight();
    
    printToSerialMsg();
  }

  if (rotary_2_turnDetected)  {        // do this only if rotation was detected
    if (rotary_2_up)
      rotary_2_count--;
    else
      rotary_2_count++;
    rotary_2_turnDetected = false;          // do NOT repeat IF loop until new rotation detected
    calcTargetWeigth();
    //Serial.println(rotary_count);
    //Serial.print("[c]");Serial.println(c);
    //Serial.print("[d]");Serial.println(d);
    
    
    //resetFinalWeight();
    
    printToSerialMsg();
  }
  
}
void calcTargetWeigth(){
  target_weight = BASE_TARGET_WEIGTH + (rotary_count/10.00) + (rotary_2_count/2.00);
}
void resetFinalWeight(){
  final_weight =0;
  displayLCD();
}
void printToSerialMsg(){
  if ( PRODUCTION==0){
    Serial.print("[TARGET_WEIGHT]");Serial.print(target_weight,1);Serial.print(" g ");Serial.print("[NOW_WEIGHT]");Serial.println(final_weight);
  }
}
void initLCD(){
  lcd.begin(20,4);
  lcd.backlight();
  lcd.home ();                   // go home
  lcd.print("Loading");
}
void displayLCD() {
  int i;
  memset(targetWeightStr, ' ', TARGET_WEIGHT_STR_SIZE);
  dtostrf(target_weight, 3, 1, targetWeightStr);  //format the display string (3 digits, 1 dp)

  String printFirstLine = String("TARGET: ") +  targetWeightStr + "g";
  for ( i = sizeof(printFirstLine); i <= DIGITS_PER_LINE; i++) // Clearing the previous message on LED.
    printFirstLine += " ";
  lcd.home();
  lcd.print(printFirstLine);


  memset(finalWeightStr, ' ', FINAL_WEIGHT_STR_SIZE);
  dtostrf(final_weight, 3, 1, finalWeightStr);  //format the display string (3 digits, 1 dp)

  String printSecondLine = String("NOW: ") + finalWeightStr + "g";
  for ( i = sizeof(printSecondLine); i < DIGITS_PER_LINE; i++)
    printSecondLine += " ";
  lcd.home();
  lcd.setCursor(0, 1);
  lcd.print(printSecondLine);
}

