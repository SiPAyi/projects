void n20_setup() {
  int in1 = 5, in2 = 6, in3 = 7, in4 = 8;

  // for n20 motors
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
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

int minMax(int motor_speed) {
  int min = 0, max = 255;
  if (motor_speed > max) {
    motor_speed = max;
  } else if (motor_speed < min) {
    motor_speed = min;
  }
  return motor_speed;
}
