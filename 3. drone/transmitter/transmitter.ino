// 0:started, 1:setupMode, 2:idealMode, 3:altitudeHold,  4:sensorCalibMode, 5:PIDTuneMode, 6:RescueMode
int transmitter_status = 0;
#define setupMode 1
#define idealMode 2
#define altitudeHoldMode 3
#define sensorCalibMode 4
#define PIDTunerMode 5
#define RescueMode 6

// lx(roll)-a3 ly(pitch)-a4 rx(yaw)-a2 ry(throttle)-a1 voltage_divider-A5  swl-7, swr-8
int throttle_pin = A1;
int yaw_pin = A2;
int pitch_pin = A4;
int roll_pin = A3;
int pot_pin = A5;
int switch1 = 7;
int switch2 = 8;

int status_led = 6;
int status = 0;

// for frequecy of execution
int time_step = 4;
double prev_time = millis();

void setup()
{
  transmitter_status = setupMode;
  Serial.begin(9600);
  Serial.println("started the transmitter");

  display_setup();

  // for input and output
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  pinMode(status_led, OUTPUT); // led output

  transmitter_setup();
}

void loop()
{
  if (millis() - prev_time >= time_step)
  {
    prev_time = millis();
    switch (drone_status)
    {
    case setupMode:
      transmitter_status = ping_drone();
      break;
    case idealMode:
      int next_state = findNextState();
      transmitter_status = idealModeTransmitter(next_state);
      break;
    case altitudeHoldMode:
      transmitter_status = altitudeHoldModeTransmitter();
      break;

    case sensorCalibMode:
      // listen to the button inputs to select the mode they want
      sensor_calib_option_select();
      sensorCalibModeTransmitter();
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
