// // first use receiver_setup() function in setup block
// // then use get_radio_values() function to get the radio values

#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE, CSN pins (customize these for your setup)
const byte address[6] = "00001";

void ResetData() {
  data.throttle = 0;  // Motor Stop (254/2=127)(Signal lost position)
  data.pitch = 0;     // Center (Signal lost position)
  data.roll = 0;      // Center(Signal lost position)
  data.yaw = 0;       // Center (Signal lost position )
}

void receiver_setup() {
  ResetData();

  Serial.println("searching for radio signals");
  while (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    radio_status_count++;


    // to indicate the radio status
    led_status = (int)radio_status_count % 255;
    analogWrite(A4, led_status);
  }
  radio_status_count = 0;
  Serial.println("got the radio signal");
  radio.openReadingPipe(1, address);
  radio.startListening();
  delay(1000);
  Serial.println("radio connected");
}

void receive_data() {
  if (radio.available()) {
    radio_status_count = 0;
    radio.read(&data, sizeof(Signal));
    analogWrite(A4, 0);
  } else {
    radio_status_count++;
    if (radio_status_count >= 1250) {                         // if radio is disconnected for 5(5*250 = 1250 times) seconds
      led_status = ((int)(radio_status_count + 1250)) % 255;  // change the output every 500(125*4) milliseconds
      analogWrite(A4, led_status);
      Serial.println("loose the connection since 5 seconds");
    } else {
      Serial.println("im not getting the signal");
    }
  }
}