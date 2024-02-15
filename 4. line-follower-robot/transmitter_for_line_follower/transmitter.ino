#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE, CSN pins (customize these for your setup)
const byte address[6] = "00001";

struct Signal
{
  bool switch1;
  bool switch2;
  int throttle;
  int pitch;
  int roll;
  int yaw;
  int P;
  int I;
  int D;
};
Signal data;

int P_pin = A1;
int I_pin = A2;
int D_pin = A4;

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

void setup()
{
  ResetData();

  Serial.begin(9600);

  // initialize the transceiver on the SPI bus
  if (!radio.begin())
  {
    Serial.println(F("radio hardware is not responding!!"));
    while (1)
    {
    } // hold in infinite loop
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);

  Serial.println("radio connected");

  radio.stopListening(); // put radio in TX mode
}

void loop()
{
  transmit_data();
}

// need a way to test wether the transmission is successful or not
void transmit_data()
{
  data.P = map(analogRead(P_pin), 0, 1023, 0, 255);
  data.I = map(analogRead(I_pin), 0, 1023, 0, 255);
  data.D = map(analogRead(D_pin), 0, 1023, 0, 255);

  radio.write(&data, sizeof(Signal));

  Serial.print("\t P : ");
  Serial.print(data.P);
  Serial.print("\t I : ");
  Serial.print(data.I);
  Serial.print("\t D : ");
  Serial.print(data.D);
}