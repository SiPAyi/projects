void pid_controller() {
  // pid out 1
  int error1 = measures[0] - setpoint;
  int error_diff1 = prev_error[0] - error1;
  error_sum[0] += error1;

  pid_out[0] = min_max(error1 * p + error_diff1 * d + error_sum[0] * i);
  prev_error[0] = error1;

  // pid out 1
  int error2 = measures[1] - setpoint;
  int error_diff2 = prev_error[1] - error2;
  error_sum[1] += error2;

  pid_out[1] = min_max(error2 * p + error_diff2 * d + error_sum[1] * i);
  prev_error[1] = error1;

  if (digitalRead(dir1)) {
    motor_speed1 = min_max(middle_speed + pid_out[0]);
    motor_speed2 = min_max(middle_speed - pid_out[0]);
  } else if (digitalRead(dir2)) {
    motor_speed1 = min_max(middle_speed - pid_out[0]);
    motor_speed2 = min_max(middle_speed + pid_out[0]);
  } else {
    motor_speed1 = middle_speed;
    motor_speed2 = middle_speed;
  }
}

int min_max(int value) {
  if (value > 255) {
    value = 255;
  } else if (value < 0) {
    value = 0;
  }
  return value;
}