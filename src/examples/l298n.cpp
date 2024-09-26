#include <Arduino.h>

#include "header.h"

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

    Serial.println("Forward function run");
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

    Serial.println("Backward function run");
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

    Serial.println("Strafe left function run");
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

    Serial.println("Strafe right function run");


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

    Serial.println("Stop function run");
}

void setup() {
    Serial.begin(115200);
    Serial.printf("\n");

    pinMode(RIGHT_IN1, OUTPUT);
    pinMode(RIGHT_IN2, OUTPUT);
    pinMode(LEFT_IN1, OUTPUT);
    pinMode(LEFT_IN2, OUTPUT);
    pinMode(RIGHT_IN3, OUTPUT);
    pinMode(RIGHT_IN4, OUTPUT);
    pinMode(LEFT_IN3, OUTPUT);
    pinMode(LEFT_IN4, OUTPUT);

    Motor_BW();
    delay(5000);
    Motor_FW();
    delay(5000);
    Motor_SL();
    delay(5000);
    Motor_SR();
    delay(5000);
    Motor_STP();
    delay(1000);
}

void loop() {

}
