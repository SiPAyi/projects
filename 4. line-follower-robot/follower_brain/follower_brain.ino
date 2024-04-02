// bldc stuff not used now, because high speed, so i put #bldc at the end of the line

// for radio communication, controller data-type
struct Signal {
  int error;
  int m1;
  int m2;
  int P;
  int I;
  int D;
};
Signal data;

// leds part
int led = A3;

// for motors
int motor_speed1, motor_speed2, m1 = 3, m2 = 4;
int max_pwm = 1080, min_pwm = 1040;  // #blcdc

// for husky lens line output
int xOrigin = 0, yOrigin = 0, xTarget = 0, yTarget = 0;
int32_t error;
float line_length = 1.0;

// motor previous values for rescue operation
int motor_values1[5] = { 0, 0, 0, 0, 0 };
int motor_values2[5] = { 0, 0, 0, 0, 0 };

// PID constants
double Kp = 1.4;        // Proportional term
double Ki = 0.0000025;  // Integral term 0.0
double Kd = 1.1;        // Derivative term 1.0

// some what failed because at 2nd turn it stoped may be kd>kp
// double Kp = 1.3
// double Ki = 0.000003
// double Kd = 1.4

// failed
// double Kp = 1.3
// double Ki = 0.0000033333
// double Kd = 1.5

// good but at one sharp(3rd) turn it stoped
// Kp = 1.4
// Ki = 0.000003
// Kd = 1.3

// for no block
int noBlock = 0;

void setup() {
  husky_setup();
  Serial.begin(115200);

  n20_setup();
  // receiver_setup();

  // motor_setup(); //#blcdc
}

void loop() {
  // receive_data();

  find_coordinates();
  calculatePID(error);

  // // for test purpose only
  // motor_speed1 = 200;
  // motor_speed2 = 200;

  if (!noBlock) {
    n20_spin();
  } else {
    n20_rescue_mode();
    // n20_stop();
  }
  // n20_spin();

  Serial.println(String() + F("error: ") + error + F("\t line_length: ") + line_length + F("\tmotor1: ") + motor_speed1 + F("\tmotor2: ") + motor_speed2);
  // transmit_data();
}
