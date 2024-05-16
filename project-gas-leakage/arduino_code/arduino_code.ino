#define GAS_PIN  A0
#define RELAY_PIN 5

void setup(){
  Serial.begin(9600);
  
  pinMode(GAS_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  delay(5000);
}

void loop(){
  int gas_value = analogRead(GAS_PIN);
  Serial.println(gas_value);

  if (gas_value>=350) {
    Serial.println("Leakage detected!");
    digitalWrite(RELAY_PIN, LOW); //turn on the relay
  }
  else{
    Serial.println("Relay off");
    digitalWrite(RELAY_PIN, HIGH); //turn off the realy
  }
  delay(5000);
}