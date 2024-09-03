// 0:started, 1:setupMode, 2:idealMode, 3:altitudeHold,  4:sensorCalibMode, 5:PIDTuneMode, 6:RescueMode
int drone_status = 0;
#define setupMode 1
#define idealMode 2
#define altitudeHoldMode 3
#define sensorCalibMode 4
#define PIDTunerMode 5
#define RescueMode 6

// for voltage measuring function
int battery_level = 0;

// pid controller
float instruction[4] = {0, 0, 0, 30};           // [Yaw (cardinal direction), Pitch (x), Roll (y), Throttle]
float measures[4] = {0, 0, 0, 0};               // [Yaw (cardinal direction), Pitch (x), Roll (y)]
int YAW = 0, PITCH = 1, ROLL = 2, THROTTLE = 3; // for array indexing

// pid values
// int tp=3, ti=0.2, td=3;
int tp = 18, ti = 0.04, td = 18.0;

float Kp[3] = {tp, tp, tp}; // P coefficients in that order : Yaw, Pitch, Roll
float Ki[3] = {ti, ti, ti}; // I coefficients in that order : Yaw, Pitch, Roll
float Kd[3] = {td, td, td}; // D coefficients in that order : Yaw, Pitch, Roll

// Throttle values for each motor
int motor_lf_throttle{0},
    motor_lb_throttle{0},
    motor_rf_throttle{0},
    motor_rb_throttle{0};

// for frequecy of execution
int time_step = 4;
double prev_time = millis();

// leds part
int green1 = 2, red = 3, green2 = 4, count = 0;
int radio_status_count = 0, led_status = 0;

void setup()
{
  drone_status = setupMode;
  // analogReference(INTERNAL);   // for battery reading

  // for debugin purpose
  Serial.begin(9600);
  Serial.println("Fligh Started");

  leds_setup(); // three leds i put on the drone will output the state it is in

  gyro_setup();

  baro_meter_setup();

  setup_motors();

  receiver_setup();
}

void loop()
{

  if (millis() - prev_time >= time_step)
  {
    prev_time = millis();
    switch (drone_status)
    {
    case setupMode:
      drone_status = wait_for_ping();
      Serial.println("established a connection to transmitter");
      Serial.println("now in idealMode(S2)");
      break;
    case idealMode:
      gyro_without_bias();
      drone_status = idealModeReceiver();
      break;
    case altitudeHoldMode:
      gyro_without_bias();
      drone_status = altitudeHoldModeTransmitter();
      pidController();
      break;

    case sensorCalibMode:
      sensorCalibModeReceiver();
      break;

    case PIDTunerMode:
      //
      break;

    case RescueMode:
      //
      break;
    }
  }
}
