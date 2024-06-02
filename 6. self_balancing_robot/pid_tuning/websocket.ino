void wifi_setup() {
  const char *ssid = "Sai";           // Enter SSID
  const char *password = "........";  // Enter Password

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
  connect_websocket();
  Serial.println("opened the websocket");
}

void connect_websocket() {
  client = server.accept();

  // run callback when messages are received
  client.onMessage([&](WebsocketsMessage message) {
    String receivedData = message.data();

    // Parse the received data
    int commaIndex1 = receivedData.indexOf(',');
    int commaIndex2 = receivedData.indexOf(',', commaIndex1 + 1);
    int commaIndex3 = receivedData.indexOf(',', commaIndex2 + 1);

    p = receivedData.substring(0, commaIndex1).toFloat();
    i = receivedData.substring(commaIndex1 + 1, commaIndex2).toFloat();
    d = receivedData.substring(commaIndex2 + 1).toFloat();
    mode = receivedData.substring(commaIndex3 + 1).toInt();

    // Print the received variables to the serial monitor
    Serial.print("p: ");
    Serial.print(p, 5);
    Serial.print("\t i: ");
    Serial.print(i, 5);
    Serial.print("\t d: ");
    Serial.print(d, 5);
    Serial.print("\t mode: ");
    Serial.println(mode);
  });
}

void handle_websocket() {
  if (client.available()) {
    client.poll();
    // send some values
    if (prev_roll != measures[0] || prev_pitch != measures[1] || prev_yaw != measures[2]) {
      prev_roll = measures[0];
      prev_pitch = measures[1];
      prev_yaw = measures[2];
      int pid_value = (measures[1] > 0) ? pid_out : -pid_out;
      client.send(String() + measures[0] + "," + measures[1] + "," + measures[2] + "," + pid_value);
    }
    count = 0;
  } else {
    Serial.println(String() + "websocket is disconnected from last " + (count * 4) + " millisecons, I'm trying to open again");
    if (count == 10) {
      client.close();
      connect_websocket();
      Serial.println("again opened the websocket");
    }
    count++;
  }
}