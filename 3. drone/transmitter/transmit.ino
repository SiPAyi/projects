#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins
const byte address[6] = "00001";

// timestamps
unsigned long last_ideal_mode_time = 0;
unsigned long last_alt_hold_mode_time = 0;

// for radio communication, controller data-type for ideal mode transmission
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

void transmitter_setup()
{
    ResetData();

    // initialize nrf module
    while (!radio.begin())
    {
        Serial.println(F("radio hardware is not responding!!"));
        lcd_print_wrap("radio hardware  not responding!!");
    }
    Serial.println(F("radio hardware is responding!!"));
    lcd_print_wrap("radio hardware  is responding!!");
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_1MBPS);
    radio.setRetries(3, 5); // Retry delay: 1500us, Retry count: 15
    radio.enableDynamicPayloads();
    radio.enableAckPayload();
    radio.stopListening();
    radio_connected_led();
    lcd_print_wrap("initialized nrf module");
}

int ping_drone()
{
    String ping_msg = "hello";
    bool sent_status = radio.write(&ping_msg, sizeof(ping_msg));
    if (send_status)
    {
        Serial.println("Now in idealMode(S2)");
        lcd_print_wrap("Now in idealMode(S2)");
        return idealMode;
    }
    else
    {
        Serial.println("trying to ping drone");
        lcd_print_wrap("Trying to ping  the drone");
        return setupMode;
    }
}

// with this function we ping the drone and that drone sends its orientation and battery status
int idealModeTransmitter(int ideal_mode_command)
{
    // get the button inputs and find the next state

    unsigned long current_millis = millis();

    if (radio.write(&ideal_mode_command, sizeof(ideal_mode_command)))
    {
        last_ideal_mode_time = millis();
        Serial.println("Message sent successfully");

        // Check for acknowledgment
        if (radio.isAckPayloadAvailable())
        {
            radio.read(&orientation_data, sizeof(orientation_data));
            Serial.print("Acknowledgment received");
            return ideal_mode_command;
        }
        else if ((current_millis - last_ideal_mode_time) < 1000) // 1000 is 1sec before connection lost
        {
            Serial.println("No acknowledgment received");
            return idealMode;
        }
        else
        {
            return setupMode;
        }
    }
    else
    {
        Serial.println("Message sending failed");
        return setupMode;
    }
}

// need a way to test wether the transmission is successful or not
int altitudeHoldModeTransmitter()
{
    unsigned long current_millis = millis();

    rpyt_command_data.throttle = map(analogRead(throttle_pin), 0, 1023, 0, 255);
    rpyt_command_data.yaw = map(analogRead(yaw_pin), 0, 1023, 0, 255);
    rpyt_command_data.pitch = map(analogRead(pitch_pin), 0, 1023, 0, 255);
    rpyt_command_data.roll = map(analogRead(roll_pin), 0, 1023, 0, 255);

    if (radio.write(&data, sizeof(Signal)))
    {
        last_alt_hold_mode_time = millis();
        Serial.println("Message sent successfully");

        // Check for acknowledgment
        if (radio.isAckPayloadAvailable())
        {
            radio.read(&orientation_data, sizeof(orientation_data));
            Serial.print("Acknowledgment received");
            return altitudeHoldMode;
        }
        else if ((current_millis - last_ideal_mode_time) < 1000) // 1000 is 1sec before connection lost
        {
            Serial.println("No acknowledgment received");
            return altitudeHoldMode;
        }
        else
        {
            return setupMode;
        }
    }
    else
    {
        Serial.println("Message sending failed");
        return setupMode;
    }
}

int sensorCalibModeTransmitter()
{



}