int ir1 = A0, ir2 = A1, status_led = A5;
int ir_out1 = 0, ir_out2 = 0;

// for calibration
int total_readings = 100;
float ir_sum1, ir_sum2, ir_center1, ir_center2;

// for pid
int error = 0, prev_error = 0, error_sum = 0, error_diff = 0;
float kp = 1, ki = 0.1, kd = 1;
int max_pwm = 1080, min_pwm = 1030, pid_out;

// for motors
int motor_speed1, motor_speed2;

void setup() {
  Serial.begin(9600);
  qtr_calibration();
  // // i got this values from manual calibration
  // ir_center1 = 43;
  // ir_center2 = 37;
}

void loop() {
  read_sensors();
  pid_controller();
}
