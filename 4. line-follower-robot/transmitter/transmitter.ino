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

// pins for pid tuning
int P_pin = A1;
int I_pin = A2;
int D_pin = A3;

int s_led = 4;


void setup() {
  pinMode(s_led, OUTPUT);

  Serial.begin(115200);

  receiver_setup();
  Serial.print("hello");

}

void loop() {
  transmit_data();
  // receive_data();
}

