int ledPin =  2;    // Relay connected to digital pin 2

void setup()   {
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH);  // Power ON
  delay(5000);
  digitalWrite(ledPin, LOW);   // Power Off
  delay(5000);
}
