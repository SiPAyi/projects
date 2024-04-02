void n20_setup() {
  int in1 = 5, in2 = 6, in3 = 7, in4 = 8;

  // for n20 motors
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(2000);  // this delay is to connect huskylens
  Serial.println("n20 motors connected");
}

void n20_spin() {
  analogWrite(m1, motor_speed1);
  analogWrite(m2, motor_speed2);
}

void n20_stop() {
  analogWrite(m1, 0);
  analogWrite(m2, 0);
}

void n20_rescue_mode() {
  motor_speed1 = (int)(motor_values1[0] + motor_values1[1] + motor_values1[2] + motor_values1[3] + motor_values1[4])/5;
  motor_speed2 = (int)(motor_values2[0] + motor_values2[1] + motor_values2[2] + motor_values2[3] + motor_values2[4])/5;

  // motor speed saturating algo
  motor_speed1 = minMax(motor_speed1);
  motor_speed2 = minMax(motor_speed2);

  n20_spin();
}

int minMax(int motor_speed) {
  int min = 0, max = 255;
  if (motor_speed > max) {
    motor_speed = max;
  } else if (motor_speed < min) {
    motor_speed = min;
  }
  return motor_speed;
}
