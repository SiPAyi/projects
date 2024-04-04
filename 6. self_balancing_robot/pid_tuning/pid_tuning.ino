#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

WebServer server(80);


// for pid tuning
float p = 1;
float i = 0.01;
float d = 1;
int measures = 0;
int prev_error = 0, error_sum = 0;
int pid_out;


// for frequecy of execution
int time_step = 4;
double prev_time = millis();
int count = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  gyro_setup();
  motor_setup();
  webpage_setup();
}

void loop() {
  server.handleClient();

  if (millis() - prev_time >= time_step) {
    prev_time = millis();

    gyro_without_bias();
    pid_controller();
  }
}
