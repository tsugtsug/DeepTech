#include <Wire.h>
const int sensorPin = A2;  // アナログピンを指定

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("");
  int sensorValue = analogRead(sensorPin);  // アナログ信号を読み取る
  
  Serial.println(sensorValue);  // 読み取った値を表示
  if (sensorValue >= 800) // Threshold level
    Serial.println("HIGHT\nThe door is closed");
  else
    Serial.println("LOW\nThe door is open");
  delay(2000);
}
