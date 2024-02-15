void pid_controller() {
  read_sensors();
  int error1 = ir_out1 - ir_center1;
  int error2 = ir_center2 - ir_out2;
  error = error1 + error2;
  error_sum += error;
  error_diff = prev_error - error;
  pid_out = kp * error + ki * error_sum + kd * error_diff;
  prev_error = error;

  // Serial.print(error1); Serial.print("\t");
  // Serial.print(error2); Serial.print("\t");
  // Serial.println(pid_out);


  motor_speed1 = 1060 - pid_out;
  motor_speed2 = 1060 + pid_out;

  // Serial.print("\t ir_out1\t");
  // Serial.print(ir_out1);
  // Serial.print("\t ir_out2\t");
  // Serial.print(ir_out2);
  // Serial.print("\t ir_out1 + ir_out2\t");
  // Serial.println(ir_out1 + ir_out2);

  if (ir_out1 + ir_out2 <= 60) {
    motor_speed1 = 1030;
    motor_speed2 = 1030;
  } else {
    motor_speed1 = min_max(motor_speed1);
    motor_speed2 = min_max(motor_speed2);
  }

  Serial.print("\t motor_speed1\t");
  Serial.print(motor_speed1);
  Serial.print("\t motor_speed2\t");
  Serial.println(motor_speed2);

  spin_motors(motor_speed1, motor_speed2);
}
