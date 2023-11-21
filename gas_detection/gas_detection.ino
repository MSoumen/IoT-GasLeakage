const byte ledPin=LED_BUILTIN;
const byte gasPin=A0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Gas Sensor Warming up.");
  pinMode(ledPin, OUTPUT);
  delay(1200000); //warming up the sensor 10min (Though better if we warm it up for 24hrs) for better accuracy reading
  // while warming up the gas sensor start with high value then gradually decreases, until it become stable
  
}

void loop()
{
  int gasValue = analogRead(gasPin);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);
  if(gasValue>=700) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
  delay(5000);
}