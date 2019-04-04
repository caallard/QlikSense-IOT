/*
 * @license    IOT-Gaph : Copyright (c) 2019, Charles-Alban Allard All rights reserved.
 * @release    1.0
 * @details    https://github.com/caallard/QlikSense-IOT
*/
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

//set here the wifi mode:
//AP: access point (Pc conected directly throught wifi to the Esp8266)
//Normal: connect the Esp8266 to the wifi of your network
const char* wifimode = "AP";

//WIFI
const char* ssid = "YourWifiSSID";
const char* password = "YourWifiPassword";

//WIFI Access Point
const char* ssid_AP = "QlikSense-IOT";
const char* password_AP = "APWifiPassword";

ESP8266WebServer server(80);

const int led = 13;
const int Neopixel = 14;//D5

DynamicJsonBuffer jsonBuffer;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, Neopixel, NEO_GRB + NEO_KHZ800);

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);

  if(wifimode!="AP"){
    WiFi.begin(ssid, password);
    Serial.println("");
  
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }else{
      Serial.print("Configuring access point...");
      /* You can remove the password parameter if you want the AP to be open. */
      WiFi.softAP(ssid_AP, password_AP);
    
      IPAddress myIP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(myIP);
  }

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'


  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/update", [](){
    digitalWrite(led, 1);
    String message = "Update:";
    for (uint8_t i=0; i<server.args(); i++){
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      
      if(server.argName(i)=="var" && server.arg(i)=="1"){
        strip.setPixelColor(0, 127, 127, 127);
        strip.setPixelColor(1, 127, 127, 127);
        strip.setPixelColor(2, 127, 127, 127);
        strip.show();
      }else if(server.argName(i)=="var" && server.arg(i)=="0"){
        //digitalWrite(cmdled, 0);
        strip.setPixelColor(0, 0, 0, 0);
        strip.setPixelColor(1, 0, 0, 0);
        strip.setPixelColor(2, 0, 0, 0);
        strip.show();
      }else if(server.argName(i)=="data"){
        
        JsonArray& tableau = jsonBuffer.parseArray(server.arg(i));
        
        for (int j=0; j <= 24; j++){
          int Red = tableau[j][0];
          int Green = tableau[j][1];
          int Blue = tableau[j][2];
          strip.setPixelColor(j, Red, Green, Blue);
        } 
        String output;
        tableau.printTo(output);
        message +=  output+ "\n";
		
        strip.show();
      }


      
    }
    server.send(200, "text/plain", message);
    digitalWrite(led, 0);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
