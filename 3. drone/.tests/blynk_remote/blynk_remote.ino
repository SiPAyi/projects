#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "your_template_id"
#define BLYNK_TEMPLATE_NAME "your_template_name"
#define BLYNK_AUTH_TOKEN "gYkYLDmWqH68kQWh3x4p_9oWzqD5J6a_"

char ssid[] = "your_SSID"; // Replace with your Wi-Fi network SSID
char pass[] = "your_PASSWORD"; // Replace with your Wi-Fi network password

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  // Read joystick values
  int joystick1X = Blynk.virtualRead(V1);
  int joystick1Y = Blynk.virtualRead(V2);
  int joystick2X = Blynk.virtualRead(V3);
  int joystick2Y = Blynk.virtualRead(V4);

  // Display values on the serial monitor
  Serial.print("Joystick 1 X: ");
  Serial.println(joystick1X);
  Serial.print("Joystick 1 Y: ");
  Serial.println(joystick1Y);
  Serial.print("Joystick 2 X: ");
  Serial.println(joystick2X);
  Serial.print("Joystick 2 Y: ");
  Serial.println(joystick2Y);

  delay(100);  // Adjust the delay as needed
}
