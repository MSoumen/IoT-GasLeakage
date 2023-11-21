void setup()
{
  
}
byte pin=10;
void loop()
{
  for(int i=0; i<256; i+=5){
    analogWrite(pin, i);
    delay(50);
  }
  for(int i=255; i>=0; i-=5){
    analogWrite(pin, i);
    delay(50);
  }
}
