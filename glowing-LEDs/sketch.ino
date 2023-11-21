byte pinStart=12;
byte pinEnd = 6;
void setup()
{
  for(int i=pinStart; i>=pinEnd; i--){
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  for(int i=pinStart; i>=pinEnd; i--){
    glowLED(i);
  }
  for(int i=pinEnd+1; i<pinStart; i++){
    glowLED(i);
  }
}

void glowLED(int pin){
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW);
  delay(200);
}
