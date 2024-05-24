#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

WebServer server(80);
Servo motor;

const int redPin = D2;
int led_state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  webpage_setup();
  motor.attach(D2);
}

void loop() {
  server.handleClient();
  motor.write(p);
}

void webpage_setup() {
  const char* ssid = "YOUR_SSID";
  const char* password = "YOUR_PASSWORD";

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    toggle_led();
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  wifi_connected_indication();

  // Starting WEB-server
  server.on("/", HTTP_GET, []() {
    if (server.args() > 0) {
      String pValue = server.arg("p");
      String iValue = server.arg("i");
      String dValue = server.arg("d");

      // Convert string values to float or integer based on your requirements
      p = pValue.toFloat();
      i = iValue.toFloat();
      d = dValue.toFloat();

      Serial.println("PID values - P: " + String(p) + ", I: " + String(i) + ", D: " + String(d));
    }
    String response = String(g_roll) + "," + String(g_pitch);  // Replace g_roll and g_pitch with your actual gyro values
    server.sendHeader("Access-Control-Allow-Origin", "*");     // Allow requests from any origin
    server.send(200, "text/plain", response);
  });

  server.onNotFound([]() {
    server.send(404, "text/plain", "Not found");
  });

  server.begin();
}

void toggle_led() {  // blinks every half second
  digitalWrite(LED_BUILTIN, !led_state);
  delay(500);
}

void wifi_connected_indication() {
  digitalWrite(LED_BUILTIN, 1);
  delay(250);
  digitalWrite(LED_BUILTIN, 0);
  delay(250);

  digitalWrite(LED_BUILTIN, 1);
  delay(250);
  digitalWrite(LED_BUILTIN, 0);
  delay(250);

  digitalWrite(LED_BUILTIN, 1);
  delay(250);
  digitalWrite(LED_BUILTIN, 0);
  delay(250);

  digitalWrite(LED_BUILTIN, 1);
  delay(1000);
  digitalWrite(LED_BUILTIN, 0);
  delay(250);

  digitalWrite(LED_BUILTIN, 1);
}