#include <Wire.h>

#define ECHO_PIN 3
#define TRIG_PIN 2

const int BUZZER = 8;
const int LIGHT = 13;
const int LIGHT2 = 12;

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(LIGHT, OUTPUT);
    pinMode(LIGHT2, OUTPUT);

    Serial.begin(9600);
    Serial.println("Distance Measurement Program");
}

void loop() {
    int distance = getDistance();
    
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    updateIndicators(distance);

    delay(1000); // Delay before the next measurement
}

int getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2;
}

void updateIndicators(int distance) {
    digitalWrite(LIGHT, LOW);
    digitalWrite(LIGHT2, LOW);
    noTone(BUZZER);

    if (distance <= 10) {
        Serial.println("Very Close");
        digitalWrite(LIGHT, HIGH);
        tone(BUZZER, 1000); // 1KHz sound
        delay(1000); // For 1 second
    } else if (distance <= 50) {
        Serial.println("Near Range");
        digitalWrite(LIGHT2, HIGH);
    } else {
        Serial.println("Far Range");
    }
}
