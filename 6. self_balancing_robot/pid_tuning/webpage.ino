// uncomment this for webpage without websockets
// // for esp32
// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <WebServer.h>
// WebServer server(80);

// // for nodemcu
// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266mDNS.h>
// ESP8266WebServer server(80);

// void webpage_setup() {
//   // Starting WEB-server
//   server.on("/", HTTP_GET, []() {
//     if (server.args() > 0) {
//       String pValue = server.arg("p");
//       String iValue = server.arg("i");
//       String dValue = server.arg("d");

//       // Convert string values to float or integer based on your requirements
//       p = pValue.toFloat();
//       i = iValue.toFloat();
//       d = dValue.toFloat();

//       Serial.println("PID values - P: " + String(p) + ", I: " + String(i) + ", D: " + String(d));
//     }
//     String response = String(g_roll) + "," + String(g_pitch);  // Replace g_roll and g_pitch with your actual gyro values
//     server.sendHeader("Access-Control-Allow-Origin", "*");     // Allow requests from any origin
//     server.send(200, "text/plain", response);
//   });

//   server.onNotFound([]() {
//     server.send(404, "text/plain", "Not found");
//   });

//   server.begin();
// }