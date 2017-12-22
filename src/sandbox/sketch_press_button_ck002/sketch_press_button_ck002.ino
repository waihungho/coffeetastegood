int val = 0;       // variable to store the read value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Ready");
  pinMode(12, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(12);     // read the input pin
  Serial.println(val);
  delay(1000);
}
