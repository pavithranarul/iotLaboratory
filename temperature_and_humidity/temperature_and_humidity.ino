#include <Wire.h>
#include "DHT.h"

#define DHTPIN 2        // Pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11 sensor type
DHT dht(DHTPIN, DHTTYPE);

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

    Serial.println("DHT11 Temperature & Humidity Program");
    dht.begin();
}

void loop() {
    digitalWrite(light, LOW);    // Reset light
    delay(2000);                 // Wait between measurements

    float humidity = dht.readHumidity();
    float tempC = dht.readTemperature();
    
    if (isnan(humidity) || isnan(tempC)) {
        Serial.println("Sensor error!");
        digitalWrite(light, HIGH);
        return;
    }

    Serial.print("Humidity: "); Serial.print(humidity);
    Serial.print("%  Temperature: "); Serial.print(tempC); Serial.println("C");

    if (tempC > 29) {  // High temperature alert
        alertHighTemp();
    } else {
        alertLowTemp();
    }

    delay(2000);  // Pause before next reading
    resetLights();
}

void alertHighTemp() {
    tone(buzzer, 1000, 1000);      // 1KHz tone for 1 sec
    digitalWrite(light1, HIGH);    // High temp light ON
    digitalWrite(light2, LOW);     // Low temp light OFF
    Serial.println("Alert: HIGH Temperature");
}

void alertLowTemp() {
    Serial.println("Alert: LOW Temperature");
    digitalWrite(light2, HIGH);    // Low temp light ON
}

void resetLights() {
    digitalWrite(light1, LOW);
    digitalWrite(light2, LOW);     // Reset lights
}
