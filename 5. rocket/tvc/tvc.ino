#include <Wire.h>

float roll, pitch, yaw, accX, accY, accZ;  // to store values
float rb, pb, yb, axb, ayb, azb; 

void setup() {
  Serial.begin(9600);
  Wire.setClock(400000);
  Wire.begin();

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(250);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  // to get the bias offset values of the mpu6050
  bias_values();
  // // i get this values from calibration
  // rb = 3.18;
  // pb = -2.58;
  // yb = 0.26;
}

void loop() {
  // get_gyro_values();
  gyro_without_bias();

  Serial.print("roll :\t");
  Serial.print(roll);
  Serial.print("pitch :\t");
  Serial.print(pitch);
  Serial.print("yaw : \t");
  Serial.println(yaw);
  delay(50);
}
