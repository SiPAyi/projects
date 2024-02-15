// // first use gyro_setup function in the setup section
// // use this function to get values;
// get_gyro_values();
// gyro_without_bias();

#include <Wire.h>

float rb, pb, yb, axb, ayb, azb;  // bias values
double previous, delta_time;

// to store values gyro and acceleration values
float roll, pitch, yaw, accX, accY, accZ;
float real_roll, real_pitch, real_yaw;

// for frequecy of execution
int time_step = 4;
double prev_time = millis();

float g_roll, g_pitch, g_yaw;
float a_roll, a_pitch;

void gyro_setup() {
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
  // bias_values();
  // i get this values from calibration
  rb = 2.58;
  pb = -1.93;
  yb = 0.4;
  axb = 0.01;
  ayb = -0.05;
  azb = -0.11;
}

void setup() {
  gyro_setup();
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
  yaw = (float)gyroZ / 65.;

  accX = ((float)accelX / 4096) - axb;
  accY = ((float)accelY / 4096) - ayb;
  accZ = ((float)accelZ / 4096) - azb;
  // Serial.print("\t");
  // Serial.print(accX);
  // Serial.print("\t");
  // Serial.print(accY);
  // Serial.print("\t");
  // Serial.println(accZ);
}

void gyro_without_bias() {
  get_gyro_values();

  // g_roll += (roll - rb) * (time_step * 4.5 / 1000.0);
  g_pitch += (pitch - pb) * (time_step * 4.5 / 1000.0);
  // g_yaw += (yaw - yb) * (time_step * 4.5 / 1000.0);

  // a_roll = atan2(accY, accZ) * 180.0 / PI;
  a_pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;

  float complimentary_gain = 0.8;
  // real_roll = complimentary_gain * g_roll + (1 - complimentary_gain) * a_roll;
  real_pitch = complimentary_gain * g_pitch + (1 - complimentary_gain) * a_pitch;
  // real_yaw = g_yaw;

  // settings measured values to use them in pid controller
  // using complimentary filter to get the values
  // measures[0] = yaw;
  // measures[1] = pitch;
  // measures[2] = roll;
}


void loop() {
  if (millis() - prev_time >= time_step) {
    prev_time = millis();

    // get_gyro_values();

    gyro_without_bias();

    // real_roll += (roll - rb) * (time_step * 4.5 / 1000.0);
    // real_pitch += (pitch - pb) * (time_step * 4.5 / 1000.0);
    // real_yaw += (yaw - yb) * (time_step * 4.5 / 1000.0);


    Serial.print("\t");
    Serial.print(a_pitch);
    Serial.print("\t");
    Serial.print(g_pitch);
    Serial.print("\t");
    Serial.println(real_pitch);


    // Serial.print("\t");
    // Serial.print(time_step);
    // Serial.print("\t");
    // Serial.print(roll - rb);
    // Serial.print("\t");
    // Serial.print(real_roll);
    // Serial.print("\t");
    // Serial.print(pitch - pb);
    // Serial.print("\t");
    // Serial.println(real_pitch);
    // Serial.print("\t");
    // Serial.print(yaw - yb);
    // Serial.print("\t");
    // Serial.println(real_yaw);
  }
}
