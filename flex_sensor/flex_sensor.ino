const int ledPin = 3; //pin 3
const int flexPin = A0; //pin A0 to read analog input
int value; //save analog value
void setup(){
pinMode(ledPin, OUTPUT); //Set pin 3 as 'output'
Serial.begin(9600); //Begin serial communication
}
void loop(){
int flexValue;
flexValue = analogRead(flexPin);
Serial.print("sensor: ");
Serial.println(flexValue);
if(flexValue>890)
digitalWrite(ledPin,HIGH);
else
digitalWrite(ledPin,LOW);
delay(1000);
}