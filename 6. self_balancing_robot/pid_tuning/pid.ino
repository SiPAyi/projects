void pid_controller() {
  int error = (measures[1] > 0) ? measures[1] : -measures[1];
  int error_diff = prev_error - error;
  error_sum += error;

  pid_out = min_max(error * p + error_diff * d + error_sum * i);
  prev_error = error;

  if ((-45 < measures[1] < 0) || (measures[1] > 45)) {
    forward(pid_out);
    // Serial.println(pid_out);
  } else if ((0 < measures[1] < 45) || (measures[1] < -45)) {
    backward(pid_out);
    // Serial.println(-pid_out);
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