// #define ENA 12
// #define IN_1 14
// #define IN_2 27
// #define IN_3 32
// #define IN_4 35
// #define ENB 34
// if the above one doesnt work
#define ENA 13
#define IN_1 12
#define IN_2 14
#define IN_3 27
#define IN_4 26
#define ENB 25



void motor_setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
}

void forward(int speed) {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_3, LOW);

  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_4, HIGH);

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void backward(int speed) {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_3, HIGH);

  digitalWrite(IN_2, LOW);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}