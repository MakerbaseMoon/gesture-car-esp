#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#define FRONT_IN1   18
#define FRONT_IN2   2

#define FRONT_IN3   4
#define FRONT_IN4   16

#define BACK_IN1    13
#define BACK_IN2    25

#define BACK_IN3    27
#define BACK_IN4    26

const char* ssid = SSID;
const char* password = PASSWORD;

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    Serial.printf("\n");
    while(!Serial);

    pinMode(FRONT_IN1, OUTPUT);
    pinMode(FRONT_IN2, OUTPUT);
    pinMode(FRONT_IN3, OUTPUT);
    pinMode(FRONT_IN4, OUTPUT);
    pinMode(BACK_IN1, OUTPUT);
    pinMode(BACK_IN2, OUTPUT);
    pinMode(BACK_IN3, OUTPUT);
    pinMode(BACK_IN4, OUTPUT);

    if(!SPIFFS.begin(true)) {
        Serial.println("SPIFFS initialization failed!");
        return;
    }
    Serial.println("SPIFFS initialization successful!");

    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");

    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("server success");
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("javascript success");
        request->send(SPIFFS, "/main.js", "application/javascript");
    });

    server.on("/forward", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("forward");
        request->send(200, "text/plain", "Forward command received.");
    });

    server.on("/backward", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("backward");
        request->send(200, "text/plain", "Backward command received.");
    });

    server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("left");
        request->send(200, "text/plain", "Left command received.");
    });

    server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("right");
        request->send(200, "text/plain", "Right command received.");
    });

    server.begin();
}

void loop() {

}
