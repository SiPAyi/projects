#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

int gyro_status = 0;

void setup() {
  // setting up the IMU module
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  gyro_status = 1;

  // Set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // Set gyro range to +-500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // Set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);

  Serial.begin(9600);
}

void get_imu_values(float &roll, float &pitch, float &yaw) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calculate roll and pitch using the complementary filter
  float acc_roll = atan2(a.acceleration.y, a.acceleration.z);
  float acc_pitch = atan(-a.acceleration.x / sqrt(pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)));

  static float gyro_roll = 0;
  static float gyro_pitch = 0;
  static float gyro_yaw = 0;

  // Integrate gyro values for roll, pitch, and yaw
  gyro_roll += (g.gyro.x * 0.0000611); // 1 / (gyro sensitivity, 500 deg/s)
  gyro_pitch += (g.gyro.y * 0.0000611);
  gyro_yaw += (g.gyro.z * 0.0000611);


  // Combine accelerometer and gyro values using the complementary filter
  roll = 0.98 * (gyro_roll) + 0.02 * acc_roll;
  pitch = 0.98 * (gyro_pitch) + 0.02 * acc_pitch;
  yaw = gyro_yaw;

  // Convert angles from radians to degrees
  roll = (roll * 180.0 / PI)*((180*7)/22); // i multiplied it by (180*7)/22, but i dont know why, it just worked
  pitch = (pitch * 180.0 / PI)*((180*7)/22);
  yaw = (yaw * 180.0 / PI)*((180*7)/22);
}

void loop() {
  float roll, pitch, yaw;
  get_imu_values(roll, pitch, yaw);
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print("\t Pitch: ");
  Serial.print(pitch);
  Serial.print("\t Yaw: ");
  Serial.println(yaw);

  delay(10); // Adjust the delay based on your desired sample rate
}
