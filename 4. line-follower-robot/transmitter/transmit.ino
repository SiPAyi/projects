#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE, CSN pins (customize these for your setup)
const byte address[6] = "00001";

void ResetData() {
  data.error = 0;
  data.m1 = 0;
  data.m2 = 0;
  data.P = 0;
  data.I = 0;
  data.D = 0;
}

void receiver_setup() {
  ResetData();

  Serial.println("searching for radio signals");
  digitalWrite(s_led, 0);

  // to test the radio hardware is connected or not
  while (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
  }
  Serial.println("got the radio hardware");
  digitalWrite(s_led, 1);

  // to initialize sending or recieving
  radio.openReadingPipe(1, address);  // for receiving
  radio.openWritingPipe(address);     // for sending
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();  // to start receiving data
  Serial.println("started listening");
  delay(2000);
}

void receive_data() {
  if (radio.available()) {
    radio.read(&data, sizeof(Signal));

    // to find the motor speeds
    Serial.println(String() + F("error: ") + data.error + F("\tmotor1: ") + data.m1 + F("\tmotor2: ") + data.m2);
  }
}

// need a way to test wether the transmission is successful or not
void transmit_data() {
  radio.stopListening();  // to get into transmission mode

  data.P = map(analogRead(P_pin), 0, 1023, 0, 255);
  data.I = map(analogRead(I_pin), 0, 1023, 0, 255);
  data.D = map(analogRead(D_pin), 0, 1023, 0, 255);

  radio.write(&data, sizeof(Signal));

  Serial.println(data.P);
  // Serial.println(String() + F("p_in: ") + data.P * 0.001 + F("\ti_in: ") + data.I * 0.001 + F("\td_in: ") + data.D * 0.001);

  radio.startListening();  // to set the module into receiving mode
}
