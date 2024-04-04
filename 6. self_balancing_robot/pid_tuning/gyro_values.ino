// // first use gyro_setup function in the setup section
// // use this function to get values;
// get_gyro_values();
// gyro_without_bias();

#include <Wire.h>


// to store values gyro and acceleration values
float roll, pitch, accX, accY, accZ;  // raw values
float rb, pb, axb, ayb, azb;          // bias values
float g_roll, g_pitch;                // rotations from gyro
float a_roll, a_pitch;                // rotations from accelerometer
float real_roll, real_pitch;          // filtered values

void gyro_setup() {
  Wire.setClock(400000);
  Wire.begin();

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // to get the bias offset values of the mpu6050
  // bias_values();
  rb = -0.3726636171341;
  pb = -2.5272758007050;
  axb = 0.1832492649555;
  ayb = -0.0084074707702;
  azb = 0.9367808699608;
}


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

  Wire.requestFrom(0x68, 4);
  int16_t gyroX = Wire.read() << 8 | Wire.read();
  int16_t gyroY = Wire.read() << 8 | Wire.read();


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

  accX = ((float)accelX / 4096) - axb;
  accY = ((float)accelY / 4096) - ayb;
  accZ = ((float)accelZ / 4096) - azb;
}

void gyro_without_bias() {
  get_gyro_values();

  g_roll += (roll - rb) * (time_step * 5.5 / 1000.0);
  g_pitch += (pitch - pb) * (time_step * 5.5 / 1000.0);

  a_roll = atan2(accY, accZ) * 180.0 / PI;
  a_pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;

  float complimentary_gain = 0.98;
  real_roll = complimentary_gain * g_roll + (1 - complimentary_gain) * a_roll;
  real_pitch = complimentary_gain * g_pitch + (1 - complimentary_gain) * a_pitch;
  
  measures = real_pitch;

  // Serial.println(String() + real_roll + F("\t") + real_pitch);
}


void bias_values() {
  Serial.println("wait bro im calibrating mpu6050");
  int n = 2000;  // number of times need to sum
  int roll_sum = 0;
  int pitch_sum = 0;
  int accX_sum = 0;
  int accY_sum = 0;
  int accZ_sum = 0;

  for (int i = 0; i < n; i++) {
    get_gyro_values();
    roll_sum += roll;
    pitch_sum += pitch;
    accX_sum += accX;
    accY_sum += accY;
    accZ_sum += accZ;
    Serial.print(".");
  }
  n = (float)n;
  rb = roll_sum / n;
  pb = pitch_sum / n;
  axb = accX_sum / n;
  ayb = accY_sum / n;
  azb = accZ_sum / n;

  Serial.println("calibrated");
  Serial.println("roll \t pitch \t yaw");

  Serial.print(rb, 13);
  Serial.print("\t");
  Serial.print(pb, 13);
  Serial.print("\t");

  Serial.print(axb, 13);
  Serial.print("\t");
  Serial.print(ayb, 13);
  Serial.print("\t");
  Serial.println(azb, 13);
  delay(5000);
}