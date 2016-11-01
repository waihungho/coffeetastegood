#include <IRremote.h>


IRsend irsend; 
void setup() {  Serial.begin(9600); } 

void loop() {    
  for (int i = 0; i < 50; i++) {                                        
     irsend.sendSony(0xa90, 12); // Sony TV power code      delay(4000田);   
     }  
}


// Infraed Red Receiver
// LEFT PIN: GND
// MIDDLE PIN: 5V
// RIGHT PIN: PIN 2

//int RECV_PIN = 2; // 使用數位腳位2接收紅外線訊號
//IRrecv irrecv(RECV_PIN); // 初始化紅外線訊號輸入
//decode_results results; // 儲存訊號的結構
//
//void setup()
//{
//  Serial.begin(9600);
//  irrecv.blink13(true); // 設為true的話，當收到訊號時，腳位13的LED便會閃爍
//  irrecv.enableIRIn(); // 啟動接收
//}
//
//void loop() {
//  if (irrecv.decode(&results)) { // 接收紅外線訊號並解碼
//    Serial.print("results value is "); // 輸出解碼後的資料
//    Serial.print(results.value, HEX);
//    Serial.print(", bits is ");
//    Serial.print(results.bits);
//    Serial.print(", decode_type is ");
//    Serial.println(results.decode_type);
//    irrecv.resume(); // 準備接收下一個訊號
//  }
//   // 70B6FC0A, FA36E9A0 -> ON/OFF
//
//   // A90 : Sony TV ON/OFF
//}




