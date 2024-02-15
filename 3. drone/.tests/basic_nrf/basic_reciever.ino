// this code failed to make connection
#include <SPI.h>
#include "RF24.h"

RF24 radio(7, 8);  // CE, CSN pins (customize these for your setup)

void setup() {
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0E1LL);  // Set the transmit address
  radio.setPALevel(RF24_PA_HIGH);       // Set the power level (adjust as needed)
  radio.startListening();

  Serial.begin(9600);
}

void loop() {
  const char text[32];
  if (radio.available()) {
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
  else{
    Serial.println("not available");
  }
  delay(1000);  // Send data every second
}
