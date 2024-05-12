// Chage These Credentials with your Blynk Template credentials
// Chage These Credentials with your Blynk Template credentials 
#define BLYNK_TEMPLATE_ID "TMPL3pdGldEia"
#define BLYNK_TEMPLATE_NAME "LPG Leakage Detection"
#define BLYNK_AUTH_TOKEN "ScSVbeEVHQyliqhaPbnM83VTcMBin6qG"
#define BLYNK_DEVICE_NAME "Gas Detection"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi"; // Change your Wifi/ Hotspot Name
char pass[] = "S0um3n@redmi"; // Change your Wifi/ Hotspot Password

BlynkTimer timer;

#define fire LED_BUILTIN
int fire_Val = 0;

WidgetLED led(V1);

void setup() //Setup function - only function that is run in deep sleep mode
{
  Serial.begin(9600); //Start the serial output at 9600 baud
  pinMode(fire, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);//Splash screen delay

  delay(2000);
  timer.setInterval(5000L, mySensor);
}

void loop() //Loop function
{
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

void mySensor()
{
  fire_Val = digitalRead(fire);
   
  if (fire_Val == HIGH)
  {
    Blynk.logEvent("gas-leakage");
    Blynk.virtualWrite(V0, 1);
    Serial.print("Light is on, ");
    Serial.println("turning off after few seconds.");
    led.on();
    digitalWrite(fire, LOW);
    delay(5000);
  }

  else
  {
    Blynk.virtualWrite(V0, 0);
    Serial.print("Light is off, ");
    Serial.println("turning on after few seconds.");
    led.off();
    digitalWrite(fire, HIGH);
  }    
}