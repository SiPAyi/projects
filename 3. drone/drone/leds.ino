bool ledState = LOW;

void leds_setup()
{
  pinMode(green1, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green2, OUTPUT);
  digitalWrite(red, HIGH);
  Serial.println("settingup leds");
}

void led_output(int green2_output, int green1_output, int red_output)
{
  digitalWrite(green2, green2_output);
  digitalWrite(green1, green1_output);
  digitalWrite(red, red_output);
}

// Function to blink LED without blocking
void blinkLED(int pin, unsigned long interval, unsigned long led_prev_millis)
{
  unsigned long currentMillis = millis();

  if (currentMillis - led_prev_millis >= interval)
  {
    led_prev_millis = currentMillis;
    ledState = !ledState;
    digitalWrite(pin, ledState);
  }
}