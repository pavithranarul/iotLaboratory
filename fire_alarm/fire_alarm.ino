#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Lowest and highest sensor readings
const int sensorMin = 0;     // Sensor minimum
const int sensorMax = 1024;   // Sensor maximum

const int buzzer = 8;
const int light = 7;
const int light1 = 6;
const int light2 = 5;

void setup() {
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    pinMode(light, OUTPUT);
    pinMode(light1, OUTPUT);
    pinMode(light2, OUTPUT);

    Serial.println("Fire Detection Program");
    Serial.println(F("Fire detection test!"));
}

void loop() {
    // Read the sensor on analog A0
    int sensorReading = analogRead(A0);

    // Map the sensor range (four options)
    int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

    // Range value
    switch (range) {
        case 0: // A fire closer than 1.5 feet away
            Serial.println("Close Fire");
            tone(buzzer, 1000);  // Send 1KHz sound signal
            delay(1000);
            digitalWrite(light, HIGH);
            tone(buzzer, 500);
            noTone(buzzer);      // Stop sound
            break;

        case 1: // A fire between 1-3 feet away
            Serial.println("** Distant Fire **");
            digitalWrite(light1, HIGH);
            break;

        case 2: // No fire detected
            Serial.println("No Fire");
            digitalWrite(light2, HIGH);
            break;
    }

    delay(500); // Delay between reads
    digitalWrite(light, LOW);
    digitalWrite(light1, LOW);
    digitalWrite(light2, LOW);
}
