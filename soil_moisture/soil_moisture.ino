#include <Wire.h>

const int buzzer = 11;
const int ledDry = 13;
const int ledHumid = 10;
const int ledWater = 12;
const int pump = 9;
int moisture;

void handleSoilCondition(String condition, int ledPin, int buzzerTone = 0); // Function prototype

void setup() {
    pinMode(A0, INPUT);        // Moisture sensor
    Serial.begin(9600);        // Begin Serial communication
    pinMode(buzzer, OUTPUT);   // Buzzer
    pinMode(ledDry, OUTPUT);   // Dry LED
    pinMode(ledHumid, OUTPUT); // Humid LED
    pinMode(ledWater, OUTPUT); // Water LED
    pinMode(pump, OUTPUT);     // Pump control
}

void loop() {
    int sensorValue = analogRead(A0);  // Read sensor value
    moisture = (100 - (sensorValue / 1023.00) * 100);  // Convert to percentage
    Serial.print(moisture);
    Serial.println("%");
    Serial.println("----------");

    // Check sensor status
    if (sensorValue >= 1000) {
        Serial.println("Not in soil or disconnected");
    } 
    else if (sensorValue >= 600) {  // Dry soil
        handleSoilCondition("DRY SOIL", ledDry, 1000);
    } 
    else if (sensorValue >= 370) {  // Humid soil
        handleSoilCondition("HUMID SOIL", ledHumid);
    } 
    else {  // Water soil
        handleSoilCondition("WATER SOIL", ledWater);
    }
}

void handleSoilCondition(String condition, int ledPin, int buzzerTone) {
    Serial.println(condition);
    digitalWrite(pump, condition == "DRY SOIL" ? LOW : HIGH);
    digitalWrite(ledDry, LOW);
    digitalWrite(ledHumid, LOW);
    digitalWrite(ledWater, LOW);
    digitalWrite(ledPin, HIGH);

    if (buzzerTone > 0) {
        tone(buzzer, buzzerTone);
        delay(1000);
        noTone(buzzer);
    }
    delay(1000);
}
