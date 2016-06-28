#include <Timer.h>

Timer tcb;

const float PER_SEC =  1000.0;
const float PER_MIN =  PER_SEC * 60.0;
const float PER_HOUR = PER_MIN * 60.0;
const float PER_DAY =  PER_HOUR * 24.0;
float interval = PER_MIN * 10.0 ;

static unsigned long count = 0;
void writeToSerial(){
  Serial.println(++count); // 從0開始輸出，每次加1
}

void setup(void)
{
  Serial.begin(9600);
  Serial.print("Ready and Go! Every "); // 從0開始輸出，每次加1
  Serial.print(interval/PER_SEC);
  Serial.println(" s");
  tcb.every(interval, writeToSerial); // 每經過1000毫秒，就會呼叫writeToSerial
}

void loop(void)
{
  tcb.update();
}
         

