#include<Servo.h>
Servo esc;
// angle 0 to 180 for a servo to map the esc throttle from 0 to 100%

int vrx = A0;
int x;

void setup() {
  pinMode(D0, OUTPUT);
  esc.attach(D0);
  esc.write(0);

  pinMode(vrx, INPUT);
  Serial.begin(9600);
  Serial.println("printing joystick values: ");
}

void loop() {
  x = analogRead(vrx);
  // Serial.println(x);
  int angle = map(x, 0, 1023, 0, 150);
  esc.write(angle);
  Serial.println(angle);
  delay(200);
}
