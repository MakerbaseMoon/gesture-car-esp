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

void setup() {
    Serial.begin(115200);
    Serial.printf("\n");
    while(!Serial);
}

void loop() {

}
