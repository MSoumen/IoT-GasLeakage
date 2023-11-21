byte pinStart=11;
byte pinEnd = 9;
void setup()
{
  for(int i=pinStart; i>=pinEnd; i--){
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  for(int i=pinStart; i>=pinEnd; i--){
    // glowLEDanalog(i);
    glowLED(i);
    // delay(1000);
  }
  // delay(1000);
  for(int i=pinEnd+1; i<pinStart; i++){
    // glowLEDanalog(i);
    glowLED(i);
    // delay(1000);
  }
}

void glowLEDanalog(int pin){
  analogWrite(pin, 0);
  delay(500);
  // analogWrite(pin, 50);
  // delay(550);
  // analogWrite(pin, 100);
  // delay(550);
  analogWrite(pin, 150);
  delay(500);
  // analogWrite(pin, 200);
  // delay(550);
  analogWrite(pin, 255);
  delay(500);
}
void glowLED(int pin){
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW);
  delay(200);
}
