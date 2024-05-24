// for pid tuning
float p = 0.4219;
float i = 0.003;
float d = 0.4219;
int setpoint = 22;
int measures[2] = { 0, 0 };
int prev_error[2] = { 0, 0 }, error_sum[2] = { 0, 0 };
int pid_out[2] = { 0, 0 };
int middle_speed = 220;

int motor_speed1 = 255, motor_speed2 = 255;


// for frequecy of execution
int time_step = 4;
double prev_time = millis();
int count = 0;

int ir1 = A2, ir2 = A3;
int dir1 = 10, dir2 = 11;
int vcc=8, gnd=9;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(dir1, INPUT);
  pinMode(dir2, INPUT);

  pinMode(vcc, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(vcc, 1);
  digitalWrite(gnd, 0);
  motor_setup();
}

void loop() {
  if (millis() - prev_time >= time_step) {
    prev_time = millis();

    measures[0] = analogRead(ir1);
    measures[1] = analogRead(ir2);

    // pid_controller();

    Serial.println(String() + "ir1 = " + measures[0] + "\tir2 = " + measures[1] + "\tm1 = " + motor_speed1 + "\tm2 = " + motor_speed2);
    spin();
  }
}
