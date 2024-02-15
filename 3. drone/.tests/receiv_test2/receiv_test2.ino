#include <SPI.h>
#include <RF24.h>
#include<Servo.h>
Servo motor;

RF24 radio(D8, D4);  // CE, CSN pins
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

  motor.attach(D0);

  radio.begin();
  radio.openReadingPipe(1, address);
  radio.startListening();

  Serial.begin(9600);
  Serial.println("I'm listening bro");
}

void loop() {
  if (radio.available()) {
    radio.read(&throttle, sizeof(int));

    Serial.println("hey bro i got: ");
    Serial.print("  throttle : ");
    Serial.println(throttle);
    // int signal = map(throttle, 0, 100, 1000, 2000);
    // motor.write(100);
    // Serial.print("  yaw : ");
    // Serial.print(data.yaw);
    // Serial.print("  roll : ");
    // Serial.print(data.roll);
    // Serial.print("  pitch : ");
    // Serial.println(data.pitch);
  }
}
