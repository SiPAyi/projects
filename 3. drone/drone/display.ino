// as we are not going to add any display to the drone
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// void display_setup() {
//   // analogWrite(A3, 255);
//   // analogWrite(A2, 0);
//   lcd.init();  // initialize the lcd
//   // Print a message to the LCD.
//   lcd.setCursor(1, 0);
//   lcd.print("Drone Starting!");
//   Serial.println("Drone Starting!");
//   lcd.setCursor(1, 1);
//   // for (int i = 0; i < 3; i++) {
//   //   lcd.print(3 - i);
//   //   lcd.print(" ");
//   //   Serial.print(3 - i);
//   //   Serial.print("\t");
//   //   delay(1000);
//   // }
// }

// void disp_gyro_check(bool status) {
//   lcd.clear();
//   lcd.setCursor(1, 0);
//   lcd.print("gyro check: ");
//   lcd.setCursor(1, 1);
//   if (status) {
//     lcd.print("success");
//   } else {
//     lcd.print("failed");
//   }
// }

// void disp_radio_check(bool status) {
//   lcd.clear();
//   lcd.setCursor(1, 0);
//   lcd.print("radio check: ");
//   lcd.setCursor(1, 1);
//   if (status) {
//     lcd.print("success");
//   } else {
//     lcd.print("failed");
//   }
// }

// void disp_measures() {
//   lcd.clear();
//   lcd.setCursor(1, 0);
//   lcd.print("r:");
//   lcd.print(measures[ROLL]);
//   lcd.print("p:");
//   lcd.print(measures[PITCH]);
//   lcd.setCursor(1, 1);
//   lcd.print("y:");
//   lcd.print(measures[YAW]);
//   lcd.print("t:");
//   lcd.print(measures[THROTTLE]);

//   // lcd.clear();
//   // lcd.setCursor(1, 0);
//   // lcd.print("r:");
//   // lcd.print(instruction[ROLL]);
//   // lcd.print("p:");
//   // lcd.print(instruction[PITCH]);
//   // lcd.setCursor(1, 1);
//   // lcd.print("y:");
//   // lcd.print(instruction[YAW]);
//   // lcd.print("t:");
//   // lcd.print(instruction[THROTTLE]);

//   Serial.print("r:");
//   Serial.print(measures[ROLL]);
//   Serial.print("\t p:");
//   Serial.print(measures[PITCH]);
//   Serial.print("\t y:");
//   Serial.print(measures[YAW]);
//   Serial.print("\t t:");
//   Serial.print(measures[THROTTLE]);
//   Serial.print("\t");
// }

// void flight_starting_indication() {
//   lcd.clear();
//   lcd.setCursor(1, 0);
//   lcd.print("Drone Started!");
//   digitalWrite(red, LOW);
//   delay(1000);
// }

// void display_motor_speed() {
//   lcd.clear();
//   lcd.setCursor(1, 0);
//   lcd.print("lf");
//   lcd.print(motor_lf_throttle);
//   lcd.print(" rf");
//   lcd.print(motor_rf_throttle);
//   lcd.setCursor(1, 1);
//   lcd.print(" lb");
//   lcd.print(motor_lb_throttle);
//   lcd.print(" rb");
//   lcd.print(motor_rb_throttle);
// }

// void display_speed(int speed) {
//   lcd.clear();
//   lcd.setCursor(1, 0);
//   lcd.print("lf");
//   lcd.print(speed);
// }