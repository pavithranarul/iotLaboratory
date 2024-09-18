#define S0 8  
#define S1 9
#define S2 10
#define S3 11
#define OUT 12

int data = 0;  // Variable to store sensor data

void setup() {
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(OUT, INPUT);

    Serial.begin(9600);

    // Set frequency scaling to 100%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, HIGH);
}

void loop() {
    readColor("Red", LOW, LOW);    // Read red value
    readColor("Blue", LOW, HIGH);  // Read blue value
    readColor("Green", HIGH, HIGH);// Read green value

    Serial.println();
    delay(2000);
}

void readColor(const char* color, int s2State, int s3State) {
    digitalWrite(S2, s2State);
    digitalWrite(S3, s3State);
    data = pulseIn(OUT, LOW);  // Measure pulse duration
    Serial.print(color);
    Serial.print(" value: ");
    Serial.print(data);
    Serial.print("\t");
    delay(20);
}
