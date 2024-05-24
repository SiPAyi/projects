#include <Servo.h>

Servo motor1;
Servo motor2;

void motor_setup() {
  // for bldc motors
  motor1.attach(m1);
  motor2.attach(m2);

  Serial.println("motors attached bro");
  motor1.writeMicroseconds(1030);
  motor2.writeMicroseconds(1030);
  delay(1000);
  Serial.println("motors started bro");
}

// used with drone transmitter
// void move_vehicle() {
//   // int speed = map(data.throttle, 0, 255, 0, 100);
//   int m1_speed = 1030 + data.throttle + (data.yaw / 2) - 62;  // -124 because we have to set the middle value of the yaw position to zero
//   int m2_speed = 1030 + data.throttle - (data.yaw / 2) + 62;  // for data.yaw (0=straight,-124=left,  124=right)

//   m1_speed = min_max(m1_speed);
//   m2_speed = min_max(m2_speed);

//   spin_motors(m1_speed, m2_speed);

//   // for speed testing purpose
//   Serial.print("spinning motors at ");
//   Serial.print(data.throttle);
//   Serial.print(" + ");
//   Serial.print(data.yaw);
//   Serial.print("\t");
//   Serial.print(m1_speed);

//   Serial.print("\t | \t");

//   Serial.print(data.throttle);
//   Serial.print(" - ");
//   Serial.print(data.yaw);
//   Serial.print("\t");
//   Serial.println(m2_speed);
// }


void spin_motors(int m1, int m2) {
  motor_speed1 = min_max(motor_speed1);
  motor_speed2 = min_max(motor_speed2);

  motor1.writeMicroseconds(m1);
  motor2.writeMicroseconds(m2);
}

void stop_motors() {
  motor1.writeMicroseconds(1030);
  motor2.writeMicroseconds(1030);
}

void test_spin(int speed) {
  motor1.writeMicroseconds(speed);
  motor2.writeMicroseconds(speed);
}

int min_max(int motor_speed) {
  if (motor_speed > max_pwm) {
    motor_speed = max_pwm;
  } else if (motor_speed < min_pwm) {
    motor_speed = min=_pwm;
  }
  return motor_speed;
}
