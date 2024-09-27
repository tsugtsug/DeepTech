#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // LoRaモジュールを初期化
  Serial.println("LoRa Receiver");
  while (1) {
    if (!LoRa.begin(868E6)) {  // 送信側と同じ周波数（868 MHz）でLoRa通信を設定
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
    // Serial.print("Received packet: ");

    String message;
    // 受信したメッセージを表示
    while (LoRa.available()) {
      message = LoRa.readString();
    }
    if (message == "0") {
      Serial.println("open");
    } else if (message == "1") {
      Serial.println("close");
    } else {
      Serial.println("error" + message);
    }

    delay(10);
    // Serial.print(" with RSSI: ");
    // Serial.println(LoRa.packetRssi());  // 受信信号強度（RSSI）を表示
  }
}
