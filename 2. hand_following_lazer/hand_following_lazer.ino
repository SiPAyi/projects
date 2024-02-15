#include<Servo.h>

Servo servoX;
Servo servoY;

void setup() {
  // Initialize serial communication.
  Serial.begin(9600);
  servoX.attach(9);
  servoY.attach(10);
}
  
void turn(float x, float y){
  x = 0 + (58*x);
  y = 90 + (28*y);
  servoX.write(x);
  servoY.write(y);
  delay(200);
}

void loop() {
  // Wait for a message from Python.
  while (!Serial.available()) {}
  
  // Read the message from Python.
  String message = Serial.readStringUntil('\n');

  // Parse the message into x, y, and z coordinates.
  int comma1 = message.indexOf(',');
  int comma2 = message.indexOf(',', comma1 + 1);
  float x = message.substring(0, comma1).toFloat();
  float y = message.substring(comma1 + 1, comma2).toFloat();
  float z = message.substring(comma2 + 1).toFloat();

  // Output the coordinates to the serial monitor.
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Z: ");
  Serial.println(z);

  turn(x, y);
}
