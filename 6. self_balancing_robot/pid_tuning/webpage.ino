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