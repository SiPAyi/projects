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

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(250);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  // bias_values(1000);
  // i got this values from calibration of new mpu
  rb = 3.153768062591552;
  pb = 2.701225519180297;
  yb = -0.467618656158447;
  axb = 0.025306832790374;
  ayb = -0.011481052637100;
  azb = 0.115818977355957;
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

  g_roll = (roll - rb) * (time_step * 5.5 / 1000.0);
  g_pitch = (pitch - pb) * (time_step * 5.5 / 1000.0);
  g_yaw = (yaw - yb) * (time_step * 5.5 / 1000.0);
}

void setup() {
  Serial.begin(9600);
  gyro_setup();
  Serial.println("\t range \t gc \t lc \t bc");
}

int gc = 0, lc = 0, bc = 0, count = 0, power = 0;
float range = 1;

void loop() {
  if (millis() - prev_time >= time_step) {
    prev_time = millis();

    gyro_without_bias();

    if (g_roll > range) {
      // delay(1000);
      // Serial.println("g_roll>0.0001");
      gc++;
    } else if (g_roll < -range) {
      // delay(1000);
      // Serial.println("its less than threshold");
      lc++;
    } else {
      // Serial.println("its in the range of -0.0001 to 0.0001");
      // delay(1000);
      bc++;
    }
    count++;

    if (count % 1000 == 0) {
      Serial.print("\t");
      Serial.print(-power);
      Serial.print("\t");
      Serial.print(gc);
      Serial.print("\t");
      Serial.print(lc);
      Serial.print("\t");
      Serial.println(bc);

      gc = lc = bc = 0;
      range *= 0.1;
      power++;
      delay(2000);
    }
  }
}

void bias_values(float n) {
  Serial.print("wait bro im calibrating mpu6050 \t");
  Serial.println(n);
  // float n = 5000.0;  // number of times need to sum

  for (int i = 0; i < (int)n; i++) {
    get_gyro_values();
    rb += roll;
    pb += pitch;
    yb += yaw;
    axb += accX;
    ayb += accY;
    azb += accZ;
  }
  rb /= n;
  pb /= n;
  yb /= n;
  axb /= n;
  ayb /= n;
  azb /= n;

  Serial.println("calibrated");
  Serial.println("roll \t pitch \t yaw");

  Serial.print(rb, 15);
  Serial.print("\t");
  Serial.print(pb, 15);
  Serial.print("\t");
  Serial.print(yb, 15);
  Serial.print("\t");

  Serial.print(axb, 15);
  Serial.print("\t");
  Serial.print(ayb, 15);
  Serial.print("\t");
  Serial.println(azb, 15);
}
