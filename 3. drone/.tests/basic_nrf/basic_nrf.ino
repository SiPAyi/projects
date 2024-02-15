// // this code failed to make connection
// #include <SPI.h>
// #include "RF24.h"

// RF24 radio(9, 10);  // CE, CSN pins (customize these for your setup)

// void setup() {
//   radio.begin();
//   radio.openWritingPipe(0xF0F0F0E1LL); // Set the transmit address
//   radio.setPALevel(RF24_PA_HIGH); // Set the power level (adjust as needed)

//   Serial.begin(9600);
// }

// void loop() {
//   const char text[32] = "Hello, NRF!";
//   radio.write(&text, sizeof(text));
//   Serial.println("data sent successfully");
//   delay(1000); // Send data every second
// }
