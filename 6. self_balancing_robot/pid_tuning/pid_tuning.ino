#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

using namespace websockets;

WebsocketsServer server;
WebsocketsClient client;

// for pid tuning
float p = 0.4219;
float i = 0.003;
float d = 0.4219;
float measures[3] = {0,0,90}; // roll, pitch, yaw;
int prev_error = 0, error_sum = 0;
int pid_out;

float prev_roll, prev_pitch, prev_yaw; // to send the values over websocket only when they are changed
float rb = 0, pb = 0, yb = 0, axb = 0, ayb = 0, azb = 0;  // bias values for mpu6050

// for frequecy of execution
int time_step = 4;
double prev_time = millis();
int count = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  gyro_setup();
  motor_setup();
  wifi_setup();
  websocket_setup();  // uncomment this for webpage with websockets
  // webpage_setup(); // uncomment this for webpage without websockets
}

void loop() {
  if (millis() - prev_time >= time_step) {
    prev_time = millis();
    
    // server.handleClient(); // uncomment this for webpage without websockets
    handle_websocket();  // uncomment this for webpage with websockets

    gyro_without_bias();
    pid_controller();
  }
}
