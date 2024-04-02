// // // first use receiver_setup() function in setup block
// // // then use get_radio_values() function to get the radio values

// #include <SPI.h>
// #include <RF24.h>

// RF24 radio(10, 9);  // CE, CSN pins (customize these for your setup)
// const byte address[6] = "00001";

// void ResetData() {
//   data.error = 0;
//   data.m1 = 0;
//   data.m2 = 0;
//   data.P = 0;
//   data.I = 0;
//   data.D = 0;
// }

// void receiver_setup() {
//   ResetData();

//   Serial.println("searching for radio signals");
//   int funny_count = 0;  // just for radio count
//   while (!radio.begin()) {
//     Serial.println(F("radio hardware is not responding!!"));
//     analogWrite(led, funny_count % 255);
//     funny_count++;
//   }
//   analogWrite(led, 255);
//   Serial.println("got the radio hardware");

//   // to initialize sending or recieving
//   radio.openReadingPipe(1, address);  // for receiving
//   radio.openWritingPipe(address);     // for sending
//   radio.setPALevel(RF24_PA_LOW);
//   radio.startListening();  // to start receiving data
//   Serial.println("started listening");
//   delay(1000);
// }

// void receive_data() {
//   if (radio.available()) {
//     radio.read(&data, sizeof(Signal));

//   // println(data.P);

//     // to change the pid values when radio available
//     Kp = data.P * 0.001;
//     Ki = data.I * 0.001;
//     Kd = data.D * 0.001;

//     Serial.println(String() + F("p_in: ") + data.P * 0.001 + F("\ti_in: ") + data.I * 0.001 + F("\td_in: ") + data.D * 0.001);
//   }
//   else{
//     Serial.println("not getting the values");
//   }
// }

// void transmit_data() {
//   radio.stopListening();  // to get into transmission mode

//   data.error = error;
//   data.m1 = motor_speed1;
//   data.m2 = motor_speed2;

//   radio.write(&data, sizeof(Signal));

//   // Serial.println(String() + F("error: ") + data.error + F("\tmotor1: ") + data.m1 + F("\tmotor2: ") + data.m2);

//   radio.startListening();  // to set the module into receiving mode
// }
