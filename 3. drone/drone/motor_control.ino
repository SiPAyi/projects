#include <Servo.h>

Servo motor_lf;
Servo motor_rf;
Servo motor_lb;
Servo motor_rb;

int min_throttle = 35;

void setup_motors()
{
  // 1-9   3-6
  // 2-10  4-5
  motor_lf.attach(9);
  motor_lb.attach(10);
  motor_rf.attach(6);
  motor_rb.attach(5);

  led_output(1, 1, 1);
  stopMotors();
  Serial.println("settingup the motors");
  delay(1000);
  led_output(0, 0, 0);
}

void applyMotorSpeeds()
{
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
}

void stopMotors()
{
  motor_lf.write(min_throttle);
  motor_rf.write(min_throttle);
  motor_lb.write(min_throttle);
  motor_rb.write(min_throttle);
  delay(1000);
}

void servoTest()
{
  int speed = map(data.throttle, 0, 255, 0, 180);
  Serial.println(speed);
  display_speed(speed);

  motor_lf.write(speed);
  motor_rf.write(speed);
  motor_lb.write(speed);
  motor_rb.write(speed);
}

void rc_car_mode()
{
  int left_motor = data.throttle + data.yaw;
  int right_motor = data.throttle - data.yaw;

  // Cauculate new target throttle for each motor
  motor_lf_throttle = data.throttle + data.yaw;
  motor_lb_throttle = data.throttle + data.yaw;
  motor_rf_throttle = data.throttle - data.yaw;
  motor_rb_throttle = data.throttle - data.yaw;

  // Scale values to be within acceptable range for motors
  motor_lf_throttle = minMax(motor_lf_throttle, 30, 100);
  motor_rf_throttle = minMax(motor_rf_throttle, 30, 100);
  motor_lb_throttle = minMax(motor_lb_throttle, 30, 100);
  motor_rb_throttle = minMax(motor_rb_throttle, 30, 100);

  applyMotorSpeeds();
}