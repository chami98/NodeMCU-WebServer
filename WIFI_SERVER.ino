#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

WiFiClient wifiClient;

const char* ssid = "Nokia 3.4";
const char* password = "12345678";

int ledPin2 = D2;
int ledPin1 = D0;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello World");
}

void handleOn(){
  digitalWrite(ledPin1, HIGH);
  server.send(200,"text/plain", "LED turned ON");

  digitalWrite(ledPin2, HIGH);
  server.send(200,"text/plain", "LED turned ON");
}

void handleOff(){
  digitalWrite(ledPin1, LOW);
  server.send(200,"text/plain", "LED turned OFF");

  digitalWrite(ledPin2, LOW);
  server.send(200,"text/plain", "LED turned OFF");
}


void setup() {
  pinMode(ledPin2, OUTPUT);  
  pinMode(ledPin1, OUTPUT);  
  Serial.begin(9600);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);
  server.on("/on",handleOn);
  server.on("/off",handleOff);

  server.begin();
   Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
