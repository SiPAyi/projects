// // first use receiver_setup() function in setup block
// // then use get_radio_values() function to get the radio values

#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE, CSN pins (customize these for your setup)
const byte address[6] = "00001";

void ResetData() {
  data.switch1 = 0;
  data.switch2 = 0;
  data.throttle = 0;  // Motor Stop (254/2=127)(Signal lost position)
  data.pitch = 0;     // Center (Signal lost position)
  data.roll = 0;      // Center(Signal lost position)
  data.yaw = 0;       // Center (Signal lost position )
  data.pid = 0;
}

void receiver_setup() {
  ResetData();

  Serial.println("searching for radio signals");
  while (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    blink_eyes();
    radio_status_count++;
    led_status = ((int)radio_status_count / 125) % 2;
    digitalWrite(green1, led_status);
    digitalWrite(green2, led_status);
  }
  radio_status_count = 0;
  Serial.println("got the radio signal");
  // radio.openWritingPipe(address);
  radio.openReadingPipe(1, address);
  radio.startListening();
  open_eyes();
  delay(1000);
  Serial.println("radio connected");
}

void receive_data() {
  if (radio.available()) {
    radio_status_count = 0;
    radio.read(&data, sizeof(Signal));

    // instruction[THROTTLE] = 60 + map(data.pid, 0, 255, 0, 120);
    // instruction[YAW] = (data.yaw - 125) / 10;
    // instruction[PITCH] = (data.pitch-125)/10;
    // instruction[ROLL] = (data.roll-125)/10;

    // below block is used when tuning
    // instruction[PITCH] = 0;
    // instruction[ROLL] = 0;
    // Kp[YAW] = (float)data.pid * 12 / 10;

    // disp_measures(); // for display info on lcd

    Serial.print("*");  // * it shows that radio is connected in the serial monitor
    open_eyes();
  } else {
    radio_status_count++;
    if (radio_status_count >= 1250) {  // if radio is disconnected for 5(5*250 = 1250 times) seconds
      stopMotors();
      led_status = ((int)(radio_status_count + 1250) / 125) % 2;  // change the output every 500(125*4) milliseconds
      digitalWrite(green1, led_status);
      digitalWrite(green2, led_status);
      Serial.println("loose the connection since 5 seconds");
    } else {
      // close_eyes();
      // Serial.println("im not getting the signal");
    }
  }
}

// void transmit_data() {
//   data.yaw = measures[YAW];
//   data.pitch = measures[PITCH];
//   data.roll = measures[ROLL];
//   data.throttle = instruction[THROTTLE];  // replace this with altitude when dealing with barometer

//   radio.write(&data, sizeof(Signal));

//   disp_measures();
// }

void flight_start_test() {
  // it will put the drone into control mode by moving the left joystick to bottom right corner
  while (true) {
    receive_data();
    if (instruction[THROTTLE] == -12 && instruction[YAW] == 13) {
      break;
    }
    Serial.print("waiting for ");
    Serial.print("instruction[THROTTLE] == 0 && instruction[YAW] == 255\t");
    Serial.print(data.throttle);
    Serial.print("\t");
    Serial.print(data.yaw);
    Serial.print("\t");
    Serial.print(instruction[THROTTLE] == 0);
    Serial.print("\t");
    Serial.println(instruction[YAW] == 255);
  }
  Serial.print("okay i got the instruction to start the props");
  Serial.print("I will start propellers in ");
  for (int i = 1; i < 4; i++) {
    lcd.print(3 - i);
    lcd.print(" ");
    Serial.print(3 - i);
    Serial.print("\t");
    digitalWrite(red, 3 % 2);
    delay(1000);
  }
  digitalWrite(red, LOW);
}

void start_menu() {
  // i want to create a menu so the i can put my drone into any mode.
  // 1. gyro calibration mode
  // 2. esc calibration mode
  // 3. control mode
  // 4. stable flight mode
}