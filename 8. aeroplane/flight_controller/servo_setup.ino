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

  esc.writeMicroseconds(1050);
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
  int roll_left = minmax((max_roll - (data.roll - 124)), 0, 2 * max_roll);
  int roll_right = minmax((max_roll + (data.roll - 124)), 0, 2 * max_roll);
  int pitch = minmax((max_pitch + (data.pitch - 128)), 0, 2 * max_pitch);
  int yaw = minmax((max_yaw + (data.yaw - 129)), 0, 2*max_yaw);
  data.throttle -= 130;
  int throttle = map(data.throttle, 0, 128, 0, 180);

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

int minmax(int value, int min_value, int max_value) {
  if (value > max_value) {
    value = 90;
  } else if (value < min_value) {
    value = 0;
  }
  return value;
}

void servo_test() {
  for (int pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    esc.write(pos);   // tell servo to go to position in variable 'pos'
    roll_servo_left.write(pos);   // tell servo to go to position in variable 'pos'
    roll_servo_right.write(pos);  // tell servo to go to position in variable 'pos'
    pitch_servo.write(pos);       // tell servo to go to position in variable 'pos'
    yaw_servo.write(pos);         // tell servo to go to position in variable 'pos'
    delay(15);                    // waits 15 ms for the servo to reach the position
  }
  for (int pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    esc.write(pos);          // tell servo to go to position in variable 'pos'
    roll_servo_left.write(pos);          // tell servo to go to position in variable 'pos'
    roll_servo_right.write(pos);         // tell servo to go to position in variable 'pos'
    pitch_servo.write(pos);              // tell servo to go to position in variable 'pos'
    yaw_servo.write(pos);                // tell servo to go to position in variable 'pos'
    delay(15);                           // waits 15 ms for the servo to reach the position
  }
}

void stop_motors(){
    esc.write(0);
  roll_servo_left.write(45);
  roll_servo_right.write(45);
  pitch_servo.write(45);
  yaw_servo.write(45);
}