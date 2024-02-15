#include <Servo.h>

Servo motor1;
Servo motor2;

void motor_setup() {
  motor1.attach(4);
  motor2.attach(5);

  motor1.writeMicroseconds(1030);
  motor1.writeMicroseconds(1030);
}

void spin_motors(int m1, int m2) {
  motor1.writeMicroseconds(m1);
  motor1.writeMicroseconds(m2);
}