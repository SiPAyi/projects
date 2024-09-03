#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the communication pipe
RF24 radio(9, 10); // CE, CSN

void setup() {
  Serial.begin(9600);
  Serial.println("Connecting to nrf module...");
  while (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    delay(500);
  }

  Serial.println("Found the nrf module");
  radio.openReadingPipe(1, pipe);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.enableDynamicPayloads();
  radio.enableAckPayload();
  radio.startListening(); // Set module as receiver
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.print("Received message: ");
    Serial.println(text);

    // Prepare acknowledgment payload
    const char ack[] = "Ack: Hello";
    radio.writeAckPayload(1, &ack, sizeof(ack));
    Serial.println("Acknowledgment sent");
  }
}
