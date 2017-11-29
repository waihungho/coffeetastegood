
// PH Meter PIN: (Logo_PHsensor v1.1)
//  PH Meter                Arduino
//    V+                      5V
//    G                       GND
//    G                       N/A
//    Po                      A0
//    Do (temperature 1)      N/A
//    To (temperature 2)      N/A
#define PH_SENSOR_PIN A0   

// PH Meter Configuration (BEGIN)
#define PH_METER_READ_TIMES 10    // read from PH meter 10 times, and take the average value.
#define PH_METER_REMOVE_MAX_MIN 2 // remove the max[the first 2], min value.
#define PH_METER_SLOPE    -5.70   // m: from formula y=mx+c
#define PH_METER_CONSTANT 21.34   // c: from formula y=mx+c
#define PH_METER_DELAY_EVERY_READ 10  // ms : delay for every read from PH meter.
int pHBuffer[PH_METER_READ_TIMES]; //just buffer value
float phValue;
// PH Meter Configuration (END)


void setup() {
 Serial.begin(9600);
 initPHMeter();
}

void loop() {
  readFromPHMeter();
 
 delay(500);
}

void initPHMeter(){
  // Nothings to do.
}
void readFromPHMeter(){
  phValue = 0;
  int temp=0;
  for(int i=0;i<PH_METER_READ_TIMES;i++) { 
    pHBuffer[i]=analogRead(PH_SENSOR_PIN);
    delay(PH_METER_DELAY_EVERY_READ);
  }
  for(int i=0;i<(PH_METER_READ_TIMES-1);i++) {  // Sorting
    for(int j=i+1;j<PH_METER_READ_TIMES;j++) {
      if(pHBuffer[i]>pHBuffer[j]) {
        temp=pHBuffer[i];
        pHBuffer[i]=pHBuffer[j];
        pHBuffer[j]=temp;
      }
    }
  }
  unsigned long int avgValue=0;
  for(int i=PH_METER_REMOVE_MAX_MIN;i<(PH_METER_READ_TIMES-PH_METER_REMOVE_MAX_MIN);i++)
    avgValue+=pHBuffer[i];
  float pHVol=(float)avgValue*5.0/1024/(PH_METER_READ_TIMES - PH_METER_REMOVE_MAX_MIN *2); // 5.0: 5V from Arduino, 1024: 5V in 1024 steps, (PH_METER_READ_TIMES - PH_METER_REMOVE_MAX_MIN *2): take average value.
  //The AnalogRead function in Ardunio which is used by your sensor reads values from 0 - 5V. It divides the values between 0 and 5V in 1024 steps. So it returns a value between 0 and 1023. That is why it is multiplied by 5. It is easier to understand if the calculation is done in reverse order. Example:
  //AnalogRead returns 512, so that is on 1024 / 512 = 0,5th part of it's range. Multiply that by 5.0 to get the actual voltage. 0.5 * 5.0 = 2.5; It is then divided by 6 to get the average.
  //I would also change the order of the calculation. The comments say that it calculates the average, but it doesn't it just adds the values. It does divide it by 6 eventually so that does not cause the error, but for readability it is generally good practice to let your code do what the comments say
  
  phValue = PH_METER_SLOPE * pHVol + PH_METER_CONSTANT; // Linear function : y=mx + c
    
  // 1. Calculate m : Given pHValue, find out the corresponding Voltage [Y: pHValue, X: Voltage : m = (Y2 - Y1) / (X2 - X1)]
  // 2. Calculate c : Given pHValue, Voltage and Slope(m), calculate c. [Y: pHValue, X: Voltage : y=mx + c]
  // Reference: http://scidle.com/how-to-use-a-ph-sensor-with-arduino/
  
  Serial.println(String("[AVERAGE_VALUE]") + avgValue/(PH_METER_READ_TIMES - PH_METER_REMOVE_MAX_MIN *2) + "[pHVol]" + pHVol + "[phValue]" + phValue);

}

