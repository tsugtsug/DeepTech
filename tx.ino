#include <LoRa.h>

#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // LoRaモジュールを初期化
  Serial.println("LoRa Sender");
  if (!LoRa.begin(915E6)) { // 915 MHzの周波数でLoRa通信を設定
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.println("Sending packet...");

  // LoRaパケットの開始
  LoRa.beginPacket();
  LoRa.print("Hello LoRa!");  // 送信するメッセージ
  LoRa.endPacket();  // パケットを送信

  delay(5000);  // 5秒待機
}
