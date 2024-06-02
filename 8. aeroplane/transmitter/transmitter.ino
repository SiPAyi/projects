#include <LiquidCrystal.h>
#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN pins
const byte address[6] = "00001";

struct Signal {
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
};
Signal data;

// lx(roll)-a0 ly(pitch)-a1 rx(yaw)-a2 ry(throttle)-a3 voltage_divider-A5  swl-7, swr-8
int throttle_pin = A0;
int yaw_pin = A1;
int pitch_pin = A2;
int roll_pin = A3;
int switch1 = 7;
int switch2 = 8;

void ResetData() {
  data.throttle = 0;
  data.pitch = 0;
  data.roll = 0;
  data.yaw = 0;
}

int status_led = 8;
int status = 0;

// for frequecy of execution
int time_step = 4;
double prev_time = millis();

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  // display_setup();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  lcd.clear();

  ResetData();

  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(8, OUTPUT);

  Serial.begin(9600);

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    lcd.clear();
    lcd.print("radio hardware");
    lcd.setCursor(0, 1);
    lcd.print("not responding");

    while (1) {}  // hold in infinite loop
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  Serial.println("radio connected");
  radio.stopListening();  // put radio in TX mode

  digitalWrite(status_led, 1);
  delay(200);
  digitalWrite(status_led, 0);
  delay(200);
  digitalWrite(status_led, 1);
  delay(200);
  digitalWrite(status_led, 0);
  delay(200);
}

void loop() {
  Serial.println(String() + "throttle: " + analogRead(throttle_pin) + "\tyaw: " + analogRead(yaw_pin) + "\troll: " + analogRead(roll_pin) + "\tpitch: " + analogRead(pitch_pin));
  transmit_data();
}

void transmit_data() {
  data.throttle = map(analogRead(throttle_pin), 0, 1023, 0, 255);
  data.yaw = map(analogRead(yaw_pin), 0, 1023, 0, 255);
  data.pitch = map(analogRead(pitch_pin), 0, 1023, 0, 255);
  data.roll = map(analogRead(roll_pin), 0, 1023, 0, 255);


  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(String() + "yaw:" + data.yaw);

  lcd.setCursor(8, 0);
  lcd.print(String() + "thr:" + data.throttle);

  lcd.setCursor(0, 1);
  lcd.print(String() + "rol:" + data.roll);

  lcd.setCursor(8, 1);
  lcd.print(String() + "pit:" + data.pitch);


  radio.write(&data, sizeof(Signal));
}