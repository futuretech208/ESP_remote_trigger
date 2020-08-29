/*
  Open browser, visit 192.168.4.1
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Shutter Remote";
const char *password = "password";
int focusPin = LOW;
int shutterPin = LOW;

ESP8266WebServer server(80);

void handleRoot()
{
  response();
}

void capture()
{
  focusPin = LOW;
  shutterPin =LOW;
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  delay(100);
  digitalWrite(D2, LOW);
  digitalWrite(D1, LOW);
  delay(100);
  response();
}

void burstMode()
{
  focusPin = LOW;
  shutterPin =LOW;
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  response();
}

void bulbOn() 
{
  focusPin = LOW;
  shutterPin =LOW;
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  response();
}

void bulbOff() 
{
  focusPin = LOW;
  shutterPin = LOW;
  digitalWrite(D2, LOW);
  digitalWrite(D1, LOW);
  response();
}

const String HtmlHtml = "<html><head>"
                        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlHtmlClose = "</html>";
const String HtmlTitle = "<h1>Wireless shutter trigger</h1><br/>\n";
const String HtmlButtons =
  "<a href=\"capture\"><button style=\"display: inline-block; width: 50%; margin: 5px auto; text-align: center;\">Capture</button></a>"
  "<a href=\"burst\"><button style=\"display: inline-block; width: 50%; margin: 5px auto; text-align: center;\">Burst mode</button></a><br/><br/>"
  "<a href=\"bulbOn\"><button style=\"display: inline-block; width: 50%; margin: 5px auto; text-align: center;\">Start Bulb Mode</button></a>"
  "<a href=\"bulbOff\"><button style=\"display: inline-block; width: 50%; margin: 5px auto; text-align: center;\">Stop</button></a><br/><br/>";
void response()
{
  String htmlRes = HtmlHtml + HtmlTitle;
  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;
  server.send(200, "text/html", htmlRes);
}

void setup()
{
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  WiFi.softAP(ssid, password);
  IPAddress apip = WiFi.softAPIP();
  Serial.print("visit: \n");
  Serial.println(apip);
  server.on("/", handleRoot);
  server.on("/capture", capture);
  server.on("/burst", burstMode);
  server.on("/bulbOn", bulbOn);
  server.on("/bulbOff", bulbOff);
  server.begin();
  Serial.println("HTTP server started");
  pinMode(D1, OUTPUT);
  digitalWrite(D1, focusPin);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, shutterPin);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
}
void loop()
{
  server.handleClient();
}
