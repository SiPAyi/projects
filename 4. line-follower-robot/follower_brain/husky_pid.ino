// PID variables
double integral = 0;
double lastError = 0;

// Function to calculate PID control signal
void calculatePID(int32_t error) {
  // Proportional term
  double P = Kp * error;

  // Integral term
  integral += error;
  double I = Ki * integral;

  // Derivative term
  double derivative = error - lastError;
  double D = Kd * derivative;

  // Total control signal
  double output = P + I + D;

  // Update last error for next iteration
  lastError = error;

  // motor mixing algorithm
  // motor_speed1 = 1060 - output; // #bldc
  // motor_speed2 = 1060 + output; // #bldc
  motor_speed1 = 150 + 50 * (line_length / 240) - output;
  motor_speed2 = 150 + 50 * (line_length / 240) + output;

  // motor_speed1 = 130 + 60 * (line_length / 190) - output;
  // motor_speed2 = 130 + 60 * (line_length / 190) + output;

  // motor speed saturating algo
  motor_speed1 = minMax(motor_speed1);
  motor_speed2 = minMax(motor_speed2);

  // the below code is not used for now
  // for rescue mode operation we need to average these values to get the motor speed
  motor_values1[0] = motor_values1[1];
  motor_values1[1] = motor_values1[2];
  motor_values1[2] = motor_values1[3];
  motor_values1[3] = motor_values1[4];
  motor_values1[4] = motor_speed1;

  motor_values2[0] = motor_values2[1];
  motor_values2[1] = motor_values2[2];
  motor_values2[2] = motor_values2[3];
  motor_values2[3] = motor_values2[4];
  motor_values2[4] = motor_speed2;
}
