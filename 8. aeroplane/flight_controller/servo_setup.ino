#include <Servo.h>

Servo esc;
Servo roll_servo_left;
Servo roll_servo_right;
Servo pitch_servo;
Servo yaw_servo;

// throttle values setting
int max_pitch = 45, min_pitch = -45;
int max_yaw = 45, min_yaw = -45;
int max_roll = 45, min_roll = -45;

void motor_setup() {
  esc.attach(3);
  roll_servo_left.attach(5);
  roll_servo_right.attach(6);
  pitch_servo.attach(9);
  yaw_servo.attach(10);

  esc.write(0);
  roll_servo_left.write(max_roll);
  roll_servo_right.write(max_roll);
  pitch_servo.write(max_pitch);
  yaw_servo.write(max_yaw);
  Serial.print("connecting the motors");
  for (int i = 0; i <= 255; i++) {
    analogWrite(A4, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(A4, i);
    delay(10);
  }
}

void motor_control() {
  int roll_left = minmax(max_roll - (data.roll - 124));
  int roll_right = minmax(max_roll + (data.roll - 124));
  int pitch = minmax(max_pitch + (data.pitch - 128));
  int yaw = minmax(max_yaw + (data.yaw - 129));
  data.throttle -= 130;
  int throttle = map(data.throttle, 0, 128, 0, 100);

  esc.write(throttle);
  roll_servo_left.write(roll_left);
  roll_servo_right.write(roll_right);
  pitch_servo.write(pitch);
  yaw_servo.write(yaw);

  Serial.print("\t throttle : ");
  Serial.print(throttle);
  Serial.print("\t roll_left : ");
  Serial.print(roll_left);
  Serial.print("\t roll_right : ");
  Serial.print(roll_right);
  Serial.print("\t pitch : ");
  Serial.print(pitch);
  Serial.print("\t yaw : ");
  Serial.println(yaw);
}

int minmax(int value) {
  if (value > 90) {
    value = 90;
  } else if (value < 0) {
    value = 0;
  }
  return value;
}

void test(){
  int speed = data.throttle+950;
   esc.writeMicroseconds(speed);
   Serial.println(speed);
}