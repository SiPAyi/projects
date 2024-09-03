// // first use receiver_setup() function in setup block
// // then use get_radio_values() function to get the radio values

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN pins (customize these for your setup)
const byte address[6] = "00001";

// timestamps
unsigned long last_ideal_mode_time = 0;
unsigned long last_alt_hold_mode_time = 0;
unsigned long last_nrf_connected_time = 0;
unsigned long last_ping_time = 0;

// for radio communication, controller data-type
struct Orientation
{
  float roll;
  float pitch;
  float yaw;
  float throttle;
  float battery_level;
};
Orientation orientation_data;

struct rpyt_command
{
  float roll;
  float pitch;
  float yaw;
  float throttle;
} rpyt_command rpyt_command_data;

void ResetData()
{
  orientation_data.roll = 0;
  orientation_data.pitch = 0;
  orientation_data.yaw = 0;
  orientation_data.throttle = 0;
  orientation_data.battery_level = 0;
  rpyt_command_data.roll = 0;
  rpyt_command_data.pitch = 0;
  rpyt_command_data.yaw = 0;
  rpyt_command_data.throttle = 0;
}

void receiver_setup()
{
  ResetData();

  Serial.println("Connecting to nrf module...");
  while (!radio.begin())
  {
    Serial.println(F("radio hardware is not responding!!"));
    blinkLED(green1, 500, last_nrf_connected_time);
    last_nrf_connected_time = millis();
  }

  Serial.println("Found the nrf module");
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.setRetries(3, 5); // Retry delay: 1500us, Retry count: 15
  radio.enableDynamicPayloads();
  radio.enableAckPayload();
  radio.startListening();
}

int wait_for_ping()
{
  if (radio.available())
  {
    radio.read(&dataReceived, sizeof(dataReceived));
    Serial.print("Received data: ");
    Serial.println(dataReceived);
    Serial.println("going to state S2");
    led_output(1, 0, 1);
    return idealMode;
  }
  else
  {
    Serial.println("waiting for transmitter ping message");
    blinkLED(green2, 500, last_ping_time);
    last_ping_time = millis();
    return setupMode;
  }
}

int idealModeReceiver()
{
  int ideal_mode_command;
  unsigned long current_millis = millis();
  if (radio.available())
  {
    last_ideal_mode_time = millis();
    radio.read(&ideal_mode_command, sizeof(ideal_mode_command));
    Serial.print("Received data: ");
    Serial.println(ideal_mode_command);

    // filling the values to transmit
    orientation_data.roll = measures[ROLL];
    orientation_data.pitch = measures[PITCH];
    orientation_data.yaw = measures[YAW];
    orientation_data.throttle = measures[THROTTLE];
    orientation_data.battery_level = battery_level;

    radio.writeAckPayload(1, &orientation_data, sizeof(orientation_data));

    if (ideal_mode_command == 1 || ideal_mode_command == 2)
    {
      return idealMode;
    }
    else if (ideal_mode_command == 3)
    {
      return altitudeHoldMode;
    }
    else if (ideal_mode_command == 4)
    {
      return sensorCalibMode;
    }
    else if (ideal_mode_command == 5)
    {
      return PIDTunerMode;
    }
  }
  else if ((current_millis - last_ideal_mode_time) < 1000) // 1000 is 1sec before connection lost
  {
    return idealMode;
  }
  else // 1sec after connection lost
  {
    return setupMode;
  }
}

void altitudeHoldModeTransmitter()
{
  unsigned long current_millis = millis();
  if (radio.available())
  {
    last_alt_hold_mode_time = millis();
    radio.read(&rpyt_command_data, sizeof(rpyt_command_data));
    instruction[ROLL] = rpyt_command_data.roll;
    instruction[PITCH] = rpyt_command_data.pitch;
    instruction[YAW] = rpyt_command_data.yaw;
    instruction[THROTTLE] = rpyt_command_data.throttle;
    Serial.print("Received rpyt command values");

    // filling the values to transmit
    orientation_data.roll = measures[ROLL];
    orientation_data.pitch = measures[PITCH];
    orientation_data.yaw = measures[YAW];
    orientation_data.throttle = measures[THROTTLE];
    orientation_data.battery_level = battery_level;

    radio.writeAckPayload(1, &orientation_data, sizeof(orientation_data));
    return altitudeHoldMode;
  }
  else if ((current_millis - last_alt_hold_mode_time) < 1000) // 1000 is 1sec before connection lost
  {
    return altitudeHoldMode;
  }
  else // 1sec after connection lost
  {
    return setupMode;
  }
}

void sensorCalibModeReceiver()
{
}