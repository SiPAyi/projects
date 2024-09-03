// for radio communication, controller data-type
struct Signal {
  byte throttle;  // ly
  byte pitch;     // ry
  byte roll;      // rx
  byte yaw;       // lx
};
Signal data;

// leds part
int led = A4;
int radio_status_count = 0, led_status = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Fligh Started");

  motor_setup();
  receiver_setup();
  // delay(30000);
}

void loop() {
  // servo_test();
  receive_data();
  if (radio_status_count > 500) {
    stop_motors();
  }
}
