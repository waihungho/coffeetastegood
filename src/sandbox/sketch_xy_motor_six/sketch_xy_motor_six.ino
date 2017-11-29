// IMPORTANT REMARK: (use 2: Remember to power on and then Open "Serial Monitor" to reset the count.)
// If the motor does not move, probably MOTOR_WAIT_INTERVAL set to low.

// On/Off Switch PIN:
#define SWITCH_PIN 13  
// Circuit:
// 5V <--->  SWITCH 
//              | <-------> PIN 13
//           RESISTOR <---> GND

// ------------------------------------------
//  Switch (BEGIN)
// ------------------------------------------
int switch_status;
#define SWITCH_ON 0       // Press down is ON.
#define SWITCH_OFF 1
// ------------------------------------------
//  Switch (END)
// ------------------------------------------

// ------------------------------------------
//  Relay (BEGIN)
// ------------------------------------------
#define RELAY_PIN 2 
#define RELAY_ON 1
#define RELAY_OFF 0
// ------------------------------------------
//  Relay (END)
// ------------------------------------------


// ------------------------------------------
//  Software (BEGIN)
// ------------------------------------------
int software_status;
#define STATUS_INIT 1
#define STATUS_MOTOR_MOVING 2
// ------------------------------------------
//  Software (BEGIN)
// ------------------------------------------




#define MOTOR_X_DIRECTION_PIN 8
#define MOTOR_X_MOVE_PIN 9

#define MOTOR_Y_DIRECTION_PIN 10  //CW+ 
#define MOTOR_Y_MOVE_PIN 11       //CLK+

#define MOTOR_X_MOVE_TOWARDS LOW  // Motor X: 地台移動,軌道固定.  // For this motor: move to the edge means move towards to motor
#define MOTOR_X_MOVE_AWAYS HIGH  
#define MOTOR_X_MOVE_STOP LOW

#define MOTOR_Y_MOVE_TOWARDS HIGH   // Motor Y: 地台固定,軌道移動. // LOW: run away from motor; HIGH: move towards to motor
#define MOTOR_Y_MOVE_AWAYS LOW                                    // For this motor: move to the edge means move away from motor
#define MOTOR_Y_MOVE_STOP LOW

#define MOTOR_MAX_STEPS 83500

//#define MOTOR_CENTER_TO_EDGE  10000
//#define MOTOR_CENTER_TO_EDGE_START  MOTOR_CENTER_TO_EDGE/2
//#define MOTOR_CENTER_TO_EDGE_ADJ  MOTOR_CENTER_TO_EDGE


#define MOTOR_STEPS_INTERVAL 5  // Lesser time, motor move faster [value 3: is the min]
//#define MOTOR_WAIT_INTERVAL 30 // value 30: is the min
#define MOTOR_WAIT_INTERVAL 30 // value 30: is the min


int motorMovingStatus=0;
double motorStepsCount=0;

#define MOTOR_ADJUST_MODE 0    // 0: NO ADJUST MODE; 1: ADJUST to the edge; 2: ADJUST TO the center
                               // Step --> 1 ---> 2 (use 2: Remeber to power on and then Open "Serial Monitor" to reset the count.)
                               // 3 only move X, 4 only move Y

//double MAX_COUNT = 83500; // It's constant value for all the delay.



void initMotor(){
  pinMode(MOTOR_X_DIRECTION_PIN, OUTPUT); 
  pinMode(MOTOR_X_MOVE_PIN, OUTPUT); 

  pinMode(MOTOR_Y_DIRECTION_PIN, OUTPUT); 
  pinMode(MOTOR_Y_MOVE_PIN, OUTPUT); 
  
  digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS); 
  digitalWrite(MOTOR_X_MOVE_PIN, LOW); 

  digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_AWAYS); 
  digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
}

#define MOTOR_CENTER_TO_RIGHT 1
#define MOTOR_RIGHT_TO_BOTTOM 2
#define MOTOR_BOTTOM_TO_LEFT  3
#define MOTOR_LEFT_TO_TOP     4
#define MOTOR_TOP_TO_RIGHT     5
#define MOTOR_RIGHT_TO_CENTER 6




//      -
//    /   \
//    |   |
//    \ - /
//      3
//    2   4
//   1     5
//    8   6 
//      7

//          Y (motor)
//          |
//  X ----------------
//          |
//          |

//    Y         X
//1:   Towards    None
//2:   Towards    Away
//3:   None       Away
//4:   Away       Away
//5:   Away       None
//6:   Away       Towards
//7:   None       Towards
//8:   Towards    Towards

//      3
//    2   4
//   1     5
//    8   6 
//      7

//        4
//      3    5
//    2       
//  1/11  C   6
//   10 
//    9      7
//        8
//      -
//    /   \
//    |   |
//    \ - /
//          Y (motor)
//          |
//  X ----------------
//          |
//          |        
//        X         Y           distance
//  1:  Towards     None         full
//  2:  None        Towards      half
//  3:  Away        Towards      full(adj)
//  4:  Away       None          
//  5:  Away       Away         full(adj)
//  6:   None       Away
//  7:   Towards       Away     full(adj)
//  8:   Towards       None
//  9:   Towards    Towards     full(adj)
//  10:   None     Towards      half
//  11:  Away       None        full
//


#define PREWETTING_INTERVAL 5  // seconds when mode == 1 is done

//#define MOVE_MODE 1
//const float MOTOR_CENTER_TO_EDGE[MOVE_MODE] = {8000};
//const float MOTOR_CENTER_TO_EDGE_START[MOVE_MODE] = {4000};
//const float MOTOR_CENTER_TO_EDGE_INIT[MOVE_MODE] = {12000};
//const float MOTOR_CENTER_TO_EDGE_ADJ[MOVE_MODE] = {8000};
//#define MOVE_STEPS 11  
//const int MAX_MOVE_STEPS[MOVE_MODE] = {11};
//const boolean enabled_x[MOVE_MODE][MOVE_STEPS] = {{true, false, true, true, true, false, true, true, true, false, true} };
//const boolean enabled_y[MOVE_MODE][MOVE_STEPS] = {{false,true, true, false, true, true, true, false, true, true, false} };
//const boolean direction_x[MOVE_MODE][MOVE_STEPS] = {
//                        {MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_STOP,    MOTOR_X_MOVE_AWAYS,   MOTOR_X_MOVE_AWAYS,   MOTOR_X_MOVE_AWAYS, 
//                           MOTOR_X_MOVE_STOP,    MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_STOP,
//                           MOTOR_X_MOVE_AWAYS}     
//                        };
//const boolean direction_y[MOVE_MODE][MOVE_STEPS] = {
//                        {MOTOR_Y_MOVE_STOP   , MOTOR_Y_MOVE_TOWARDS, MOTOR_Y_MOVE_TOWARDS, MOTOR_Y_MOVE_STOP ,   MOTOR_Y_MOVE_AWAYS,
//                           MOTOR_Y_MOVE_AWAYS  , MOTOR_Y_MOVE_AWAYS,   MOTOR_Y_MOVE_STOP   , MOTOR_Y_MOVE_TOWARDS, MOTOR_Y_MOVE_TOWARDS,
//                           MOTOR_Y_MOVE_STOP}                                                   
//                        };



#define MOVE_MODE 2
const float MOTOR_CENTER_TO_EDGE[MOVE_MODE] = {5000,8000};
const float MOTOR_CENTER_TO_EDGE_START[MOVE_MODE] = {2500, 4000};
const float MOTOR_CENTER_TO_EDGE_INIT[MOVE_MODE] = {7500,12000};
const float MOTOR_CENTER_TO_EDGE_ADJ[MOVE_MODE] = {5000,8000};
#define MOVE_STEPS 11  
const int MAX_MOVE_STEPS[MOVE_MODE] = {11, 11};
const boolean enabled_x[MOVE_MODE][MOVE_STEPS] = {{true, false, true, true, true, false, true, true, true, false, true}, {true, false, true, true, true, false, true, true, true, false, true} };
const boolean enabled_y[MOVE_MODE][MOVE_STEPS] = {{false,true, true, false, true, true, true, false, true, true, false}, {false,true, true, false, true, true, true, false, true, true, false} };
const boolean direction_x[MOVE_MODE][MOVE_STEPS] = {
   {MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_STOP,    MOTOR_X_MOVE_AWAYS,   MOTOR_X_MOVE_AWAYS,   MOTOR_X_MOVE_AWAYS, 
                           MOTOR_X_MOVE_STOP,    MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_STOP,
                           MOTOR_X_MOVE_AWAYS}     ,
                        {MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_STOP,    MOTOR_X_MOVE_AWAYS,   MOTOR_X_MOVE_AWAYS,   MOTOR_X_MOVE_AWAYS, 
                           MOTOR_X_MOVE_STOP,    MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_TOWARDS, MOTOR_X_MOVE_STOP,
                           MOTOR_X_MOVE_AWAYS}     
                        };
const boolean direction_y[MOVE_MODE][MOVE_STEPS] = {
   {MOTOR_Y_MOVE_STOP   , MOTOR_Y_MOVE_TOWARDS, MOTOR_Y_MOVE_TOWARDS, MOTOR_Y_MOVE_STOP ,   MOTOR_Y_MOVE_AWAYS,
                           MOTOR_Y_MOVE_AWAYS  , MOTOR_Y_MOVE_AWAYS,   MOTOR_Y_MOVE_STOP   , MOTOR_Y_MOVE_TOWARDS, MOTOR_Y_MOVE_TOWARDS,
                           MOTOR_Y_MOVE_STOP} ,
                        {MOTOR_Y_MOVE_STOP   , MOTOR_Y_MOVE_TOWARDS, MOTOR_Y_MOVE_TOWARDS, MOTOR_Y_MOVE_STOP ,   MOTOR_Y_MOVE_AWAYS,
                           MOTOR_Y_MOVE_AWAYS  , MOTOR_Y_MOVE_AWAYS,   MOTOR_Y_MOVE_STOP   , MOTOR_Y_MOVE_TOWARDS, MOTOR_Y_MOVE_TOWARDS,
                           MOTOR_Y_MOVE_STOP}                                                   
                        };


#define ROUTE_END_INTERVAL 0  
                        
// return 0: motor is moving; 1: motor reaches the target.
int motorMove(int mode, int movement){
  int motorStatus =0 ;
  motorStepsCount++;
  if (
    ( ( movement==1 or movement==9 ) and motorStepsCount>MOTOR_CENTER_TO_EDGE_START[mode] ) or  
    ( ( movement==0 or movement==10 ) and motorStepsCount>MOTOR_CENTER_TO_EDGE_INIT[mode] ) or 
    ( ( movement==3 or movement==5 or movement==7 ) and motorStepsCount>MOTOR_CENTER_TO_EDGE[mode] ) or 
    ( ( movement==2 or movement==4 or movement==6 or movement==8  ) and motorStepsCount>MOTOR_CENTER_TO_EDGE_ADJ[mode] ) 
  ) {  
    motorStatus = 1;
    motorStepsCount = 0;
    delay(ROUTE_END_INTERVAL);
  }else {
   
    if ( enabled_x[mode][movement] ){                          
      digitalWrite(MOTOR_X_DIRECTION_PIN, direction_x[mode][movement]);
      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
    }
    if ( enabled_y[mode][movement] ){
      digitalWrite(MOTOR_Y_DIRECTION_PIN, direction_y[mode][movement]);
      digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
    } 
    delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
    if ( enabled_x[mode][movement] ){      
      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
    }
    if ( enabled_y[mode][movement] ){
      digitalWrite(MOTOR_Y_MOVE_PIN, LOW);       
    }


//
//    if (movement == 1 ) {
//      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_TOWARDS);
//      //digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_AWAYS);
//      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      //digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//     // digitalWrite(MOTOR_Y_MOVE_PIN, LOW);         
//
//    } else if (movement == 2 ) {
//      //digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS);
//      digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_TOWARDS);
//     // digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      //digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, LOW);      
//      
//    } else if ( movement == 3 ){      
//      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS);
//      digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_TOWARDS);
//      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, LOW);       
//    } else if ( movement == 4 ){ 
//      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS);
//      //digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_TOWARDS);
//      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      //digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//      //digitalWrite(MOTOR_Y_MOVE_PIN, LOW);        
//    } else if ( movement == 5 ){ 
//      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS);
//      digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_AWAYS);
//      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
//    } else if ( movement == 6 ){ 
//      //digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS);
//      digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_AWAYS);
//      //digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      //digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
//    } else if ( movement == 7 ){ 
//      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_TOWARDS);
//      digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_AWAYS);
//      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
//    } else if ( movement == 8 ){
//      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_TOWARDS);
//      //digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_AWAYS);
//      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      //digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//      //digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
//    } else if ( movement == 9 ){
//      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_TOWARDS);
//      digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_TOWARDS);
//      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
//    } else if ( movement == 10 ){
//      //digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_TOWARDS);
//      digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_TOWARDS);
//      //digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      //digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//      digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
//    } else if ( movement == 11 ){
//      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS);
//      //digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_TOWARDS);
//      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
//      //digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
//      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
//      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
//      //digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
//    } else {
//      Serial.println("ERROR: Wrong movement value.");
//    }
    delayMicroseconds(MOTOR_WAIT_INTERVAL); 
  }
  return motorStatus;
}

// target 1: move to the edge. 2: Motor(Y) move to CENTER, Motor(X) move to CENTER
void adjustMotor(int target){
//                              |
//    (TOP)                     |
//  WATER    (RIGHT)   -----    |  - - - - - MOTOR (X)  反轉 (因為是地台固定,軌道移動,所以跟MOTOR(Y)是反轉)
//    (BOTTM)                   |
//                          MOTOR(Y) (地台移動,軌道固定)

  // Motor(Y), Motor(X) 地台 move to the edge first (AWAY from MOTOR)
  if ( target ==1 ) {
    while (1==1){ // stop by power off the motor!!!
      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS);
      digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_AWAYS);
      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
      digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
      digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
      delayMicroseconds(MOTOR_WAIT_INTERVAL); 
    }
  } else if (target == 2){
    double motorCount=0;
    double MOTOR_Y_CENTER_COUNT = 50000;  // MOTOR_MAX_STEPS
    while ( motorCount <= MOTOR_Y_CENTER_COUNT ){
      motorCount++;
      digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_TOWARDS);
      digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
      digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
      delayMicroseconds(MOTOR_WAIT_INTERVAL);      
    }
    motorCount=0;
    double MOTOR_X_CENTER_COUNT = 20000; 
    while ( motorCount <= MOTOR_X_CENTER_COUNT ){
      motorCount++;
      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_TOWARDS);
      digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
      delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
      digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
      delayMicroseconds(MOTOR_WAIT_INTERVAL);      
    }


   } else if (target ==3 ) {
      while (1==1){ // stop by power off the motor!!!
        digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS);

        digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 

        delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
        digitalWrite(MOTOR_X_MOVE_PIN, LOW); 

        delayMicroseconds(MOTOR_WAIT_INTERVAL); 
      }
    }else if (target ==4 ) {
      while (1==1){ // stop by power off the motor!!!

        digitalWrite(MOTOR_Y_DIRECTION_PIN, MOTOR_Y_MOVE_AWAYS);

        digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
        delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster

        digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
        delayMicroseconds(MOTOR_WAIT_INTERVAL); 
      } 

    
  } else {
    Serial.println("ERROR: invalid target");
  }
  Serial.println("DONE Adjustment");
  
}


void setup() { 
  Serial.begin(9600);
  initSwitch();
  initRelay();
  
  initMotor();

  if ( MOTOR_ADJUST_MODE==1){
    adjustMotor(1);
  } else if ( MOTOR_ADJUST_MODE==2){
    adjustMotor(2);   // Remeber to power on and then Open "Serial Monitor" to reset the count.
  } else if ( MOTOR_ADJUST_MODE==3){
    adjustMotor(3);
  }else if ( MOTOR_ADJUST_MODE==4){
    adjustMotor(4);  
   
  }


  software_status = STATUS_INIT;

} 

//    #define MOTOR_CENTER_TO_RIGHT 1
//    #define MOTOR_RIGHT_TO_BOTTOM 2
//    #define MOTOR_BOTTOM_TO_LEFT  3
//    #define MOTOR_LEFT_TO_TOP     4
//    #define MOTOR_TOP_TO_RIGHT     5
//    #define MOTOR_RIGHT_TO_CENTER 6
void logMotorStatus(int mStatus){
  switch (mStatus){
    case MOTOR_CENTER_TO_RIGHT:
      Serial.println("Center to Right");
      break;
    case MOTOR_RIGHT_TO_BOTTOM:
      Serial.println("Right to Bottom");
      break;
    case MOTOR_BOTTOM_TO_LEFT:
      Serial.println("Bottom to Left");
      break;
    case MOTOR_LEFT_TO_TOP:
      Serial.println("Left to Top");
      break;
    case MOTOR_TOP_TO_RIGHT:
      Serial.println("Top to Right");
      break;
    case MOTOR_RIGHT_TO_CENTER:
      Serial.println("Right to Center");
      break;
    default:
      Serial.println("invalid Motor Status");
      break;
  }


}

int currentMode = 0;
void loop(){

  manualMove();

  if ( MOTOR_ADJUST_MODE == 0 ){

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
    
    if (software_status == STATUS_INIT && switch_status == SWITCH_ON  && changeStatus) {
      software_status = STATUS_MOTOR_MOVING;
      controlRelay(RELAY_ON);
      motorMovingStatus =0;
      currentMode=0;
      //logMotorStatus(motorMovingStatus);       
    }

 
    if ( software_status == STATUS_MOTOR_MOVING ) {
      if ( motorMovingStatus > MOVE_STEPS-1 and currentMode == MOVE_MODE-1) {
        Serial.println("ALL DONE");
        software_status = STATUS_INIT;
        controlRelay(RELAY_OFF);
      } else {
        // if ( motorMovingStatus > MOVE_STEPS-1 and currentMode == 0) {
        if ( motorMovingStatus > MAX_MOVE_STEPS[currentMode]-1 and currentMode < (MOVE_MODE-1)) {
          
          currentMode++;
          motorMovingStatus=0;
          controlRelay(RELAY_OFF);
          delay(PREWETTING_INTERVAL*1000);
          controlRelay(RELAY_ON);
        }
        if ( motorMove(currentMode,motorMovingStatus) == 1 ) { // ==1 : means movement done.
          motorMovingStatus ++;
          //delay(10000);
          logMotorStatus(motorMovingStatus);
          //delay(2000);
        }
      }
    }

  }
}
  
  
int thisStatus = -1; // 1 means move away from motor; -1 means move towards from motor.
void tryLoop(){
  //
  if ( 0==1 ) {
    digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS);       // LOW: run away from motor; HIGH: move towards from motor
    digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
    delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster  // 3: is the min
    digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
    delayMicroseconds(MOTOR_WAIT_INTERVAL);  // 30: is the min
  } else { 
    motorStepsCount++;
    // digitalWrite(8, LOW);       // LOW: run away from motor; HIGH: move towards from motor
    if ( motorStepsCount>MOTOR_MAX_STEPS ) {  // 84000 : end to end  
      // 83500 : for  
//      digitalWrite(9, HIGH); 
//      delayMicroseconds(5);     // Lesser time, motor faster
//      digitalWrite(9, LOW); 
//      delayMicroseconds(100); 
      
      thisStatus = thisStatus * -1;
      motorStepsCount=0;
    }
    if (thisStatus==1){
      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_AWAYS);
    } else {
      digitalWrite(MOTOR_X_DIRECTION_PIN, MOTOR_X_MOVE_TOWARDS);
    }
    digitalWrite(9, HIGH); 
    delayMicroseconds(MOTOR_STEPS_INTERVAL);     // Lesser time, motor faster
    digitalWrite(9, LOW); 
    delayMicroseconds(MOTOR_WAIT_INTERVAL); 
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

void manualMove(){
    //#define MOTOR_MAX_STEPS 83500
  //#define MOTOR_CENTER_TO_EDGE  15000
  //X10:  move towards motor (1 : motor X 1000)
  //X-10: move aways from motor
  //Y10:
  if ( Serial.available()){
    Serial.println("X10: X axis platform move towards motor. (10000)");
    Serial.println("X-10: X axis platform move away motor. (10000)");
    
    String in= Serial.readString();// read the incoming data as string
    in.trim();
    String firstChar = in.substring(0,1);
    firstChar.toUpperCase();
    String valueChar = in.substring(1,in.length());
    float value = valueChar.toFloat() * 1000;
    Serial.println(String("First:") + firstChar);
    Serial.println(String("Value:") + value);
    int moveDirection = 1;  // 1: means move away from motor, 0: move towards from motor
    if ( value < 0 ) {
      moveDirection=0;
      value = value*-1;
    }
    if ( String("X").equals(firstChar) ){
      int steps = 0;
      while (steps<=value){ // stop by power off the motor!!!
        steps++;
        if ( moveDirection == 1 )
          digitalWrite(MOTOR_X_DIRECTION_PIN, HIGH);
        else
          digitalWrite(MOTOR_X_DIRECTION_PIN, LOW);
        digitalWrite(MOTOR_X_MOVE_PIN, HIGH); 
        delayMicroseconds(MOTOR_STEPS_INTERVAL);    
        digitalWrite(MOTOR_X_MOVE_PIN, LOW); 
        delayMicroseconds(MOTOR_WAIT_INTERVAL); 
      }
    } else {
      int steps = 0;
      while (steps<=value){ // stop by power off the motor!!!
        steps++;
        if ( moveDirection == 1 )
          digitalWrite(MOTOR_Y_DIRECTION_PIN, HIGH);
        else
          digitalWrite(MOTOR_Y_DIRECTION_PIN, LOW);      
        
        digitalWrite(MOTOR_Y_MOVE_PIN, HIGH); 
        delayMicroseconds(MOTOR_STEPS_INTERVAL);     
        digitalWrite(MOTOR_Y_MOVE_PIN, LOW); 
        delayMicroseconds(MOTOR_WAIT_INTERVAL); 
      }
    }
  }
}


//void loop() { 
//  digitalWrite(9, HIGH); 
//  delayMicroseconds(100); 
//  digitalWrite(9, LOW); 
//  delayMicroseconds(100); 
//  Distance = Distance + 1; // record this step // Check to see if we are at the end of our move 
//  // two rotation for 1/8 bridge and 1 rotation for 1/6 bridge (for this code) 
//  if (Distance == 32000) { // We are! Reverse direction (invert DIR signal) 
//    if (digitalRead(8) == LOW) { 
//      digitalWrite(8, HIGH); 
//    } else { 
//      digitalWrite(8, LOW); 
//    } // Reset our distance back to zero since we're // starting a new move 
//    Distance = 0; // Now pause for half a second delay(500); 
//  } 
//}



