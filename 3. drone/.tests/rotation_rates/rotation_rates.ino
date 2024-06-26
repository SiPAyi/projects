// // first use gyro_setup function in the setup section
// // use this function to get values;
// get_gyro_values();
// gyro_without_bias();

#include <Wire.h>


// to store values gyro and acceleration values
float roll, pitch, yaw, accX, accY, accZ;  // raw values
float rb, pb, yb, axb, ayb, azb;           // bias values
float g_roll, g_pitch, g_yaw;              // rotations from gyro
float a_roll, a_pitch;                     // rotations from accelerometer
float real_roll, real_pitch, real_yaw;     // filtered values


// for frequecy of execution
int time_step = 4;
double prev_time = millis();

int measures[3] = { 0, 0, 0 };

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
  // bias_values();
  // i get this values from calibration for mpu1
  rb = 1.41;
  pb = -1.75;
  yb = -0.79;

  // i got this values from calibration of new mpu
  // rb = 3.1091;
  // pb = 2.70;
  // yb = -0.46;
  // axb = 0.00;
  // ayb = -0.01;
  // azb = 1.12;
  // i get this values from calibration for mpu1
  // rb = 2.35508;
  // pb = -1.90995;
  // yb = 0.184536;
  // axb = 0.01;
  // ayb = -0.05;
  // azb = -0.11;

  // get_gyro_values();

  // // // setting the initial angle to the gyrovalues
  // a_roll = atan2(accY, accZ) * 180.0 / PI;
  // a_pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;
  // g_roll = a_roll;
  // g_pitch = a_pitch;
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

  // accX = ((float)accelX / 4096) - axb;
  // accY = ((float)accelY / 4096) - ayb;
  // accZ = ((float)accelZ / 4096) - azb;

  // Serial.println(String() + F("\t ") + accX + F("\t ") + accY + F("\t ") + accZ + F("\t ") + roll + F("\t ") + pitch + F("\t ") + yaw);
  // Serial.println(String() + F("\taccX: ") + accX + F("\taccY: ") + accY + F("\taccZ: ") + accZ + F("\troll: ") + roll + F("\tpitch: ") + pitch + F("\tyaw: ") + yaw);
}

void gyro_without_bias() {
  get_gyro_values();

  g_roll += (roll - rb) * (time_step * 5.5 / 1000.0);
  g_pitch += (pitch - pb) * (time_step * 5.5 / 1000.0);
  g_yaw += (yaw - yb) * (time_step * 5.5 / 1000.0);

  Serial.println(String() + g_roll + F("\t") + g_pitch + F("\t") + g_yaw);


  // a_roll = atan2(accY, accZ) * 180.0 / PI;
  // a_pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;

  // float complimentary_gain = 0.98;
  // real_roll = complimentary_gain * g_roll + (1 - complimentary_gain) * a_roll;
  // real_pitch = complimentary_gain * g_pitch + (1 - complimentary_gain) * a_pitch;
  // real_yaw = g_yaw;

  // settings measured values to use them in pid controller
  // using complimentary filter to get the values
  // measures[0] = real_roll;
  // measures[1] = real_pitch;
  // measures[2] = real_yaw;
}

void setup() {
  Serial.begin(115200);
  gyro_setup();
  Serial.println(String() + F("\taccX: ") + F("\taccY: ") + F("\taccZ: ") + F("\troll: ") + F("\tpitch: ") + F("\tyaw: "));
}

void loop() {
  if (millis() - prev_time >= time_step) {
    prev_time = millis();

    // get_gyro_values();

    gyro_without_bias();

    // Serial.print("\t");
    // Serial.print(measures[0]);
    // Serial.print("\t");
    // Serial.print(measures[1]);
    // Serial.print("\t");
    // Serial.println(measures[2]);

    // Serial.print(g_roll);
    // Serial.print(", ");
    // Serial.print(g_pitch);
    // Serial.print(", ");
    // Serial.println(g_yaw);
  }
}

void bias_values() {
  Serial.println("wait bro im calibrating mpu6050");
  int n = 2000;  // number of times need to sum
  int roll_sum = 0;
  int pitch_sum = 0;
  int yaw_sum = 0;
  int accX_sum = 0;
  int accY_sum = 0;
  int accZ_sum = 0;

  for (int i = 0; i < n; i++) {
    get_gyro_values();
    roll_sum += roll;
    pitch_sum += pitch;
    yaw_sum += yaw;
    accX_sum += accX;
    accY_sum += accY;
    accZ_sum += accZ;
    Serial.print(".");
  }
  n = (float)n;
  rb = roll_sum / n;
  pb = pitch_sum / n;
  yb = yaw_sum / n;
  axb = accX_sum / n;
  ayb = accY_sum / n;
  azb = accZ_sum / n;

  Serial.println("calibrated");
  Serial.println("roll \t pitch \t yaw");

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
  delay(5000);
}