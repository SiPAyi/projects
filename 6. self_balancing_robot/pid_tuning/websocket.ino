void wifi_setup() {
  const char* ssid = "Sai";               //Enter SSID
  const char* password = "saikottapeta";  //Enter Password

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    toggle_led();
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  wifi_connected_indication();
}

// uncomment the below code for webpage with websockets
void websocket_setup() {
  server.listen(80);
  Serial.print("Is server live? ");
  Serial.println(server.available());
  client = server.accept();

  // run callback when messages are received
  client.onMessage([&](WebsocketsMessage message) {
    String receivedData = message.data();

    // Parse the received data
    int commaIndex1 = receivedData.indexOf(',');
    int commaIndex2 = receivedData.indexOf(',', commaIndex1 + 1);

    float p = receivedData.substring(0, commaIndex1).toFloat();
    float i = receivedData.substring(commaIndex1 + 1, commaIndex2).toFloat();
    float d = receivedData.substring(commaIndex2 + 1).toFloat();

    // Print the received variables to the serial monitor
    Serial.print("Var1: ");
    Serial.print(p, 5);
    Serial.print("\tVar2: ");
    Serial.print(i, 5);
    Serial.print("\tVar3: ");
    Serial.println(d, 5);
  });
}

void handle_websocket() {
  if (client.available()) {  // uncomment this for webpage with websockets
    client.poll();
    // send some values
    if (prev_roll != measures[0] || prev_pitch != measures[1] || prev_yaw != measures[2]) {
      prev_roll = measures[0];
      prev_pitch = measures[1];
      prev_yaw = measures[2];
      client.send(String() + measures[0] + "," + measures[1] + "," + measures[2]);
    }
    count++;
  }
}