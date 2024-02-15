
void get_gyro_values(void) {
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();

  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();

  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();

  Wire.requestFrom(0x68, 6);
  int16_t gyroX = Wire.read() << 8 | Wire.read();
  int16_t gyroY = Wire.read() << 8 | Wire.read();
  int16_t gyroZ = Wire.read() << 8 | Wire.read();


  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();

  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();

  Wire.requestFrom(0x68, 6);
  int16_t accelX = Wire.read() << 8 | Wire.read();
  int16_t accelY = Wire.read() << 8 | Wire.read();
  int16_t accelZ = Wire.read() << 8 | Wire.read();


  roll = (float)gyroX / 65.5;
  pitch = (float)gyroY / 65.5;
  yaw = (float)gyroZ / 65.5;

  accX = (float)accelX / 4096;
  accY = (float)accelY / 4096;
  accZ = (float)accelZ / 4096;
}

void bias_values() {
  Serial.println("wait bro im calibrating mpu6050");
  int n = 20000;  // number of times need to sum

  for (int i = 0; i < n; i++) {
    get_gyro_values();
    rb += roll;
    pb += pitch;
    yb += yaw;
    axb += accX;
    ayb += accY;
    azb += accZ;
    Serial.print(".");
  }
  rb /= n;
  pb /= n;
  yb /= n;
  axb /= n;
  ayb /= n;
  azb /= n;

  Serial.println("calibrated");
  Serial.println("roll \t pitch \t yaw");
  Serial.print(rb);
  Serial.print("\t");
  Serial.print(pb);
  Serial.print("\t");
  Serial.println(yb);
  Serial.print("\t");

  Serial.println(axb);
  Serial.print("\t");
  Serial.println(ayb);
  Serial.print("\t");
  Serial.println(azb);
}

void gyro_without_bias() {
  get_gyro_values();

  roll -= rb;
  pitch -= pb;
  yaw -= yb;
  accX -= axb;
  accY -= ayb;
  accZ -= azb;
}
