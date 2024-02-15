// need a way to test wether the transmission is successful or not
void transmit_data() {
  // data.switch1 = digitalRead(switch1);
  // data.switch2 = digitalRead(switch2);
  data.throttle = map(analogRead(throttle_pin), 0, 1023, 0, 255);
  data.yaw = map(analogRead(yaw_pin), 0, 1023, 0, 255);
  data.pitch = map(analogRead(pitch_pin), 0, 1023, 0, 255);
  data.roll = map(analogRead(roll_pin), 0, 1023, 0, 255);
  data.pid = map(analogRead(pid_pin), 0, 1023, 0, 255);



  radio.write(&data, sizeof(Signal));

  // disp_measures();

  // Serial.print("\t switch1 : ");
  // Serial.print(data.switch1);
  // Serial.print("\t switch : ");
  // Serial.print(digitalRead(7));

  Serial.print("\t roll : ");
  Serial.print(data.roll);
  Serial.print("\t pitch : ");
  Serial.print(data.pitch);
  Serial.print("\t yaw : ");
  Serial.print(data.yaw);
  Serial.print("\t throttle : ");
  Serial.print(data.throttle);
  Serial.print("\t pid : ");
  // Serial.println(map(data.pid, 0, 255, 0, 180));
  Serial.println((float)data.pid*12/1000, 6);
  
}