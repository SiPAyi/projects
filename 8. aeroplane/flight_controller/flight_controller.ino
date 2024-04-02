// for radio communication, controller data-type
struct Signal {
  bool switch1;
  bool switch2;
  byte pitch;     // ry
  byte throttle;  // ly
  byte yaw;       // lx
  byte roll;      // rx
  byte pid;
};
Signal data;

// leds part
int led = A4;
int radio_status_count = 0, led_status = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Fligh Started");

  motor_setup();
  receiver_setup();
}

void loop() {
  receive_data();

  // motor_control();

  test();

  // Serial.print("\t roll : ");
  // Serial.print(data.roll);
  // Serial.print("\t pitch : ");
  // Serial.print(data.pitch);
  // Serial.print("\t yaw : ");
  // Serial.print(data.yaw);
  // Serial.print("\t throttle : ");
  // Serial.print(data.throttle);
  // Serial.print("\t pid : ");
  // Serial.println(data.pid);
}
