#include <Arduino.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "header.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if(info -> final && info -> index == 0 && info -> len == len && info -> opcode == WS_TEXT) {
        data[len] = 0;
        String message = (char*)data;
        Serial.printf("websocket: %s\n", message);
    }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type)
    {
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

void setup() {
    Serial.begin(115200);
    while(!Serial);

    WiFi.mode(WIFI_AP_STA);

    WiFi.begin(SSID, PASSWORD);
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
    WiFi.softAP(AP_SSID, AP_PASSWORD);

    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());

    initWebSocket();
    server.begin();
}

void loop() {
    delay(10);
}