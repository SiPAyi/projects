#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

ESP8266WebServer server(80);

// Define the pin connected to the built-in LED
const int LED_PIN = LED_BUILTIN; // This is usually GPIO2 (D4) on NodeMCU

bool ledState = LOW; // Initialize LED state to off

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Start the web server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/toggle", HTTP_GET, handleToggle);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  // Send HTML page with a button to toggle the LED and display LED state
  String page = "<!DOCTYPE html><html><head><title>LED Control</title>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<style>body{text-align:center;font-family:Arial, sans-serif;background-color:#f2f2f2;}"
          ".container{display:flex;flex-direction:column;align-items:center;justify-content:center;height:100vh;}"
          "button{padding:10px 20px;background-color:#4CAF50;color:white;border:none;border-radius:5px;cursor:pointer;font-size:16px;margin-bottom:20px;}"
          "button:hover{background-color:#45a049;}@media screen and (max-width: 600px){button{width:80%;}} .led-state{font-size: 20px;}</style>";
  page += "<script>function updateLEDState(state) {"
          "document.getElementById('ledState').innerHTML = 'LED is currently ' + state;"
          "}</script>";
  page += "</head><body><div class='container'>";
  page += "<h1>Control LED</h1>";
  page += "<p class='led-state' id='ledState'>LED is currently " + String(ledState ? "ON" : "OFF") + "</p>";
  page += "<button onclick='toggleLED()'>Toggle LED</button>";
  page += "</div><script>function toggleLED() {"
          "var xhttp = new XMLHttpRequest();"
          "xhttp.onreadystatechange = function() {"
          "if (this.readyState == 4 && this.status == 200) {"
          "updateLEDState(this.responseText);"
          "}"
          "};"
          "xhttp.open('GET', '/toggle', true);"
          "xhttp.send();}</script></body></html>";

  server.send(200, "text/html", page);
}

void handleToggle() {
  // Toggle LED state
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  
  // Send response with LED state
  server.send(200, "text/plain", ledState ? "turned off" : "turned on");
}
