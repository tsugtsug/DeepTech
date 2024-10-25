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
  // GND 3本目
  // 6 2本目 
  pinMode(6, OUTPUT);
  // 7 4本目
  pinMode(7, OUTPUT);

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
      // GREEN
      Serial.println("open");
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
    } else if (message == "1") {
      // RED
      Serial.println("close");
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
    } else {
      Serial.println("error" + message);
    }

    delay(10);
    // Serial.print(" with RSSI: ");
    // Serial.println(LoRa.packetRssi());  // 受信信号強度（RSSI）を表示
  }
}
