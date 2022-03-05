// Light up an LED whenever noise is detected

int sensorPin = 7;
int ledPin = 13;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (digitalRead(sensorPin) == HIGH) 
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);
}
