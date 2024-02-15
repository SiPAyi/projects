#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN pins
const byte address[6] = "00001";

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

// lx(roll)-a3 ly(pitch)-a4 rx(yaw)-a2 ry(throttle)-a1 voltage_divider-A5  swl-7, swr-8
int throttle_pin = A1;
int yaw_pin = A2;
int pitch_pin = A4;
int roll_pin = A3;
int pid_pin = A0;
int switch1 = 7;
int switch2 = 8;

void ResetData() {
  data.switch1 = 0;
  data.switch2 = 0;
  data.throttle = 0;  
  data.pitch = 0;     
  data.roll = 0;      
  data.yaw = 0;       
}

int status_led = 6;
int status = 0;

// for frequecy of execution
int time_step = 4;
double prev_time = millis();

void setup() {

  // display_setup();

  ResetData();

  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

  pinMode(6, OUTPUT);

  Serial.begin(9600);

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    // disp_radio_check(0);
    while (1) {}  // hold in infinite loop
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  disp_radio_check(1);
  Serial.println("radio connected");
 
  radio.stopListening();  // put radio in TX mode

  digitalWrite(status_led, 1);
  delay(200);
  digitalWrite(status_led, 0);
  delay(200);
  digitalWrite(status_led, 1);
  delay(200);
  // digitalWrite(status_led, 0);
  // delay(200);
}

void loop() {
  transmit_data();
  // receive_data();  
}