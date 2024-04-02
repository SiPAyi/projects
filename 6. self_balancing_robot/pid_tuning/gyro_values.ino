// // first use gyro_setup function in the setup section
// // use this function to get values;
// get_gyro_values();
// gyro_without_bias();

#include <Wire.h>


// to store values gyro and acceleration values
float roll, pitch;      // raw values
float rb, pb;           // bias values
float g_roll, g_pitch;  // rotations from gyro

// for frequecy of execution
int time_step = 4;
double prev_time = millis();

int measures = 0;

void gyro_setup() {
  Serial.begin(9600);
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
  bias_values();
  // i get this values from calibration for mpu1
  // rb = 1.41;
  // pb = -1.75;
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


  roll = (float)gyroX / 65.5;
  pitch = (float)gyroY / 65.5;
}

void gyro_without_bias() {
  get_gyro_values();

  g_roll += (roll - rb) * time_step * (5.5 / 1000.0);
  g_pitch += (pitch - pb) * time_step * (5.5 / 1000.0);

  Serial.println(String() + F("roll: ") + g_roll + F("\tpitch: ") + g_pitch);
  measures = g_roll;
}

void bias_values() {
  Serial.println("wait bro im calibrating mpu6050");
  int n = 2000;  // number of times need to sum

  for (int i = 0; i < n; i++) {
    get_gyro_values();
    rb += roll;
    pb += pitch;
    Serial.print(".");
  }
  n = (float)n;
  rb /= n;
  pb /= n;

  Serial.println("calibrated");
  Serial.println("roll \t pitch");

  Serial.print(rb);
  Serial.print("\t");
  Serial.println(pb);
  delay(5000);
}