#include <SPI.h>
#include <RF24.h>
#include <Servo.h>
Servo esc;

RF24 radio(D4, D8);  // CE, CSN pins
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
  radio.openReadingPipe(1, address);
  radio.startListening();

  pinMode(D0, OUTPUT);
  esc.attach(D0);
  esc.write(0);
}

void loop() {
  if (radio.available()) {
    int throttle;
    radio.read(&throttle, sizeof(throttle));
    throttle = (throttle > 50) ? (throttle - 50) : 0;
    Serial.println(3 * throttle);
    esc.write(3 * throttle);

    // radio.read(&data, sizeof(Signal));
    // Serial.print("throttle : ");
    // Serial.print(data.throttle);
    // Serial.print("  yaw : ");
    // Serial.print(data.yaw);
    // Serial.print("  pitch : ");
    // Serial.print(data.pitch);
    // Serial.print("  roll : ");
    // Serial.println(data.roll);
  }
}
