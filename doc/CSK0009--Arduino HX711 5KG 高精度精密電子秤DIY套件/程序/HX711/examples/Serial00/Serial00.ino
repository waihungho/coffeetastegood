#include <HX711.h>
HX711 hx(9, 10, 128, 0.00127551);
void setup() {
  Serial.begin(9600);
  hx.set_offset(36300);

}
void loop() {
  delay(500);
  double sum0 = 0;
  double sum1 = 0;
  for (int i = 0; i < 10; i++) {
    sum0 += hx.read();
    sum1 += hx.bias_read();
  }
  Serial.print(sum0/10);
  Serial.print(" ");
  Serial.println(sum1/10);
}
