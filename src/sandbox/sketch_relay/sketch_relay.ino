int ledPin =  2;    // Relay connected to digital pin 2

void setup()   {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  Serial.println("ON");
  digitalWrite(ledPin, HIGH);  // Power ON
  delay(10000);
  Serial.println("OFF");
  digitalWrite(ledPin, LOW);   // Power Off
  delay(10000);
}
