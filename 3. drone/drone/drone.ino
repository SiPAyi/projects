// for voltage measuring function
int battery = A0;  // pin where voltage divider node is connected
int battery_level = 0;

// for radio communication, controller data-type
struct Signal {
  bool switch1;
  bool switch2;
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
  byte pid;
};
Signal data;

// pid controller
float instruction[4] = { 0, 0, 0, 30 };           // [Yaw (cardinal direction), Pitch (x), Roll (y), Throttle]
float measures[4] = { 0, 0, 0, 0 };              // [Yaw (cardinal direction), Pitch (x), Roll (y)]
int YAW = 0, PITCH = 1, ROLL = 2, THROTTLE = 3;  // for array indexing

// pid values
// int tp=3, ti=0.2, td=3; 
int tp=1.3, ti=0.04, td=18.0; 

float Kp[3] = { tp, tp, tp };  // P coefficients in that order : Yaw, Pitch, Roll
float Ki[3] = { ti, ti, ti };  // I coefficients in that order : Yaw, Pitch, Roll
float Kd[3] = { td, td, td };  // D coefficients in that order : Yaw, Pitch, Roll


// Status of Drone
#define STOPPED 0
#define STARTING 1
#define STARTED 2

// Throttle values for each motor
int motor_lf_throttle{ 0 },
  motor_lb_throttle{ 0 },
  motor_rf_throttle{ 0 },
  motor_rb_throttle{ 0 };

// for frequecy of execution
int time_step = 4;
double prev_time = millis();

// leds part
int green1 = 2, red = 3, green2 = 4, count = 0;
int radio_status_count = 0, led_status=0;

void setup() {
  // analogReference(INTERNAL);   // for battery reading
  Serial.begin(9600);
  Serial.println("Fligh Started");
  leds_setup(); // three leds i put on the drone will output the state it is in

  display_setup(); // need to implement it later or remove it

  kalman_gyro_setup();  // setuping gyro

  receiver_setup();

  setup_motors();

  // flight_start_test();

  // start_menu();
}

void loop() {

  if (millis() - prev_time >= time_step) {
    prev_time = millis();

    receive_data(); // * it shows that radio is connected in the serial monitor

    kalman_filtered_angles(); // ^ this means got the gyro values

    pidController();

    // Serial.print(measures[ROLL]);
    // Serial.print(",");
    // Serial.print(data.roll);
    // Serial.print("\t");
    // Serial.print(measures[PITCH]);
    // Serial.print(",");
    // Serial.print(data.pitch);
    // Serial.print("\t");
    // Serial.print(measures[YAW]);
    // Serial.print(",");
    // Serial.print(data.yaw);
    // Serial.print("\t");
    // Serial.println(data.throttle);

    // // next features to implement
    // transmit_data();
    // get_battery_level();
    // servoTest();
  }
}
