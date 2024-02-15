#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


const uint64_t pipeOut = 0xE9E8F0F0E1LL; //IMPORTANT: The same as in the receiver 0xE9E8F0F0E1LL
RF24 radio(8, 10); // select CE,CSN pin |

struct Signal {
bool state;
byte throttle;
byte pitch;
byte roll;
byte yaw;
};

Signal data;

void ResetData()
{
data.state = 0;
data.throttle = 127; // Motor Stop (254/2=127)(Signal lost position)
data.pitch = 127; // Center (Signal lost position)
data.roll = 127; // Center(Signal lost position)
data.yaw = 127; // Center (Signal lost position )
}

void setup()
{
//Start everything up
ResetData();

radio.begin();
radio.openWritingPipe(pipeOut);
radio.stopListening(); //start the radio comunication for Transmitter
Serial.begin(9600);
Serial.println("started transmitting");
}


void loop()
{
// Control Stick Calibration
// Setting may be required for the correct values of the control levers.

data.state = digitalRead(3);
data.throttle = map( analogRead(A3), 0, 1023, 0, 100);
data.roll = map( analogRead(A1), 0, 1023, 0, 100); // "true" or "false" for servo direction
data.pitch = map( analogRead(A0), 0, 1023, 0, 100); // "true" or "false" for servo direction
data.yaw = map( analogRead(A2), 0, 1023, 0, 100); // "true" or "false" for servo direction

radio.write(&data, sizeof(Signal));

Serial.print("throttle : ");
Serial.print(data.throttle);
Serial.print("  yaw : ");
Serial.print(data.yaw);
Serial.print("  pitch : ");
Serial.print(data.pitch);
Serial.print("  roll : ");
Serial.println(data.roll);

}