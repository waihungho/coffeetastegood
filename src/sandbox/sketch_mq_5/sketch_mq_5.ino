
int AOpin = A3;
int DOpin = 8;

void setup() {
  pinMode(AOpin, INPUT);
  pinMode(DOpin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(AOpin);
  //int digitalSensor = !(digitalRead(DOpin));

  Serial.print("Detected Value = ");
  Serial.print(analogSensor);
  Serial.print("\t");
  //Serial.print("Alarm = ");
  //Serial.print(digitalSensor);
  Serial.println();

  delay(1000);
}
