
#include <LiquidCrystal_I2C.h>

const int trigPins[] = {3, 5, 7, 9};  
const int echoPins[] = {2, 4, 6, 8};  
const int numSensors = 4;             
const int ledPin[] = {14,15,16,17};
LiquidCrystal_I2C lcd1(0x27, 20, 4);

float durations[numSensors];
float distances[numSensors];

void setup() {
  lcd1.begin(20,4);
  lcd1.backlight();
  Serial.begin(9600);
  for (int i = 0; i < numSensors; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    pinMode(ledPin[i], OUTPUT);
  }
  
}

void loop() {
  for (int i = 0; i < numSensors; i++) {
    delayMicroseconds(50000);
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);
    
    durations[i] = pulseIn(echoPins[i], HIGH);
    distances[i] = (durations[i] * 0.0343) / 2;
    
    if(distances[i]<300){
      digitalWrite(ledPin[i], LOW);
      lcd1.setCursor(0, i);
      lcd1.print("P.Slot ");
      lcd1.print(i+1);
      lcd1.print(" is  FULL");
    }
    else{
      digitalWrite(ledPin[i], HIGH);
      lcd1.setCursor(0, i);
      lcd1.print("P.Slot ");
      lcd1.print(i+1);
      lcd1.print(" is EMPTY");
    }
  }
  
  delay(100);
}