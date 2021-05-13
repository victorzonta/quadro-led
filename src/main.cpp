#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h> 

#define  R D3
#define  G D2
#define  B D1

ESP8266WiFiMulti wifiMulti; 
ESP8266WebServer server(80);
void handleRoot();
void handleNotFound();
void changetored();
void changetogreen();
void changetoblue();
void changetoamarelo();
void changetodark();
void changetopurple();
void changecolor();
void changetoon();
void setup() {
  pinMode ( R, OUTPUT);
  pinMode ( G, OUTPUT);
  pinMode ( B, OUTPUT);
  Serial.begin(9600);
  wifiMulti.addAP("WIFI", "SENHA");
  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/vermelho", changetored);
  server.on("/verde", changetogreen);
  server.on("/azul", changetoblue);
  server.on("/amarelo", changetoamarelo);
  server.on("/off", changetodark);
  server.on("/roxo", changetopurple);
  server.on("/on", changetoon);
  server.on("/mudacor", changecolor);
  server.onNotFound(handleNotFound);
  server.begin();                           // Actually start the server
  Serial.println("HTTP server started"); 
 
}

void loop() {
  server.handleClient();

}
void changetored() {
  digitalWrite (R, HIGH);
  digitalWrite (G, LOW);
  digitalWrite (B, LOW);
  server.send(200, "text/plain", "vermelho");
}
void changetogreen() {
  digitalWrite (R, LOW);
  digitalWrite (G, HIGH);
  digitalWrite (B, LOW);
  server.send(200, "text/plain", "verde");
}
void changetoblue() {
  digitalWrite (R, LOW);
  digitalWrite (G, LOW);
  digitalWrite (B, HIGH);
  server.send(200, "text/plain", "azul");
}
void changetoamarelo() {
  digitalWrite (R, HIGH);
  digitalWrite (G, HIGH);
  digitalWrite (B, LOW);
  server.send(200, "text/plain", "amarelo");
}
void changetodark() {
  digitalWrite (R, LOW);
  digitalWrite (G, LOW);
  digitalWrite (B, LOW);
  server.send(200, "text/plain", "off");
}
void changetopurple() {
  digitalWrite (R, HIGH);
  digitalWrite (G, LOW);
  digitalWrite (B, HIGH);
  server.send(200, "text/plain", "roxo");
}
void changetoon() {
  digitalWrite (R, HIGH);
  digitalWrite (G, HIGH);
  digitalWrite (B, HIGH);
  server.send(200, "text/plain", "to on");
}


void handleRoot() {
  server.send(200, "text/plain", "led zonta on");   // Send HTTP status 200 (Ok) and send some text to the browser/client
}
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void changecolor() {
  String vermelho;
  String azul;
  String verde;
  vermelho=server.arg("vermelho");
  azul=server.arg("azul");
  verde=server.arg("verde");
  analogWrite(R, vermelho.toInt());
  analogWrite(G, verde.toInt());
  analogWrite(B, azul.toInt());
  server.send(200, "text/plain", "mudacor ");
}