#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <esp_now.h>

#define RIGHT_IN1   18    // B
#define RIGHT_IN2   16    // B

#define RIGHT_IN3    4    // F 
#define RIGHT_IN4    2    // F

#define LEFT_IN1    13    // B
#define LEFT_IN2    27    // B

#define LEFT_IN3    26    // F
#define LEFT_IN4    25    // F

int speed = 128;

const char* ssid = SSID;
const char* password = PASSWORD;

#define CAR_MAC {0xCC, 0x7B, 0x5C, 0x99, 0x59, 0x14}
#define CONTROLLER_MAC {0xB4, 0x8A, 0x0A, 0x9B, 0x05, 0x44}

const uint8_t car_mac[6] = CAR_MAC;
const uint8_t controller_mac[6] = CONTROLLER_MAC;

esp_now_peer_info_t peerInfo;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if(info -> final && info -> index == 0 && info -> len == len && info -> opcode == WS_TEXT) {
        data[len] = 0;
        String message = (char*)data;
        Serial.printf("\nwebsocket: %s\n", message);
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

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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
}

void Motor_FW() {                   // 前進
    Serial.println("Forward function");

    analogWrite(RIGHT_IN1, speed);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, speed);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, speed);

    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, speed);
}

void Motor_BW() {                   // 後退
    Serial.println("Backward function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, speed);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, speed);

    analogWrite(LEFT_IN1, speed);
    analogWrite(LEFT_IN2, 0);

    analogWrite(LEFT_IN3, speed);
    analogWrite(LEFT_IN4, 0);
}

void Motor_TL() {                   // 左轉
    Serial.println("Turn left function");

    analogWrite(RIGHT_IN1, speed);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, speed);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, speed);
    analogWrite(LEFT_IN2, 0);

    analogWrite(LEFT_IN3, speed);
    analogWrite(LEFT_IN4, 0);
}

void Motor_TR() {                   // 右轉
    Serial.println("Turn right function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, speed);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, speed);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, speed);

    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, speed);
}

void Motor_SL() {                   // 左平移
    Serial.println("Strafe left function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, speed);

    analogWrite(RIGHT_IN3, speed);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, speed);

    analogWrite(LEFT_IN3, speed);
    analogWrite(LEFT_IN4, 0);
}

void Motor_SR() {                   // 右平移
    Serial.println("Strafe right function");

    analogWrite(RIGHT_IN1, speed);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, speed);

    analogWrite(LEFT_IN1, speed);
    analogWrite(LEFT_IN2, 0);

    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, speed);
}

void Motor_FL() {                   // 左前進
    Serial.println("Forward left function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, speed);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, speed);

    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, 0);
}

void Motor_BL() {                   // 左後退
    Serial.println("Backward left function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, speed);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, 0);

    analogWrite(LEFT_IN3, speed);
    analogWrite(LEFT_IN4, 0);
}

void Motor_FR() {                   // 右前進
    Serial.println("Forward right function");

    analogWrite(RIGHT_IN1, speed);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, 0);

    analogWrite(LEFT_IN1, 0);
    analogWrite(LEFT_IN2, 0);
    
    analogWrite(LEFT_IN3, 0);
    analogWrite(LEFT_IN4, speed);
}

void Motor_BR() {                   // 右後退
    Serial.println("Backward right function");

    analogWrite(RIGHT_IN1, 0);
    analogWrite(RIGHT_IN2, 0);

    analogWrite(RIGHT_IN3, 0);
    analogWrite(RIGHT_IN4, speed);

    analogWrite(LEFT_IN1, speed);
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

void setup() {
    Serial.begin(115200);
    Serial.printf("\n");
    while(!Serial);

    WiFi.mode(WIFI_STA);
    Serial.println("Controller MAC address: " + WiFi.macAddress());
    Serial.printf("Car MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n", car_mac[0], car_mac[1], car_mac[2], car_mac[3], car_mac[4], car_mac[5]);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        while(1);
    }

    esp_now_register_send_cb(OnDataSent);

    memcpy(peerInfo.peer_addr, car_mac, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }

    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

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

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/favicon.jpg", "image/x-icon");
    });
    
    initWebSocket();

    server.begin();
}

void loop() {
    String message = "Hello from 123";
    esp_err_t result = esp_now_send(car_mac, (uint8_t *)message.c_str(), message.length());

    if (result == ESP_OK) {
        Serial.println("Sent with success");
    } else {
        Serial.println("Error sending the data");
    }
    delay(1000);
}
