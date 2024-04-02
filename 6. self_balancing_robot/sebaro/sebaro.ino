#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


// pid controller
float instruction[4] = { 0, 0, 0, 30 };          // [Yaw (cardinal direction), Pitch (x), Roll (y), Throttle]
float measures[4] = { 0, 0, 0, 0 };              // [Yaw (cardinal direction), Pitch (x), Roll (y)]
int YAW = 0, PITCH = 1, ROLL = 2, THROTTLE = 3;  // for array indexing
int kp=1, kd=1, ki=1;

// Throttle values for each motor
int motor_l_throttle{ 0 }, motor_r_throttle{ 0 };


// for frequecy of execution
int time_step = 4;
double prev_time = millis();

// motor setup
#define ENA D0
#define IN_1 D1
#define IN_2 D2
#define IN_3 D3
#define IN_4 D4
#define ENB D5

String command;
int speedCar = 800;
int speed_Coeff = 3;

const char* ssid = "SEBARO";
ESP8266WebServer server(80);

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  Serial.begin(9600);

  // Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Starting WEB-server
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();


  kalman_gyro_setup();  // setuping gyro
}

void loop() {
  if (millis() - prev_time >= time_step) {
    prev_time = millis();

    kalman_filtered_angles();  // ^ this means got the gyro values

  Serial.print(measures[YAW]);
  Serial.print("\t");
  Serial.print(measures[PITCH]);
  Serial.print("\t");
  Serial.println(measures[ROLL]);

    // // for wireless communication
    // server.handleClient();

    // command = server.arg("State");
    // if (command == "F") kp += 1;
  }
}


void HTTP_handleRoot(void) {

  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}