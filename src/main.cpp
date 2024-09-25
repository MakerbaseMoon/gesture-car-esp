#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <esp_now.h>

#define FRONT_IN1   18
#define FRONT_IN2   2

#define FRONT_IN3   4
#define FRONT_IN4   16

#define BACK_IN1    13
#define BACK_IN2    25

#define BACK_IN3    27
#define BACK_IN4    26

int speed = 128;

const char* ssid = SSID;
const char* password = PASSWORD;

AsyncWebServer server(80);

void Motor_FW() {                   // 前進
    Serial.println("Forward function");

    analogWrite(FRONT_IN1, 0);
    analogWrite(FRONT_IN2, speed);

    analogWrite(FRONT_IN3, 0);
    analogWrite(FRONT_IN4, speed);

    analogWrite(BACK_IN1, 0);
    analogWrite(BACK_IN2, speed);

    analogWrite(BACK_IN3, 0);
    analogWrite(BACK_IN4, speed);
}
void Motor_BW() {                   // 後退
    Serial.println("Backward function");

    analogWrite(FRONT_IN1, speed);
    analogWrite(FRONT_IN2, 0);

    analogWrite(FRONT_IN3, speed);
    analogWrite(FRONT_IN4, 0);

    analogWrite(BACK_IN1, speed);
    analogWrite(BACK_IN2, 0);

    analogWrite(BACK_IN3, speed);
    analogWrite(BACK_IN4, 0);
}
void Motor_TL() {                   // 左轉
    Serial.println("Turn left function");

    analogWrite(FRONT_IN1, 0);
    analogWrite(FRONT_IN2, speed);

    analogWrite(FRONT_IN3, speed);
    analogWrite(FRONT_IN4, 0);

    analogWrite(BACK_IN1, 0);
    analogWrite(BACK_IN2, speed);

    analogWrite(BACK_IN3, speed);
    analogWrite(BACK_IN4, 0);
}
void Motor_TR() {                   // 右轉
    Serial.println("Turn right function");

    analogWrite(FRONT_IN1, speed);
    analogWrite(FRONT_IN2, 0);

    analogWrite(FRONT_IN3, 0);
    analogWrite(FRONT_IN4, speed);

    analogWrite(BACK_IN1, speed);
    analogWrite(BACK_IN2, 0);

    analogWrite(BACK_IN3, 0);
    analogWrite(BACK_IN4, speed);
}
void Motor_SL() {                   // 左平移
    Serial.println("Strafe left function");

    analogWrite(FRONT_IN1, 0);
    analogWrite(FRONT_IN2, speed);

    analogWrite(FRONT_IN3, speed);
    analogWrite(FRONT_IN4, 0);

    analogWrite(BACK_IN1, speed);
    analogWrite(BACK_IN2, 0);

    analogWrite(BACK_IN3, 0);
    analogWrite(BACK_IN4, speed);
}
void Motor_SR() {                   // 右平移
    Serial.println("Strafe right function");

    analogWrite(FRONT_IN1, speed);
    analogWrite(FRONT_IN2, 0);

    analogWrite(FRONT_IN3, 0);
    analogWrite(FRONT_IN4, speed);

    analogWrite(BACK_IN1, 0);
    analogWrite(BACK_IN2, speed);

    analogWrite(BACK_IN3, speed);
    analogWrite(BACK_IN4, 0);
}
void Motor_FL() {                   // 左前進
    Serial.println("Forward left function");

    analogWrite(FRONT_IN1, 0);
    analogWrite(FRONT_IN2, speed);

    analogWrite(FRONT_IN3, 0);
    analogWrite(FRONT_IN4, 0);

    analogWrite(BACK_IN1, 0);
    analogWrite(BACK_IN2, 0);

    analogWrite(BACK_IN3, 0);
    analogWrite(BACK_IN4, speed);
}
void Motor_BL() {                   // 左後退
    Serial.println("Backward left function");

    analogWrite(FRONT_IN1, 0);
    analogWrite(FRONT_IN2, 0);

    analogWrite(FRONT_IN3, speed);
    analogWrite(FRONT_IN4, 0);

    analogWrite(BACK_IN1, speed);
    analogWrite(BACK_IN2, 0);

    analogWrite(BACK_IN3, 0);
    analogWrite(BACK_IN4, 0);
}
void Motor_FR() {                   // 右前進
    Serial.println("Forward right function");

    analogWrite(FRONT_IN1, 0);
    analogWrite(FRONT_IN2, 0);

    analogWrite(FRONT_IN3, 0);
    analogWrite(FRONT_IN4, speed);

    analogWrite(BACK_IN1, 0);
    analogWrite(BACK_IN2, speed);
    
    analogWrite(BACK_IN3, 0);
    analogWrite(BACK_IN4, 0);
}
void Motor_BR() {                   // 右後退
    Serial.println("Backward right function");

    analogWrite(FRONT_IN1, speed);
    analogWrite(FRONT_IN2, 0);

    analogWrite(FRONT_IN3, 0);
    analogWrite(FRONT_IN4, 0);

    analogWrite(BACK_IN1, 0);
    analogWrite(BACK_IN2, 0);
    
    analogWrite(BACK_IN3, speed);
    analogWrite(BACK_IN4, 0);
}
void Motor_STP() {                  // 停止
    Serial.println("Stop function");

    analogWrite(FRONT_IN1, 0);
    analogWrite(FRONT_IN2, 0);

    analogWrite(FRONT_IN3, 0);
    analogWrite(FRONT_IN4, 0);

    analogWrite(BACK_IN1, 0);
    analogWrite(BACK_IN2, 0);

    analogWrite(BACK_IN3, 0);
    analogWrite(BACK_IN4, 0);
}

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

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("style success");
        request->send(SPIFFS, "/style.css", "text/css");
    });

    server.on("/Forward", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("Forward");
        request->send(200, "text/plain", "Forward command received.");
        Motor_FW();
    });

    server.on("/Backward", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("Backward");
        request->send(200, "text/plain", "Backward command received.");
        Motor_BW();
    });

    server.on("/TurnLeft", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("TurnLeft");
        request->send(200, "text/plain", "TurnLeft command received.");
        Motor_TL();
    });

    server.on("/TurnRight", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("TurnRight");
        request->send(200, "text/plain", "TurnRight command received.");
        Motor_TR();
    });

    server.on("/StrafeLeft", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("StrafeLeft");
        request->send(200, "text/plain", "StrafeLeft command received.");
        Motor_SL();
    });

    server.on("/StrafeRight", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("StrafeRight");
        request->send(200, "text/plain", "StrafeRight command received.");
        Motor_SR();
    });

    server.on("/ForwardLeft", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("ForwardLeft");
        request->send(200, "text/plain", "ForwardLeft command received.");
        Motor_FL();
    });

    server.on("/BackwardLeft", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("BackwardLeft");
        request->send(200, "text/plain", "BackwardLeft command received.");
        Motor_BL();
    });

    server.on("/ForwardRight", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("ForwardRight");
        request->send(200, "text/plain", "ForwardRight command received.");
        Motor_FR();
    });

    server.on("/BackwardRight", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("BackwardRight");
        request->send(200, "text/plain", "BackwardRight command received.");
        Motor_BR();
    });

    server.on("/Stop", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("Stop");
        request->send(200, "text/plain", "Stop command received.");
        Motor_STP();
    });

    server.begin();
}

void loop() {

}
