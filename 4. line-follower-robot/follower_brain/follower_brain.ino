// for radio communication, controller data-type
struct Signal {
  bool switch1;
  bool switch2;
  int throttle;
  int pitch;
  int roll;
  int yaw;
  int P;
  int I;
  int D;
};
Signal data;

// leds part
int led = A3;

// for motors
int motor_speed1, motor_speed2;
int max_pwm = 1090, min_pwm = 1030;

// for husky lens line output
int xOrigin = 0, yOrigin = 0, xTarget = 0, yTarget = 0;
int32_t error;

void setup() {
  Serial.begin(9600);
  husky_setup();

  motor_setup();
  // receiver_setup();
}

void loop() {
  find_coordinates();

  double pid_out = calculatePID(error);

  // motor mixing algorithm
  motor_speed1 = 1050 - pid_out;
  motor_speed2 = 1050 + pid_out;
  
  Serial.println(String() + F("error: ") + error + F("\tmotor1: ") + motor_speed1 + F("\tmotor1: ") + motor_speed2);
  // spin_motors(motor_speed1, motor_speed2);
}
