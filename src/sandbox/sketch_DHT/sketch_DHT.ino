#define DHT_PIN 2 


// DHT.read22(DHT_PIN) for DHT22
// DHT.read11for DHT11

#define SERIAL_BAUD_RATE 9600

// DHT 溫度和濕度 Configuration (BEGIN)
#include <dht.h>   
#define DHT_INIT_WAIT 1000 
dht DHT;   
// DHT Configuration (BEGIN)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BAUD_RATE);

    initDHT(); // initialize DHT
}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read22(DHT_PIN);   //去library裡面找DHT.read11 
 Serial.print("Humidity = ");   
    Serial.print(DHT.humidity);   
    Serial.print("% ");   
    Serial.print("temperature = ");   
    Serial.print(DHT.temperature);   
    Serial.println("C ");   
    delay(2000);
 
}


void initDHT(){
  delay(DHT_INIT_WAIT);  //Wait rest of 1000ms recommended delay before accessing DHT sensor   
}
