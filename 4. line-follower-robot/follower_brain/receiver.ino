// // first use receiver_setup() function in setup block
// // then use get_radio_values() function to get the radio values

#include <SPI.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSN pins (customize these for your setup)
const byte address[6] = "00001";

void ResetData()
{
  data.switch1 = 0;
  data.switch2 = 0;
  data.throttle = 0; 
  data.yaw = 0;      
  data.pitch = 0;    
  data.roll = 0;     
  data.P = 0;
  data.I = 0;
  data.D = 0;
}

void receiver_setup()
{
  ResetData();

  Serial.println("searching for radio signals");
  int funny_count = 0; // just for radio count
  while (!radio.begin())
  {
    Serial.println(F("radio hardware is not responding!!"));
    analogWrite(led, funny_count % 255);
    funny_count++;
  }
  analogWrite(led, 255);

  Serial.println("got the radio hardware");
  radio.openReadingPipe(1, address);
  radio.startListening();
  delay(1000);
  Serial.println("radio working");
}

void receive_data()
{
  if (radio.available())
  {
    radio_status_count = 0;
    radio.read(&data, sizeof(Signal));

    if (data.throttle >= 128)
    {
      data.throttle -= 128; // data.throttle middle value is 128
      data.throttle /= 2;
    }
    else
    {
      data.throttle = 0; // if throttle less than 128 it will decrease the speed even we want to move like left turn
    }
  }
  // else
  // {
  //   radio_status_count++;
  // if (radio_status_count >= 1250) {  // if radio is disconnected for 5(5*250 = 1250 times) seconds
  //   led_status = ((int)(radio_status_count + 1250) / 125) % 2;  // change the output every 500(125*4) milliseconds
  //   digitalWrite(led, led_status);
  //   Serial.println("loose the connection since 5 seconds");
  // } else {
  //   Serial.println("im not getting the signal");
  // }
  // }
}
