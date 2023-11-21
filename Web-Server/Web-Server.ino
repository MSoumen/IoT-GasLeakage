#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h> //mDNS is not working
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

// #define LED LED_BUILTIN

void blinkLED();
void handleRoot();
void handleNotFound();
void glowLED();

//create a web server that listen for HTTP req. on port 80
ESP8266WebServer server(80);


void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("\n");
  // pinMode(LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  const char *SSID = "HELLO", *PASS = "12345678";
  WiFi.hostname("Expressif-8266");
  WiFi.begin(SSID, PASS);
  Serial.print("Connecting ");
  while (WiFi.status() != WL_CONNECTED) {
    blinkLED();
    delay(200);
    Serial.print(". ");
  }
  Serial.println("\n");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  glowLED();
  // digitalWrite(LED_BUILTIN, HIGH);
  // Serial.println("Connection lost!");
  delay(50);

  if(MDNS.begin("esp")) Serial.println("mDNS Satrted.");
  else Serial.println("ERROR setting in mDNS");

  // working with server
  server.on("/", handleRoot);
  server.on("/main", handleRoot);
  server.on("/greet", greet);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP Server [Port:80] started.");
}

boolean flag = false;

void loop() {
  MDNS.update();
  server.handleClient();
  
  delay(10);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connection lost!");
    Serial.print("Trying to reconnect. ");
  }
  while (WiFi.status() != WL_CONNECTED) {
    blinkLED();
    delay(200);
    Serial.print(". ");
  }
  if (WiFi.status() == WL_CONNECTED && !flag) {
    flag = true;
    glowLED();
    // digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("\n");
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());
    delay(10);
    
  }
  delay(100);
}

void handleRoot() {
  server.send(200, "text/plain", "Emergency Alert!");
}

void greet(){
  server.send(200, "text/plain", "Hello Soumen. ");
}

void handleNotFound() {
  server.send(404, "text/plain", "404 : Page not Found!");
}

void blinkLED() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void glowLED(){
  Serial.println("LED on");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
}