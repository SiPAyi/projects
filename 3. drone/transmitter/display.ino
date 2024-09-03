#include <LiquidCrystal.h>

const int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 5;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void display_setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  // Print a message to the LCD.
  lcd.print("Started..");
}

// led part
void radio_connected_led()
{
  digitalWrite(status_led, 1);
  delay(200);
  digitalWrite(status_led, 0);
  delay(200);
  digitalWrite(status_led, 1);
  delay(200);
  digitalWrite(status_led, 0);
  delay(200);
}

void lcd_print(String message, int row, int col)
{
  lcd.clear();
  lcd.setCursor(col, row);
  lcd.print(message);
}

void lcd_print_wrap(String msg)
{
  int len = msg.length();

  // Clear the LCD
  lcd.clear();

  // Determine the length for each row
  int row1Len = min(len, 16);
  int row2Len = min(len - row1Len, 16);

  // Extract substrings for each row
  String row1 = msg.substring(0, row1Len);
  String row2 = msg.substring(16, 16 + row2Len);

  // Set cursor and print first row
  lcd.setCursor(0, 0);
  lcd.print(row1);

  // Set cursor and print second row
  lcd.setCursor(0, 1);
  lcd.print(row2);
}

void show_orientation()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("rol:");
  lcd.print(125);
  lcd.print(" pit:");
  lcd.print(125);
  lcd.setCursor(0, 1);
  lcd.print("yaw:");
  lcd.print(125);
  lcd.print(" thr:");
  lcd.print(125);
}

void show_battery_levels()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Drone_bat : ");
  lcd.print(100);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Trans_bat : ");
  lcd.print(100);
  lcd.print("%");
}

void sensorCalibModeDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print("Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Calibration Mode");
}

void pidModeDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print("PID");
  lcd.setCursor(0, 1);
  lcd.print("Tuning Mode");
}

void altitudeHoldDisplay(){
    lcd.setCursor(0, 0);
  lcd.print("Altitude Hold");
  lcd.setCursor(0, 1);
  lcd.print("Mode");
}