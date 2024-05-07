#define BLYNK_TEMPLATE_ID   "TMPL3pdGldEia"
#define BLYNK_TEMPLATE_NAME "LPG Leakage Detection"
#define BLYNK_AUTH_TOKEN    "ScSVbeEVHQyliqhaPbnM83VTcMBin6qG"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



// Comment this out to disable prints and save space
// #define BLYNK_PRINT Serial
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
    digitalWrite(LED_BUILTIN, LOW); //turn on led
    digitalWrite(RELAY_PIN, LOW); //turn on the relay
  }
  else{
    Serial.println("Relay off");
    digitalWrite(LED_BUILTIN, HIGH); //turn off led
    digitalWrite(RELAY_PIN, HIGH); //turn off the realy
    
  }

}

void setup(){
  Serial.begin(9600);
  
  pinMode(GAS_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, notify_on_gas_detection);
}

void loop(){
  Blynk.run();
  timer.run();
}