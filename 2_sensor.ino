#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_AMG88xx.h>  // AMG8833センサーのライブラリを追加

Adafruit_AMG88xx amg;          // AMG8833のオブジェクトを宣言
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];  // 8x8の温度データを格納する配列
const int sensorPin = A2;  // アナログピンを指定

void setup() {
  Serial.begin(9600);
  while (!Serial);
  while (!amg.begin(0x68)){
      Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
      delay(100);
    }

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
  //tempreture
  amg.readPixels(pixels);
    int tem_sum = 0;
    int tem_mean;

  // 8x8の温度データを表示
  for (int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++) {
      // Serial.print(pixels[i], 1);  // 小数点以下1桁で温度を表示
      tem_sum += pixels[i];
      // Serial.print("\t");

      // 8ピクセルごとに改行
      // if ((i + 1) % 8 == 0) {
          // Serial.println();
      // }
  }
  tem_mean = tem_sum / 64;
  Serial.print(tem_mean);
  if(tem_mean > 25){
    Serial.print("people inside");
  }
  Serial.println();
  
  //magnetic

  Serial.println("");
  int sensorValue = analogRead(sensorPin);  // アナログ信号を読み取る
  
  Serial.println("Sending packet..."); // (Serial)

  Serial.println(sensorValue);  // 読み取った値を表示 (Serial)

  LoRa.beginPacket(); // LoRaパケットの開始 (LoRa begin)

  if (sensorValue >= 600 || sensorValue <= 400) { // Threshold level 
    Serial.println("HIGHT\nThe door is closed"); // (Serial)
    LoRa.print(1); // (LoRa)
  } else {
    Serial.println("LOW\nThe door is open"); // (Serial)
    if(tem_mean > 25) {
      Serial.println("maybe people inside");
      LoRa.print(2); // (LoRa)
    }else{
      LoRa.print(0); // (LoRa)
    }
    // LoRa.print(0); // (LoRa)
  }

  LoRa.endPacket();  // パケットを送信完了 (LoRa end)

  delay(1000);
}