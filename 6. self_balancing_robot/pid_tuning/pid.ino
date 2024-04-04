void pid_controller() {
  int error = (measures > 0) ? measures : -measures;
  int error_diff = prev_error - error;
  error_sum += error;

  pid_out = min_max(error * p + error_diff * d + error_sum * i);
  prev_error = error;

  if (measures > 0) {
    forward(pid_out);
    Serial.println(pid_out);
  } else {
    backward(pid_out);
    Serial.println(-pid_out);
  }
}

int min_max(int value){
  if(value>255){
    value = 255;
  }
  else if(value < 0){
    value = 0;
  }
  return value;
}