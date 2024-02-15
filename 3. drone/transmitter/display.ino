#include <LiquidCrystal.h>

const int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
// int vdd = 13, v0 = 12, rw = 10, rs = 11, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2, a = 1, k = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void display_setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Tras Started!");
}

void disp_measures() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("r : ");
  lcd.print(data.roll);
  lcd.print("p : ");
  lcd.print(data.pitch);
  lcd.setCursor(1, 1);
  lcd.print("y : ");
  lcd.print(data.yaw);
  lcd.print("t : ");
  lcd.print(data.throttle);
}

void disp_radio_check(bool status) {
  lcd.setCursor(1, 0);
  lcd.print("radio check: ");
  lcd.setCursor(1, 1);
  if (status) {
    lcd.print("success");
  } else {
    lcd.print("failed");
  }
}