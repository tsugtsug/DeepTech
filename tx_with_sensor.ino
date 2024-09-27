#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

const int sensorPin = A2;  // アナログピンを指定

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // LoRaモジュールを初期化
  Serial.println("LoRa Sender");
  while (1) {
    if (!LoRa.begin(868E6)) { // 868 MHzの周波数でLoRa通信を設定
      Serial.println("Starting LoRa failed!");
    }
    else {
      Serial.println("Starting LoRa conncetion success!");
      break;
    }
    delay(1000);
  }
}

void loop() {

  Serial.println("");
  int sensorValue = analogRead(sensorPin);  // アナログ信号を読み取る
  
  Serial.println("Sending packet..."); // (Serial)

  Serial.println(sensorValue);  // 読み取った値を表示 (Serial)

  LoRa.beginPacket(); // LoRaパケットの開始 (LoRa begin)

  if (sensorValue >= 800) { // Threshold level 
    Serial.println("HIGHT\nThe door is closed"); // (Serial)
    LoRa.print(1); // (LoRa)
  } else {
    Serial.println("LOW\nThe door is open"); // (Serial)
    LoRa.print(0); // (LoRa)
  }

  LoRa.endPacket();  // パケットを送信完了 (LoRa end)

  delay(5000);
}
