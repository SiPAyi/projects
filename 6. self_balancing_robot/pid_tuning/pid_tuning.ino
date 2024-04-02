#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

float p = 0;
float i = 0;
float d = 0;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Starting WEB-server
  server.on("/", handleRoot);
  server.onNotFound(handleRoot);
  server.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  gyro_setup();
}

void loop() {
  if (millis() - prev_time >= time_step) {
    prev_time = millis();
    server.handleClient();

    analogWrite(LED_BUILTIN, p);
    // get_gyro_values();
    gyro_without_bias();
  }
}

void handleRoot() {
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

  server.sendHeader("Access-Control-Allow-Origin", "*");  // Allow requests from any origin
  server.send(200, "text/plain", "OK");
}
