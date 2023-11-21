//connecting to one specific network
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

//put network details
const char* SSID = "HELLO";
const char* PASS = "12345678";

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(100);
  Serial.println("Setup started ->");
  WiFi.hostname("ESP8266-GROUP-8");  // changing the board name which will be displayed at hostpot
  WiFi.begin(SSID, PASS);
  printf("Connecting to %s ...\n", SSID);

  int i = 0;
  // if wifi is not connected then blink the LED for 2 sec
  while (WiFi.status() != WL_CONNECTED) {
    delay(5);
    Serial.print(++i);
    Serial.println(". Trying to connect..");  //without some delay in loop print is not working.
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }

  Serial.println("Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // enabling the multipleDNS service
  boolean c = MDNS.begin("esp82");
  if (!c) {  // its enable us to use esp82.local in place of ip address to communicate.
    delay(5);
    Serial.println("Error while settng up mDNS!");
  }

  Serial.println("MDNS Started.");
}

void loop() {
  MDNS.update(); // provide it to run mdns properly
  // put your main code here, to run repeatedly:
  // int i=0;
  // if wifi is not connected then blink the LED for 2 sec
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nConnection lost !\nTrying to connect . ");
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(5);
    Serial.print(". ");
    // Serial.println(". Trying to connect.."); //without some delay in loop print is not working.
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }

  Serial.println("Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(2000);
}
