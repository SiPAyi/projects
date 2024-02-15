// /*  1.Need to connect to the transmitter and get the values [roll, pitch, yaw, throttle] */
#include <SPI.h>
#include <RF24.h>

// need this structure datatype to store the received values from nrf module
struct Signal {
  bool state;
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
};
Signal data = { 0, 0, 0, 0, 0 };  // initialized the structure
int setpoint_rpy[3] = { 0, 0, 0 };
int roll_index = 0;
int pitch_index = 1;
int yaw_index = 2;

// setup the radio
int communication_status = 0;
RF24 radio(8, 9);  // CE, CSN pins
const byte address[6] = "00001";

// call the below function which update the "data" stuctrure
void get_radio_values() {
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.startListening();

  if (radio.available()) {
    communication_status = 1;
    radio.read(&data, sizeof(Signal));
    setpoint_rpy[roll_index] = data.roll;
    setpoint_rpy[pitch_index] = data.pitch;
    setpoint_rpy[yaw_index] = data.yaw;
  } else {
    communication_status = 0;
    // need to modify to add led to indicate the status of the communication
  }
}



// /* 2. Get the readings from the imu module and find the angles [roll, pitch, yaw]*/
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// setting up the imu_module
int gyro_status = 0;
Adafruit_MPU6050 mpu;

void initialize_gyro() {
  if (!mpu.begin()) {
    while (1) {
      delay(10);
    }
  }
  gyro_status = 1;  // after finding the module
  // need to modify to add led to indicate the working of imu module

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

float rpy[3] = { 0, 0, 0 };  // initialized for storing the roll, pitch, yaw values


// we can update the rpy array with calling the below function
void get_rpy_values() {
  // before using this function initialize_gyro atleast once
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


  // Calculate roll and pitch using the complementary filter
  float acc_roll = atan2(a.acceleration.y, a.acceleration.z);
  float acc_pitch = atan(-a.acceleration.x / sqrt(pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)));

  static float gyro_roll = 0;
  static float gyro_pitch = 0;
  static float gyro_yaw = 0;

  // Integrate gyro values for roll, pitch, and yaw
  gyro_roll += (g.gyro.x * 0.0000611);  // 1 / (gyro sensitivity, 500 deg/s)
  gyro_pitch += (g.gyro.y * 0.0000611);
  gyro_yaw += (g.gyro.z * 0.0000611);

  // Combine accelerometer and gyro values using the complementary filter

  rpy[roll_index] = 0.98 * (gyro_roll) + 0.02 * acc_roll;
  rpy[pitch_index] = 0.98 * (gyro_pitch) + 0.02 * acc_pitch;
  rpy[yaw_index] = gyro_yaw;

  // Convert angles from radians to degrees
  rpy[roll_index] = (rpy[roll_index] * 180.0 / PI) * ((180 * 7) / 22);
  rpy[pitch_index] = (rpy[pitch_index] * 180.0 / PI) * ((180 * 7) / 22);
  rpy[yaw_index] = (rpy[yaw_index] * 180.0 / PI) * ((180 * 7) / 22);
}


// /*  3. Calculate the errors [roll_error, pitch_error, yaw_error] and make a pid controller to get the controller output*/

// to find the error we need the setpoints which we can get from the "data" structure
// and need current values which we can get from rpy array but we dont need to initialize it
// float setpoint_rpy[3] = {0.0, 0.0, 0.0};  // Roll, Pitch, Yaw setpoints
// float rpy[3] = {0.0, 0.0, 0.0};

// Define PID Controller Constants for Roll, Pitch, and Yaw
float Kp[3] = { 0.065, 0.059, 0.0200 };  // Proportional constant for roll, pitch, yaw
float Ki[3] = { 0.065, 0.059, 0.020 };  // Integral constant for roll, pitch, yaw
float Kd[3] = { 0.002, 0.002, 0 };  // Derivative constant for roll, pitch, yaw

// Define variables for PID calculations
float error = 0.0;
float prev_errors[3] = { 0, 0, 0 };
float integral[3] = { 0, 0, 0 };
float derivative[3] = { 0, 0, 0 };

// Define control variables
float controller_output[3] = { 0, 0, 0 };

// Define sample time (in milliseconds)
unsigned long lastTime = 0;
unsigned long sampleTime = 4;  // 1 second


void pid_controller() {
  // Calculate the time since the last loop execution
  unsigned long now = millis();
  float deltaTime = (float)(now - lastTime) / 1000.0;  // Convert to seconds

  get_radio_values();
  if (communication_status) {
    setpoint_rpy[0] = 0;
    setpoint_rpy[1] = 0;
    setpoint_rpy[2] = 0;
    data.throttle = 0;
  }
  get_rpy_values();


  // Separate PID controllers for Roll, Pitch, and Yaw
  for (int i = 0; i < 3; i++) {
    // Calculate the error
    error = setpoint_rpy[i] - rpy[i];

    // Calculate the integral term
    integral[i] += error * deltaTime;

    // Calculate the derivative term
    derivative[i] = (error - prev_errors[i]) / deltaTime;

    // Calculate the PID output
    controller_output[i] = Kp[i] * error + Ki[i] * integral[i] + Kd[i] * derivative[i];

    // Remember the current error for the next iteration
    prev_errors[i] = error;
  }

  // Update the last time variable
  lastTime = now;
}

// /* 4.based on the controller output set the motor speed*/

// m1>   <m2
//   \_f_/
//   |___|
//   /   \
// m3<   >m4

#include <Servo.h>
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

float minMax(float value, float min_value, float max_value) {
  if (value > max_value) {
    value = max_value;
  } else if (value < min_value) {
    value = min_value;
  }

  return value;
}

void set_motor_speed() {
  // controller outputs roll, pitch, yaw
  int motor1_speed = minMax(data.throttle + controller_output[0] + controller_output[1] + controller_output[2], 0, 180);
  int motor2_speed = minMax(data.throttle - controller_output[0] + controller_output[1] - controller_output[2], 0, 180);
  int motor3_speed = minMax(data.throttle + controller_output[0] - controller_output[1] - controller_output[2], 0, 180);
  int motor4_speed = minMax(data.throttle - controller_output[0] - controller_output[1] + controller_output[2], 0, 180);

  motor1.write(motor1_speed);
  motor2.write(motor2_speed);
  motor3.write(motor3_speed);
  motor4.write(motor4_speed);

  Serial.print("motor speeds \t");
  Serial.print(motor1_speed);
  Serial.print("\t");
  Serial.print(motor2_speed);
  Serial.print("\t");
  Serial.print(motor3_speed);
  Serial.print("\t");
  Serial.println(motor4_speed);
}

void stop_motors() {
  motor1.write(0);
  motor2.write(0);
  motor3.write(0);
  motor4.write(0);
}


void setup() {
  initialize_gyro();
  motor1.attach(7);
  motor2.attach(6);
  motor3.attach(5);
  motor4.attach(4);

  stop_motors();

  Serial.begin(9600);
  Serial.println("your drone is started");

  // Set the initial time it is need in pid control
  lastTime = millis();
}

void loop() {
  pid_controller();
  set_motor_speed();

  // Add a delay to control the sample time
  delay(sampleTime);
}
