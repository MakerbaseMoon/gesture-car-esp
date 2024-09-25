#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>

#include "header.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

void Motor_FW() {                   // 前進
    Serial.println("Forward function");

    analogWrite(RIGHT_IN1, SPEED);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, SPEED);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, SPEED);

    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, SPEED);
}

void Motor_BW() {                   // 後退
    Serial.println("Backward function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, SPEED);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, SPEED);

    analogWrite(LEFT_IN1, SPEED);
    analogWrite(LEFT_IN2, 0);

    analogWrite(LEFT_IN3, SPEED);
    analogWrite(LEFT_IN4, 0);
}

void Motor_TL() {                   // 左轉
    Serial.println("Turn left function");

    analogWrite(RIGHT_IN1, SPEED);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, SPEED);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, SPEED);
    analogWrite(LEFT_IN2, 0);

    analogWrite(LEFT_IN3, SPEED);
    analogWrite(LEFT_IN4, 0);
}

void Motor_TR() {                   // 右轉
    Serial.println("Turn right function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, SPEED);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, SPEED);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, SPEED);

    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, SPEED);
}

void Motor_SL() {                   // 左平移
    Serial.println("Strafe left function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, SPEED);

    analogWrite(RIGHT_IN3, SPEED);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, SPEED);

    analogWrite(LEFT_IN3, SPEED);
    analogWrite(LEFT_IN4, 0);
}

void Motor_SR() {                   // 右平移
    Serial.println("Strafe right function");

    analogWrite(RIGHT_IN1, SPEED);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, SPEED);

    analogWrite(LEFT_IN1, SPEED);
    analogWrite(LEFT_IN2, 0);

    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, SPEED);
}

void Motor_FL() {                   // 左前進
    Serial.println("Forward left function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, SPEED);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, SPEED);

    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, 0);
}

void Motor_BL() {                   // 左後退
    Serial.println("Backward left function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, SPEED);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, 0);

    analogWrite(LEFT_IN3, SPEED);
    analogWrite(LEFT_IN4, 0);
}

void Motor_FR() {                   // 右前進
    Serial.println("Forward right function");

    analogWrite(RIGHT_IN1, SPEED);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, 0);
    
    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, SPEED);
}

void Motor_BR() {                   // 右後退
    Serial.println("Backward right function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, SPEED);

    analogWrite(LEFT_IN1, SPEED);
    analogWrite(LEFT_IN2, 0);
    
    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, 0);
}

void Motor_STP() {                  // 停止
    Serial.println("Stop function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, 0);

    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, 0);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if(info -> final && info -> index == 0 && info -> len == len && info -> opcode == WS_TEXT) {
        data[len] = 0;
        String message = (char*)data;
        Serial.printf("\nwebsocket: %s\n", message);

        if(message.indexOf("StrafeLeft") >= 0) {
            Motor_SL();
            Serial.printf("Websocket: StrafeLeft\n");
        } else if(message.indexOf("StrafeRight") >= 0) {
            Motor_SR();
            Serial.printf("Websocket: StrafeRight\n");
        } else if(message.indexOf("Forward") >= 0) {
            Motor_FW();
            Serial.printf("Websocket: Forward\n");
        } else if(message.indexOf("Backward") >= 0) {
            Motor_BW();
            Serial.printf("Websocket: Backward\n");
        } else {
            Motor_STP();
            Serial.printf("Websocket: Stop\n");
        }
    }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client -> id(), client -> remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client -> id());
        break;
    case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}

void initWebSocket() {
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    Serial.printf("Packet received from: %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    char *data = (char *)malloc(len + 1);
    if (data == NULL) {
        Serial.println("malloc failed");
        return;
    }

    memcpy(data, incomingData, len);
    data[len] = 0;
    Serial.printf("Received data: %s\n", data);

    if(strcmp(data, "StrafeLeft") == 0) {
        Motor_SL();
        Serial.println("The string is StrafeLeft.");
    } else if(strcmp(data, "StrafeRight") == 0) {
        Motor_SR();
        Serial.println("The string is StrafeRight.");
    } else if(strcmp(data, "Forward") == 0) {
        Motor_FW();
        Serial.println("The string is Forward.");
    } else if(strcmp(data, "Backward") == 0) {
        Motor_BW();
        Serial.println("The string is Backward.");
    } else {
        Motor_STP();
        Serial.println("The string is Stop.");
    }
}


void setup() {
    Serial.begin(115200);
    Serial.printf("\n");
    while(!Serial);

    WiFi.mode(WIFI_AP_STA);

    pinMode(RIGHT_IN1, OUTPUT);
    pinMode(RIGHT_IN2, OUTPUT);
    pinMode(LEFT_IN1, OUTPUT);
    pinMode(LEFT_IN2, OUTPUT);
    pinMode(RIGHT_IN3, OUTPUT);
    pinMode(RIGHT_IN4, OUTPUT);
    pinMode(LEFT_IN3, OUTPUT);
    pinMode(LEFT_IN4, OUTPUT);

    if(!SPIFFS.begin(true)) {
        Serial.println("SPIFFS initialization failed!");
        return;
    }
    Serial.println("SPIFFS initialization successful!");

    WiFi.begin(SSID, PASSWORD);
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
    WiFi.softAP(AP_SSID, AP_PASSWORD);

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

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/favicon.jpg", "image/x-icon");
    });

    initWebSocket();
    server.begin();
}

void loop() {
    delay(10);
}
