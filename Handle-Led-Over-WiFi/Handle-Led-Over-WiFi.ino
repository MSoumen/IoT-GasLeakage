#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>


void blinkLED();
void greet();
void handleRoot();
void handleLED();
void handleNotFound();
// void glowLED();

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
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);

  if(MDNS.begin("esp")) Serial.println("mDNS Satrted.");
  else Serial.println("ERROR setting in mDNS");

  // working with server
  server.on("/",HTTP_GET, handleRoot);
  server.on("/main",HTTP_GET, handleRoot);
  server.on("/greet", HTTP_GET, greet);

  server.on("/led", HTTP_POST, handleLED);

  // server.onNotFound(handleNotFound);
  //inline function
  server.onNotFound([](){
    server.send(404, "text/plain", "404: Page not found!  :( ");
  });

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
    // glowLED();
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
  const char *htmlcode = "<form action=\"led\" method=\"POST\"> <input type=\"submit\" value=\"toggle LED\"></form>";
  server.send(200, "text/html", htmlcode);
}

void greet(){
  server.send(200, "text/plain", "Hello Soumen. ");
}

void handleLED(){
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  server.sendHeader("Location", "/"); //return to root again
  server.send(303);
}

/*
void handleNotFound() {
  server.send(404, "text/plain", "404 : Page not Found!");
}
*/

void blinkLED() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

/*
void glowLED(){
  Serial.println("LED on");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
}
*/