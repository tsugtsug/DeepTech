#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // LoRaモジュールを初期化
  Serial.println("LoRa Receiver");
  while (1) {
    if (!LoRa.begin(915E6)) {  // 送信側と同じ周波数（915 MHz）でLoRa通信を設定
      Serial.println("Starting LoRa failed!");
    }
    else {
      Serial.println("Starting LoRa connection success!");
      break;
    }
    delay(1000);
  }
}

void loop() {
  // パケットを受信したかどうかを確認
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // パケットを受信
    Serial.print("Received packet: ");

    // 受信したメッセージを表示
    while (LoRa.available()) {
      String message = LoRa.readString();
      Serial.println(message);
    }


    Serial.println("");
    // Serial.print(" with RSSI: ");
    // Serial.println(LoRa.packetRssi());  // 受信信号強度（RSSI）を表示
  }
}
