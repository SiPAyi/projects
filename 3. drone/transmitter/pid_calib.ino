int roll = 0, pitch = 0, yaw = 0, throttle = 0;

void send_pid_values() {

  if (Serial.available()) {
    // Read the incoming string until a newline character is received
    String message = Serial.readStringUntil('\n');

    // Split the string into individual variables
    roll = message.substring(0, message.indexOf(',')).toInt();
    message.remove(0, message.indexOf(',') + 1);

    pitch = message.substring(0, message.indexOf(',')).toInt();
    message.remove(0, message.indexOf(',') + 1);

    yaw = message.substring(0, message.indexOf(',')).toInt();
    message.remove(0, message.indexOf(',') + 1);

    throttle = message.toInt();

    // Reset the message buffer
    message = "";

    data.roll = roll;
    data.pitch = pitch;
    data.yaw = yaw;
    data.throttle = throttle;

    radio.write(&data, sizeof(Signal));
    // to know the status
    digitalWrite(status_led, 1);
    delay(200);
    digitalWrite(status_led, 0);
    delay(200);
  } else {
    data.roll = roll;
    data.pitch = pitch;
    data.yaw = yaw;
    data.throttle = throttle;

    radio.write(&data, sizeof(Signal));
    // to know the status
    digitalWrite(status_led, 1);
    delay(500);
    digitalWrite(status_led, 0);
    delay(500);
  }
}