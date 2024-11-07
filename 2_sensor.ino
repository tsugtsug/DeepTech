#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;          // AMG8833 Object
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];  // Array for the temperature data 8x8
const int sensorPin = A2;  // PIN A2

void setup() {
  Serial.begin(9600);
  while (!Serial);
  while (!amg.begin(0x68)){ //　Address of capteur infrarouge
      Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
      delay(100);
  }

  // initialize the LoRa module
  Serial.println("LoRa Sender");
  while (1) {
    if (!LoRa.begin(868E6)) { // LoRa communication 868 MHz
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

  // --- Temperature Part ---
  amg.readPixels(pixels);
  int tem_sum = 0;
  int tem_mean;

  // Calculation of temperature mean
  for (int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++) {
      tem_sum += pixels[i];
  }

  tem_mean = tem_sum / 64;
  Serial.print("Temperature : ");
  Serial.println(tem_mean);
  // If the temperature is over 25 degrees, detecg someone in the room
  if(tem_mean > 25){
    Serial.println("Detect someone in the room !");
  }
  
  // --- Magnetic part ---

  Serial.println("");
  int sensorValue = analogRead(sensorPin);  // Capturing by magnetic capture
  
  Serial.println("Sending packet..."); // (Serial)

  Serial.print("Magnetic sensor value : ");  // Print magnetic value (Serial)
  Serial.println(sensorValue);

  // --- LoRa Part ---

  LoRa.beginPacket(); // LoRa begin

  if (sensorValue >= 250 && sensorValue <= 450) { // Threshold level 
    Serial.println("The door is closed"); // (Serial)
    LoRa.print(0); // CLOSE if magnetic sensor on, send "0"
  } else {
    Serial.println("The door is open"); // (Serial)
    if(tem_mean >= 25) {
      Serial.println("Someone forgot to close the door");
      LoRa.print(1); // CLOSE if magnetic sensor off and the temperature is more than 25 degrees, send "1"
    }else{
      Serial.println("No one there");
      LoRa.print(2); // OPEN if magnetic sensor off and the temperature is less than 25 degrees, send "2"
    }
  }

  LoRa.endPacket(); // LoRa end

  delay(1000); // delay 1 second
}
