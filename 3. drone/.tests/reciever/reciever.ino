#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int ch_width_1 = 0;
int ch_width_2 = 0;
int ch_width_3 = 0;
int ch_width_4 = 0;

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;

struct Signal {
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
};

Signal data;

const uint64_t pipeIn = 0xE9E8F0F0E1LL;
RF24 radio(7, 8);

void ResetData() {
  // Define the inicial value of each data input.
  // The middle position for Potenciometers. (254/2=127)
  data.throttle = 127;  // Motor Stop
  data.pitch = 127;     // Center
  data.roll = 127;      // Center
  data.yaw = 127;       // Center
}

void throttle() {
  // spin all motors at the same speed
  ch_width = map(data.yaw, 0, 255, 1000, 2000);

  // Write the PWM signal
  ch1.writeMicroseconds(ch_width);
  ch2.writeMicroseconds(ch_width);
  ch3.writeMicroseconds(ch_width);
  ch4.writeMicroseconds(ch_width);
}

void pitch() {
  // side motors spin with slower speed
  ch_width = map(data.yaw, 0, 255, 1000, 2000);

  // Write the PWM signal
  ch1.writeMicroseconds(ch_width);
  ch2.writeMicroseconds(ch_width);
  ch3.writeMicroseconds(ch_width);
  ch4.writeMicroseconds(ch_width);
}

void roll() {
  // front and back motors speed changes

  ch_width = map(data.yaw, 0, 255, 1000, 2000);

  // Write the PWM signal
  ch1.writeMicroseconds(ch_width);
  ch2.writeMicroseconds(ch_width);
  ch3.writeMicroseconds(ch_width);
  ch4.writeMicroseconds(ch_width);
}

void yaw() {
  // diagonal motor speeds changes

  ch_width = map(data.yaw, 0, 255, 1000, 2000);

  // Write the PWM signal
  ch1.writeMicroseconds(ch_width);
  ch2.writeMicroseconds(ch_width);
  ch3.writeMicroseconds(ch_width);
  ch4.writeMicroseconds(ch_width);
}


void setup() {
  //Set the pins for each PWM signal
  ch1.attach(2);
  ch2.attach(3);
  ch3.attach(4);
  ch4.attach(5);

  //Configure the NRF24 module
  ResetData();
  radio.begin();
  radio.openReadingPipe(1, pipeIn);

  radio.startListening();  //start the radio comunication for receiver
}

unsigned long lastRecvTime = 0;

void recvData() {
  while (radio.available()) {
    radio.read(&data, sizeof(Signal));
    lastRecvTime = millis();  // receive the data |
  }
}

void loop() {
  recvData();
  unsigned long now = millis();
  if (now - lastRecvTime > 1000) {
    ResetData();  // Signal lost.. Reset data |
  }

  ch_width_1 = map(data.throttle, 0, 255, 1000, 2000);
  ch_width_2 = map(data.pitch, 0, 255, 1000, 2000);
  ch_width_3 = map(data.roll, 0, 255, 1000, 2000);
  ch_width_4 = map(data.yaw, 0, 255, 1000, 2000);


  // Write the PWM signal
  ch1.writeMicroseconds(ch_width_1);
  ch2.writeMicroseconds(ch_width_2);
  ch3.writeMicroseconds(ch_width_3);
  ch4.writeMicroseconds(ch_width_4);
}