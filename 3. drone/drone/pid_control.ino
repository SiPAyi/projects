// motor pins on arduino
#define motor_lf 1
#define motor_rf 2
#define motor_lb 3
#define motor_rb 4

// ---------------- PID Variables ---------------------------------------
// Measured errors compared to target positions in order: [yaw, pitch, roll]
float errors[3];
// Error sums used for integral component of PID in order: [yaw, pitch, roll]
float error_sum[3] = { 0, 0, 0 };
// Previous errors used for derivative component of PID in order:
float previous_error[3] = { 0, 0, 0 };  // [yaw, pirch, roll]
float delta_err[3] = { 0, 0, 0 };       // Error deltas in that order   : Yaw, Pitch, Roll

// // pid values
// float Kp[3] = { 0.200, 0.05999999, 0.06500001 };       // P coefficients in that order : Yaw, Pitch, Roll
// float Ki[3] = { 0.020, 0.05999999, 0.06500001 };  // I coefficients in that order : Yaw, Pitch, Roll
// float Kd[3] = { 0, 0.002, 0.002 };         // D coefficients in that order : Yaw, Pitch, Roll

void calculateErrors() {
  errors[YAW] = instruction[YAW] - measures[YAW];
  errors[PITCH] = instruction[PITCH] - measures[PITCH];
  errors[ROLL] = instruction[ROLL] - measures[ROLL];
  Serial.print(measures[YAW]);
  Serial.print("\t");
  Serial.print(measures[PITCH]);
  Serial.print("\t");
  Serial.print(measures[ROLL]);
  Serial.print("\t");
  Serial.print(errors[YAW]);
  Serial.print("\t");
  Serial.print(errors[PITCH]);
  Serial.print("\t");
  Serial.print(errors[ROLL]);
  Serial.println("\t");

  // disp_measures();
}

void pidController() {
  float yaw_pid = 0;
  float pitch_pid = 0;
  float roll_pid = 0;

  // Take no action if there is no throttle to the motors
  // if (instruction[THROTTLE] > 0) {
  if (1) {
    calculateErrors();

    // Calculate sum of errors : Integral coefficients
    error_sum[YAW] += errors[YAW];
    error_sum[PITCH] += errors[PITCH];
    error_sum[ROLL] += errors[ROLL];

    // Calculate error delta : Derivative coefficients
    delta_err[YAW] = errors[YAW] - previous_error[YAW];
    delta_err[PITCH] = errors[PITCH] - previous_error[PITCH];
    delta_err[ROLL] = errors[ROLL] - previous_error[ROLL];

    // Save current error as previous_error for next time
    previous_error[YAW] = errors[YAW];
    previous_error[PITCH] = errors[PITCH];
    previous_error[ROLL] = errors[ROLL];

    // PID = e.Kp + ∫e.Ki + Δe.Kd
    // yaw_pid = (errors[YAW] * Kp[YAW]) + (error_sum[YAW] * Ki[YAW]) + (delta_err[YAW] * Kd[YAW]);
    yaw_pid = 0;
    pitch_pid = (errors[PITCH] * Kp[PITCH]) + (error_sum[PITCH] * Ki[PITCH]) + (delta_err[PITCH] * Kd[PITCH]);
    roll_pid = (errors[ROLL] * Kp[ROLL]) + (error_sum[ROLL] * Ki[ROLL]) + (delta_err[ROLL] * Kd[ROLL]);

    // Serial.print(pitch_pid);
    // Serial.print("\t");
    // Serial.print(roll_pid);
    // Serial.print("\t");

    // Cauculate new target throttle for each motor
    motor_lf_throttle = instruction[THROTTLE] - roll_pid + pitch_pid + yaw_pid;
    motor_rf_throttle = instruction[THROTTLE] + roll_pid + pitch_pid - yaw_pid;
    motor_lb_throttle = instruction[THROTTLE] - roll_pid - pitch_pid - yaw_pid;
    motor_rb_throttle = instruction[THROTTLE] + roll_pid - pitch_pid + yaw_pid;

    // Scale values to be within acceptable range for motors
    motor_lf_throttle = minMax(motor_lf_throttle, 30, 100);
    motor_rf_throttle = minMax(motor_rf_throttle, 30, 100);
    motor_lb_throttle = minMax(motor_lb_throttle, 30, 100);
    motor_rb_throttle = minMax(motor_rb_throttle, 30, 100);

    applyMotorSpeeds();
  }
}

float minMax(float value, float min_value, float max_value) {
  if (value > max_value) {
    value = max_value;
  } else if (value < min_value) {
    value = min_value;
  }

  return value;
}
