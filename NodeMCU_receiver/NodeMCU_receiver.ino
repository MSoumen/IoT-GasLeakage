void setup() {
  Serial.begin(9600);
  pinMode(BUILTIN_LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //checking for serial communication
  if(Serial.available()){
    Serial.print(Serial.read());
  }
  else{
    digitalWrite(BUILTIN_LED, HIGH);
    delay(500);
    digitalWrite(BUILTIN_LED, LOW);
    delay(500);
  }

}
