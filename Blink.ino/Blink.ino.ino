void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("LED On!");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  Serial.println("LED Off!");
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}