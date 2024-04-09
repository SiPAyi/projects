#include <LiquidCrystal.h>

// with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void lcd_setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("LCD STARTED");
  lcd.clear();
  lcd.print("STARTING...");
}

void display_weight(){
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("weight:");
  lcd.setCursor(1, 1);
  lcd.print(weight);
}


