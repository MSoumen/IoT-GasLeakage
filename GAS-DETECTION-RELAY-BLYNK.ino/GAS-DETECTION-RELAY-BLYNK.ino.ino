#define BLYNK_TEMPLATE_ID   "TMPL3pdGldEia"
#define BLYNK_TEMPLATE_NAME "LPG Leakage Detection"
#define BLYNK_AUTH_TOKEN    "ScSVbeEVHQyliqhaPbnM83VTcMBin6qG"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#define GAS_PIN  A0
#define RELAY_PIN 1

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

  if (gas_value>=150) {
    Serial.println("Leakage detected!");
    // Blynk.notify("Alert : Gas Leakage detected in Home");
    // Blynk.logEvent("leakage_alert","Gas Leakage detected in Home");
    
    digitalWrite(RELAY_PIN, LOW); //turn on the relay
  }
  else{
    digitalWrite(RELAY_PIN, HIGH); //turn off the realy

  }
}

void setup(){
  Serial.begin(115200);
  
  pinMode(GAS_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, notify_on_gas_detection);
}

void loop(){
  Blynk.run();
  timer.run();
}