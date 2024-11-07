#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // initialize the LoRa module
  Serial.println("LoRa Receiver");
  while (1) {
    if (!LoRa.begin(868E6)) {  // LoRa communication 868 MHz
      Serial.println("Starting LoRa failed!");
    }
    else {
      Serial.println("Starting LoRa connection success!");
      break;
    }
    delay(1000);
  }

  // Set each pin
  // GND 3本目
  // 6 2本目 RED
  pinMode(6, OUTPUT);
  // 7 4本目 GREEN
  pinMode(7, OUTPUT);
  // 8 1本目 BLUE
  pinMode(8, OUTPUT);

  // Initialize all the digitalPins off
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void loop() {
  int packetSize = LoRa.parsePacket(); // Recieve LoRa packet
  if (packetSize) { // If it receives a LoRa packet

    String message; // Variable for the message that it receives
    while (LoRa.available()) {
      message = LoRa.readString();
    }

    // Switch

    switch (message[0]) {
      case '0': // 6 RED magnetic sensor on
        Serial.println("The door is closed. Someone is taking a shower");
        digitalWrite(6, HIGH); // 6 HIGH
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        break;

      case '1': // 8 BLUE magnetic sensor off and the temperature is more than 25 degrees
        Serial.println("The door is open. Someone forgot to close the door");
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH); // 8 HIGH
        break;
      
      case '2': // 7 GREEN magnetic sensor off and the temperature is less than 25 degrees
        Serial.println("The door is open. No one is there");
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH); // 7 HIGH
        digitalWrite(8, LOW);
        break;
      
      default:
        Serial.println("Value is unknown");
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        break;
    }
    delay(100); // delay 0.1 second
  }
}
