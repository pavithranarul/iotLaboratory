#include <Wire.h>

const int buzzer = 11;
const int light = 13;
const int sensor = 2;  // Sensor pin
int state = LOW;       // Motion state
int val = 0;           // Sensor value

void setup() {
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    pinMode(light, OUTPUT);
    pinMode(sensor, INPUT);  // Sensor as input
}

void loop() {
    val = digitalRead(sensor);  // Read sensor value

    if (val == HIGH && state == LOW) {  // Motion detected
        Serial.println("Motion Detected");
        digitalWrite(light, HIGH);
        tone(buzzer, 1000);  // Sound the buzzer
        delay(500);
        noTone(buzzer);
        state = HIGH;  // Update state to HIGH
    } 
    else if (val == LOW && state == HIGH) {  // Motion stopped
        Serial.println("Motion Stopped");
        digitalWrite(light, LOW);
        state = LOW;  // Update state to LOW
    }

    delay(100);  // Short delay to prevent bouncing
}
