// // use get_battery_level function to get the values
// void get_battery_level() {
//   int level = analogRead(battery);

//   float reference_voltage = 1.1;
//   float analog_value_per_volt = 1024 / reference_voltage;

//   float resistor_divider = (1.0 / 23.0);  // (output resistance)/(total resistance)

//   float battery_max_voltage = 4.3;// for 1s battery
//   float battery_min_voltage = 3.71;
//   // float battery_max_voltage = 12.6; // for 3s battery
//   // float battery_min_voltage = 11.12;

//   float battery_max_level_analog_value = battery_max_voltage * resistor_divider * analog_value_per_volt;
//   float battery_min_level_analog_value = battery_min_voltage * resistor_divider * analog_value_per_volt;
  
//   battery_level = map(level, battery_min_level_analog_value, battery_max_level_analog_value, 15, 100);

//   Serial.print(battery_max_level_analog_value);
//   Serial.print("\t");
//   Serial.print(battery_min_level_analog_value);
//   Serial.print("\t");
//   Serial.print(level);
//   Serial.print("\t");
//   Serial.println(battery_level);
// }