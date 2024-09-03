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
  radio.openWritingPipe(pipe);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.setRetries(3, 5); // Retry delay: 1500us, Retry count: 15
  radio.enableAckPayload();
  radio.stopListening(); // Set module as transmitter
}

void loop() {
  const char text[] = "Hello";
  if (radio.write(&text, sizeof(text))) {
    Serial.println("Message sent successfully");

    // Check for acknowledgment
    if (radio.isAckPayloadAvailable()) {
      char ackMessage[32] = "";
      radio.read(&ackMessage, sizeof(ackMessage));
      Serial.print("Acknowledgment received: ");
      Serial.println(ackMessage);
    } else {
      Serial.println("No acknowledgment received");
    }
  } else {
    Serial.println("Message sending failed");
  }
  delay(1000);
}
