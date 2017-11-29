#define BUTTON_PANEL_1_PIN A0
#define BUTTON_PANEL_2_PIN A1
#define BUTTON_PANEL_3_PIN A2
#define BUTTON_PANEL_4_PIN A3
//#define BUTTON_PANEL_5_PIN A4
//#define BUTTON_PANEL_6_PIN A5
//#define BUTTON_PANEL_7_PIN A6
//#define BUTTON_PANEL_8_PIN A7

boolean buttonOn1 = false; // true: button clicked
boolean buttonOn2 = false;
boolean buttonOn3 = false;
boolean buttonOn4 = false;
boolean buttonOn5 = false;
boolean buttonOn6 = false;
boolean buttonOn7 = false;
boolean buttonOn8 = false;

void initButtonPanel(){
  pinMode(BUTTON_PANEL_1_PIN, INPUT);     
  pinMode(BUTTON_PANEL_2_PIN, INPUT);     
  pinMode(BUTTON_PANEL_3_PIN, INPUT);     
  pinMode(BUTTON_PANEL_4_PIN, INPUT);   
//  pinMode(BUTTON_PANEL_5_PIN, INPUT);     
//  pinMode(BUTTON_PANEL_6_PIN, INPUT);      
//  pinMode(BUTTON_PANEL_7_PIN, INPUT);      
//  pinMode(BUTTON_PANEL_8_PIN, INPUT);     
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
  if ( analogRead(BUTTON_PANEL_1_PIN) != 0)
    buttonOn1=true;
  if ( analogRead(BUTTON_PANEL_2_PIN) != 0)
    buttonOn2=true;
  if ( analogRead(BUTTON_PANEL_3_PIN) != 0)
    buttonOn3=true;
  if ( analogRead(BUTTON_PANEL_4_PIN) != 0)
    buttonOn4=true;
//  if ( analogRead(BUTTON_PANEL_5_PIN) != 0)
//    buttonOn5=true;
//  if ( analogRead(BUTTON_PANEL_6_PIN) != 0)
//    buttonOn6=true;
//  if ( analogRead(BUTTON_PANEL_7_PIN) != 0)
//    buttonOn7=true;
//  if ( analogRead(BUTTON_PANEL_8_PIN) != 0)
//    buttonOn8=true;           
}
void loop()
{
  readButtonPanel();
  if (buttonOn1)
    Serial.println("Button 1 clicked");
  if (buttonOn2)
    Serial.println("Button 2 clicked");
  if (buttonOn3)
    Serial.println("Button 3 clicked");
  if (buttonOn4)
    Serial.println("Button 4 clicked");
  if (buttonOn5)
    Serial.println("Button 5 clicked");
  if (buttonOn6)
    Serial.println("Button 6 clicked");
  if (buttonOn7)
    Serial.println("Button 7 clicked");
  if (buttonOn8)
    Serial.println("Button 8 clicked");
        
  delay(100);
}


void setup()
{
  Serial.begin(9600);

  initButtonPanel();
}
