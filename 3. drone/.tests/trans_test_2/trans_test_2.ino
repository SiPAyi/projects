#include <SPI.h>
#include <RF24.h>

RF24 radio(8, 10);  // CE, CSN pins
const byte address[6] = "00001";

int state, throttle, roll, pitch, yaw;

void ResetData() {
  state = 0;
  throttle = 0;  // Motor Stop (254/2=127)(Signal lost position)
  pitch = 0;     // Center (Signal lost position)
  roll = 0;      // Center(Signal lost position)
  yaw = 0;       // Center (Signal lost position )
}

void setup() {
  ResetData();

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  
  Serial.begin(9600);
  Serial.println("started transmitting");
}

void loop() {
  state = digitalRead(3);
  throttle = map(analogRead(A3), 0, 1023, 0, 100);
  roll = map(analogRead(A1), 0, 1023, 0, 100);   // "true" or "false" for servo direction
  pitch = map(analogRead(A0), 0, 1023, 0, 100);  // "true" or "false" for servo direction
  yaw = map(analogRead(A2), 0, 1023, 0, 100);    // "true" or "false" for servo direction


  radio.write(&throttle, sizeof(int));

  Serial.print("  throttle : ");
  Serial.println(throttle);
}
