int led_state = 0;

void toggle_led() {  // blinks every half second
  digitalWrite(LED_BUILTIN, !led_state);
  delay(500);
}

void wifi_connected_indication() {
  digitalWrite(LED_BUILTIN, 1);
  delay(250);
  digitalWrite(LED_BUILTIN, 0);
  delay(250);

  digitalWrite(LED_BUILTIN, 1);
  delay(250);
  digitalWrite(LED_BUILTIN, 0);
  delay(250);

  digitalWrite(LED_BUILTIN, 1);
  delay(250);
  digitalWrite(LED_BUILTIN, 0);
  delay(250);

  digitalWrite(LED_BUILTIN, 1);
  delay(1000);
  digitalWrite(LED_BUILTIN, 0);
  delay(250);

  digitalWrite(LED_BUILTIN, 1);
}