// // first use gyro_setup function in the setup section
// // use this function to get values;
// get_gyro_values();
// gyro_without_bias();

#include <Wire.h>


// to store values gyro and acceleration values
float roll, pitch, yaw, accX, accY, accZ;  // raw values
float g_roll, g_pitch, g_yaw;              // rotations from gyro
float a_roll, a_pitch;                     // rotations from accelerometer
float real_roll, real_pitch, real_yaw;     // filtered values

float roll_calib_factor = 1, pitch_calib_factor = 1, yaw_calib_factor = 1;

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

  isEEPROMInitialized();
  // to get the bias offset values of the mpu6050
  rb = -2.9979395866394;
  pb = -5.1416850090027;
  yb = -0.8455882072449;
  axb = -0.0460012219846;
  ayb = 0.0108886715025;
  azb = 1.0262498855591;

  get_staring_pos();
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

  accX = ((float)accelX / 4096) - axb;
  accY = ((float)accelY / 4096) - ayb;
  accZ = ((float)accelZ / 4096) - azb;
}

void gyro_without_bias() {
  get_gyro_values();

  g_roll += (roll - rb) * (time_step / 1000.0) * roll_calib_factor;  // angular velociry * time * calib_factor
  g_pitch += (pitch - pb) * (time_step / 1000.0) * pitch_calib_factor;
  g_yaw += (yaw - yb) * (time_step / 1000.0) * yaw_calib_factor;

  a_roll = atan2(accY, accZ) * 180.0 / PI;
  a_pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;

  float complimentary_gain = 0.98;
  real_roll = complimentary_gain * g_roll + (1 - complimentary_gain) * a_roll;
  real_pitch = complimentary_gain * g_pitch + (1 - complimentary_gain) * a_pitch;
  real_yaw = g_yaw;

  measures[0] = real_roll;
  measures[1] = real_pitch;
  measures[2] = real_yaw;

  // Serial.println(String() + real_roll + F("\t") + real_pitch);
}

void bias_values() {
  Serial.println("wait bro im finding the error values in mpu6050");
  int n = 2000;  // number of times need to sum
  float roll_sum = 0;
  float pitch_sum = 0;
  float yaw_sum = 0;
  float accX_sum = 0;
  float accY_sum = 0;
  float accZ_sum = 0;

  for (int i = 0; i < n; i++) {
    get_gyro_values();
    roll_sum += roll;
    pitch_sum += pitch;
    yaw_sum += yaw;
    accX_sum += accX;
    accY_sum += accY;
    accZ_sum += accZ;

    Serial.println(String() + (float)(i / n) * 100 + "% completed");
  }
  n = (float)n;
  rb = roll_sum / n;
  pb = pitch_sum / n;
  yb = yaw_sum / n;
  axb = accX_sum / n;
  ayb = accY_sum / n;
  azb = accZ_sum / n;

  Serial.println("\ncalibrated");
  Serial.println("roll \t pitch \t yaw \t accX \t accY \t accZ");

  Serial.print(rb, 13);
  Serial.print("\t");
  Serial.print(pb, 13);
  Serial.print("\t");
  Serial.print(yb, 13);
  Serial.print("\t");

  Serial.print(axb, 13);
  Serial.print("\t");
  Serial.print(ayb, 13);
  Serial.print("\t");
  Serial.println(azb, 13);
  askToSave();
}

void get_staring_pos() {
  get_gyro_values();
  float avg_start_roll = 0, avg_start_pitch = 0;
  for (int i = 0; i < 100; i++) {
    a_roll = atan2(accY, accZ) * 180.0 / PI;
    a_pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;
    avg_start_roll += a_roll;
    avg_start_pitch += a_pitch;
  }
  g_roll = avg_start_roll / 100;
  g_pitch = avg_start_pitch / 100;
  Serial.print(String() + "starting roll values : " + g_roll + "\tstarting pitch value : " + g_pitch);
  // while(true){ // while debugging used it
  //   delay(5000);
  // }
}