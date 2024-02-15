#include <SPI.h>
#include <RF24.h>

RF24 radio(8, 10);  // CE, CSN pins
const byte address[6] = "00001";

struct Signal {
  bool state;
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
};

Signal data;

void ResetData() {
  data.state = 0;
  data.throttle = 0;  // Motor Stop (254/2=127)(Signal lost position)
  data.pitch = 0;     // Center (Signal lost position)
  data.roll = 0;      // Center(Signal lost position)
  data.yaw = 0;       // Center (Signal lost position )
}


void setup() {
  ResetData();

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
}

void loop() {

  // int throttle = map(analogRead(A3), 0, 1023, 0, 100);
  // radio.write(&throttle, sizeof(throttle));
  // Serial.println(throttle);
  
  data.throttle = map(analogRead(A3), 0, 1023, 0, 100);
  data.roll = map(analogRead(A1), 0, 1023, 0, 100);   // "true" or "false" for servo direction
  data.pitch = map(analogRead(A0), 0, 1023, 0, 100);  // "true" or "false" for servo direction
  data.yaw = map(analogRead(A2), 0, 1023, 0, 100);    // "true" or "false" for servo direction

  radio.write(&data, sizeof(Signal));

  Serial.print("throttle : ");
  Serial.print(data.throttle);
  Serial.print("  yaw : ");
  Serial.print(data.yaw);
  Serial.print("  pitch : ");
  Serial.print(data.pitch);
  Serial.print("  roll : ");
  Serial.println(data.roll);
}
