#define BLYNK_TEMPLATE_ID   "TMPL3pdGldEia"
#define BLYNK_TEMPLATE_NAME "LPG Leakage Detection"
#define BLYNK_AUTH_TOKEN    "ScSVbeEVHQyliqhaPbnM83VTcMBin6qG"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define GAS_PIN  A0
#define RELAY_PIN 5

#define DATASTREAM V0
#define STATUS V1

char auth[] = BLYNK_AUTH_TOKEN;

//  WiFi credentials.
char ssid[] =  "Aircrack-ng"; //  "WIFI NAME";
char pass[] =  "RedChille";     //  "WIFI PASSWORD"; // "" for open networks.
 

BlynkTimer timer;

void notify_on_gas_detection()
{
  int gas_value = analogRead(GAS_PIN);
  Serial.println(gas_value);
  
  Blynk.virtualWrite(DATASTREAM, gas_value);
  Blynk.virtualWrite(STATUS, 1);

  if (gas_value>=350) {
    Serial.println("Leakage detected!");
    digitalWrite(RELAY_PIN, LOW); //turn on the relay
  }
  else{
    Serial.println("Relay off");
    digitalWrite(RELAY_PIN, HIGH); //turn off the realy
  }

}

void setup(){
  Serial.begin(9600);
  
  pinMode(GAS_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
  delay(2000);
  timer.setInterval(5000L, notify_on_gas_detection);
}

void loop(){
  if(WiFi.status()!= WL_CONNECTED){
    Serial.println("Disconnected!");
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
  else{
    Blynk.run();
    timer.run();   
  }
}
