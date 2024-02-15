// // ## this code fails because of no kalman filter and gyro drift
// // // first use gyro_setup(); function in the setup section
// // // use this function to get values;
// // // gyro_without_bias();

// // i dont know wether the imu is giving readings or not it should be updated in the next iteration

// #include <Wire.h>

// // to store values gyro and acceleration values
// float roll, pitch, yaw, accX, accY, accZ;  // raw values
// float rb, pb, yb, axb, ayb, azb;           // bias values
// float g_roll, g_pitch, g_yaw;              // rotations from gyro
// float a_roll, a_pitch;                     // rotations from accelerometer
// float real_roll, real_pitch, real_yaw;     // filtered values
 
// void gyro_setup() {
//   Serial.begin(9600);
//   Wire.setClock(400000);
//   Wire.begin();

//   pinMode(13, OUTPUT);
//   digitalWrite(13, HIGH);
//   delay(250);

//   Wire.beginTransmission(0x68);
//   Wire.write(0x6B);
//   Wire.write(0x00);
//   Wire.endTransmission();

//   disp_gyro_check(1); // to display on lcd

//   // to get the bias offset values of the mpu6050
//   // for new mpu6050 values
//   rb = 3.167583703994750;
//   pb = 2.712061405181884;
//   yb = -0.457538270950317;
//   axb = 0.025306832790374;
//   ayb = -0.001481052637100;
//   azb = 0.115818977355957;
//   // calibrate_gyro(2000);
  

//   get_gyro_values();

//   // setting the initial angle to the gyrovalues
//   a_roll = atan2(accY, accZ) * 180.0 / PI;
//   a_pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;
//   g_roll = a_roll;
//   g_pitch = a_pitch;
// }

// void get_gyro_values(void) {
//   Wire.beginTransmission(0x68);
//   Wire.write(0x1A);
//   Wire.write(0x05);
//   Wire.endTransmission();

//   Wire.beginTransmission(0x68);
//   Wire.write(0x1B);
//   Wire.write(0x08);
//   Wire.endTransmission();

//   Wire.beginTransmission(0x68);
//   Wire.write(0x43);
//   Wire.endTransmission();

//   Wire.requestFrom(0x68, 6);
//   int16_t gyroX = Wire.read() << 8 | Wire.read();
//   int16_t gyroY = Wire.read() << 8 | Wire.read();
//   int16_t gyroZ = Wire.read() << 8 | Wire.read();


//   Wire.beginTransmission(0x68);
//   Wire.write(0x1C);
//   Wire.write(0x10);
//   Wire.endTransmission();

//   Wire.beginTransmission(0x68);
//   Wire.write(0x3B);
//   Wire.endTransmission();

//   Wire.requestFrom(0x68, 6);
//   int16_t accelX = Wire.read() << 8 | Wire.read();
//   int16_t accelY = Wire.read() << 8 | Wire.read();
//   int16_t accelZ = Wire.read() << 8 | Wire.read();


//   roll = (float)gyroX / 65.5;
//   pitch = (float)gyroY / 65.5;
//   yaw = (float)gyroZ / 65.;

//   accX = ((float)accelX / 4096) - axb;
//   accY = ((float)accelY / 4096) - ayb;
//   accZ = ((float)accelZ / 4096) - azb;
// }

// bool gyro_without_bias() {
//   get_gyro_values();

//   g_roll += (roll - rb) * (time_step * 4.5 / 1000.0);
//   g_pitch += (pitch - pb) * (time_step * 4.5 / 1000.0);
//   g_yaw += (yaw - yb) * (time_step * 4.5 / 1000.0);

//   a_roll = atan2(accY, accZ) * 180.0 / PI;
//   a_pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;

//   // using complimentary filter to get the values
//   float complimentary_gain = 0.98;
//   real_roll = complimentary_gain * g_roll + (1 - complimentary_gain) * a_roll;
//   real_pitch = complimentary_gain * g_pitch + (1 - complimentary_gain) * a_pitch;
//   real_yaw = g_yaw;

//   // Serial.print(g_roll);
//   // Serial.print("\t");
//   // Serial.print(g_pitch);
//   // Serial.print("\t");
//   // Serial.print(g_yaw);
//   // Serial.print("\t");
//   // Serial.print(accX);
//   // Serial.print("\t");
//   // Serial.print(accY);
//   // Serial.print("\t");
//   // Serial.println(accZ);

//   // settings measured values to use them in pid controller
//   measures[ROLL] = real_roll;
//   measures[PITCH] = real_pitch;
//   measures[YAW] = real_yaw;
//   return 1;
// }

// void calibrate_gyro(float n) {
//   Serial.print("wait bro im calibrating mpu6050 \t");
//   Serial.println(n);
//   // float n = 5000.0;  // number of times need to sum

//   for (int i = 0; i < (int)n; i++) {
//     get_gyro_values();
//     rb += roll;
//     pb += pitch;
//     yb += yaw;
//     axb += accX;
//     ayb += accY;
//     azb += accZ;
//   }
//   rb /= n;
//   pb /= n;
//   yb /= n;
//   axb /= n;
//   ayb /= n;
//   azb /= n;

//   Serial.println("calibrated");
//   Serial.println("roll \t pitch \t yaw");

//   Serial.print(rb, 15);
//   Serial.print("\t");
//   Serial.print(pb, 15);
//   Serial.print("\t");
//   Serial.print(yb, 15);
//   Serial.print("\t");

//   Serial.print(axb, 15);
//   Serial.print("\t");
//   Serial.print(ayb, 15);
//   Serial.print("\t");
//   Serial.println(azb, 15);
// }