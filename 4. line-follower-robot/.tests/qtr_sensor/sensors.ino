void read_sensors() {
  ir_out1 = analogRead(ir1);
  ir_out2 = analogRead(ir2);

  Serial.print("ir1 : ");
  Serial.print(ir_out1);
  Serial.print("\t ir2 : ");
  Serial.println(ir_out2);
}

void qtr_calibration() {
  read_sensors();

  for (int i = 0; i < total_readings; i++) {
    ir_sum1 += ir_out1;
    ir_sum2 += ir_out2;
  }
  ir_center1 = ir_sum1 / total_readings;
  ir_center2 = ir_sum2 / total_readings;
  Serial.print("ir1 : ");
  Serial.print(ir_center1);
  Serial.print("\t ir2 : ");
  Serial.println(ir_center2);
}

// // the below ones are not required
// void find_all_values_setup() {
//   int ir_1_min_value = 100, ir_1_max_value = 0;
//   int ir_2_min_value = 100, ir_2_max_value = 0;
//   int center_value = 0;
// }
// void find_all_values() {
//   ir_1_min_value = (ir_out1 < ir_1_min_value) ? ir_out1 : ir_1_min_value;
//   ir_1_max_value = (ir_out1 > ir_1_max_value) ? ir_out1 : ir_1_max_value;

//   ir_2_min_value = (ir_out2 < ir_2_min_value) ? ir_out2 : ir_2_min_value;
//   ir_2_max_value = (ir_out2 > ir_2_max_value) ? ir_out2 : ir_2_max_value;

//   center_value = (ir_out1 == ir_out2) ? ir_out1 : center_value;  // center values may not be used or they are not accurate

//   Serial.print("\tmin1 : ");
//   Serial.print(ir_1_min_value);
//   Serial.print("\tmax1 : ");
//   Serial.print(ir_1_max_value);

//   Serial.print("\tmin1 : ");
//   Serial.print(ir_2_min_value);
//   Serial.print("\tmax2 : ");
//   Serial.print(ir_2_max_value);

//   Serial.print("\tcenter : ");
//   Serial.print(ir_out1);

//   // sensors values {min, max, center values are not required for our need}
//   // ir1 : xx	 ir2 : xx min1 : 35	max1 : 73	min1 : 33	max2 : 57	center : 40
//   // ir1 : xx	 ir2 : xx min1 : 35	max1 : 69	min1 : 33	max2 : 60	center : 40
//   // ir1 : xx	 ir2 : xx min1 : 35	max1 : 68	min1 : 33	max2 : 59	center : 39
//   // ir1 : 43	 ir2 : 37	min1 : 35	max1 : 72	min1 : 33	max2 : 58	center : xx
//   // ir1 : 42	 ir2 : 38	min1 : 35	max1 : 63	min1 : 33	max2 : 59	center : xx
//   // ir1 : 43	 ir2 : 37	min1 : 35	max1 : 64	min1 : 33	max2 : 58	center : xx
//   // ir1 : 43	 ir2 : 37	min1 : 35	max1 : 67	min1 : 34	max2 : 58
// }