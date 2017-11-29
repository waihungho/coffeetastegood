#include "HX711.h"   // https://github.com/bogde/HX711

// HX711.DOUT  - pin #A1
// HX711.PD_SCK - pin #A0
//HX711 scale(A1, A0);   // parameter "gain" is ommited; the default value 128 is used by the library

//  WEIGHTER    Keyes 234
//  E+          RED
//  E-          BLACK
//  A-          WHITE
//  A+          GREEN

#define WEIGHER_SCK_PIN 9
#define WEIGHER_DOUT_PIN 10 

HX711 weigher(WEIGHER_SCK_PIN, WEIGHER_DOUT_PIN);   // parameter "gain" is ommited; the default value 128 is used by the library
#define WEiGHER_SCALE 395.05  // Different medal , different scale. (usually decrease this value if the weight is under-estimated.
                               // 1588.05 : small grey scale.
                               // 395.05 : 
const unsigned int WEIGHER_READ_TIMES  = 5;


void setup() {
  Serial.begin(9600);
  Serial.println(" 1HX711 Demo");

//  Serial.println("Before setting up the scale:");
//  Serial.print("read: \t\t");
//  Serial.println(scale.read());     // print a raw reading from the ADC
//
//  Serial.print("read average: \t\t");
//  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC
//
//  Serial.print("get value: \t\t");
//  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)
//
//  Serial.print("get units: \t\t");
//  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided 
//            // by the SCALE parameter (not set yet)  

  initWeigher();
//  weigher.set_scale(1587.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
//  weigher.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

//  Serial.print("read: \t\t");
//  Serial.println(scale.read());                 // print a raw reading from the ADC
//
//  Serial.print("read average: \t\t");
//  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
//
//  Serial.print("get value: \t\t");
//  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()
//
//  Serial.print("get units: \t\t");
//  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
//            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void initWeigher(){
  weigher.set_scale(WEiGHER_SCALE);  //  this value is obtained by calibrating the scale with known weights; see the README for details
  weigher.tare();
}


double readWeigher(){
  double result =0 ;
//  weigher.power_up();
  
  result = weigher.get_units(WEIGHER_READ_TIMES);
//  if ( result < 0 )
//    result = 0;
//  
//  weigher.power_down(); 
  return result;
}

void loop() {
//  Serial.print("one reading:\t");
//  Serial.print(weigher.get_units(),4);
  Serial.print("\t| average:\t");
  Serial.println(readWeigher(), 1);

  //weigher.power_down();             // put the ADC in sleep mode
  delay(100);
  //weigher.power_up();
}
