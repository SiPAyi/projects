#define ENA A1
#define IN_1 2
#define IN_2 3
#define IN_3 4
#define IN_4 5
#define ENB A0


void motor_setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, motor_speed1);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, motor_speed2);
}

void spin() {
  analogWrite(ENA, motor_speed1);
  analogWrite(ENB, motor_speed2);
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