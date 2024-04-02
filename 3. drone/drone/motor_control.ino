#include <Servo.h>

Servo motor_lf;
Servo motor_rf;
Servo motor_lb;
Servo motor_rb;


void setup_motors() {
  // 1-9   3-6
  // 2-10  4-5
  motor_lf.attach(9);
  motor_lb.attach(10);
  motor_rf.attach(6);
  motor_rb.attach(5);

  stopMotors();
  Serial.println("settingup the motors");
  stopMotors();
  motor_setup_indication();
}

void applyMotorSpeeds() {
  motor_lf.write(motor_lf_throttle);
  motor_rf.write(motor_rf_throttle);
  motor_lb.write(motor_lb_throttle);
  motor_rb.write(motor_rb_throttle);


  // Serial.print(motor_lf_throttle);
  // Serial.print("\t");
  // Serial.print(motor_rf_throttle);
  // Serial.print("\t");
  // Serial.print(motor_lb_throttle);
  // Serial.print("\t");
  // Serial.println(motor_rb_throttle);

  display_motor_speed();
}

void stopMotors() {
  motor_lf.write(35);
  motor_rf.write(35);
  motor_lb.write(35);
  motor_rb.write(35);
  delay(2000);
}

void servoTest() {
  int speed = map(data.pid, 0, 255, 0, 180);
  Serial.println(speed);
  display_speed(speed);

  motor_lf.write(speed);
  motor_rf.write(speed);
  motor_lb.write(speed);
  motor_rb.write(speed);
}
