int ledPin =  4;    // Relay connected to digital pin 2

void setup()   {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Power ON
}

void loop()
{
  Serial.println("ON");
  digitalWrite(ledPin, LOW);  // Power ON
  delay(10000);
  Serial.println("OFF");
  digitalWrite(ledPin, HIGH);   // Power Off
  delay(10000);
}
