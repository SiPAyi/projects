void leds_setup() {
  pinMode(green1, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green2, OUTPUT);
  digitalWrite(red, HIGH);
  Serial.println("settingup leds");
}

void blink_eyes() {
  digitalWrite(red, LOW);
  digitalWrite(green1, HIGH);
  digitalWrite(green2, HIGH);
  delay(100);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  delay(100);
}

void open_eyes() {
  digitalWrite(green1, HIGH);
  digitalWrite(green2, HIGH);
  digitalWrite(red, LOW);
}

void close_eyes() {
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(red, LOW);
}

void motor_setup_indication() {
  int led_delay = 100;
  for (int i = 0; i < 3; i++) {
    digitalWrite(green2, HIGH);
    delay(led_delay);
    digitalWrite(red, HIGH);
    delay(led_delay);
    digitalWrite(green1, HIGH);
    delay(led_delay);
    digitalWrite(green2, LOW);
    delay(led_delay);
    digitalWrite(red, LOW);
    delay(led_delay);
    digitalWrite(green1, LOW);
    delay(led_delay);
  }
}