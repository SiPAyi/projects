// this code for testing each ir sensor, directly connecting to arduino uno board

// for qtr sensor
int A_out = A0, D_out = A1, gnd = A2, vcc = A3, A2_out = A4, A3_out = A5;

// for ir sensor
int d_ir = 2;
int d_gnd = d_ir + 1;
int d_vcc = d_ir + 2;
int test_led = 13;  // we can't use serial port while using the sensor at rx/tx pins

void setup() {
  analogWrite(gnd, 0);
  analogWrite(vcc, 255);
  Serial.begin(9600);

  // for normal ir sensor
  pinMode(d_ir, INPUT);
  pinMode(d_gnd, OUTPUT);
  pinMode(d_vcc, OUTPUT);
  pinMode(test_led, OUTPUT);

  digitalWrite(d_gnd, 0);
  digitalWrite(d_vcc, 1);
}

void loop() {
  // for qtr sensor we can also use this for normal ir sensor
  int A_read = analogRead(A_out);
  int A2_read = analogRead(A2_out);
  int A3_read = analogRead(A3_out);
  // int D_read = analogRead(D_out);

  Serial.print("Analog output1 : \t");
  Serial.print(A_read);
  Serial.print("\t");

  Serial.print("Analog output2 : \t");
  Serial.print(A2_read);
  Serial.print("\t");

  Serial.print("Analog output3 : \t");
  Serial.print(A3_read);
  Serial.print("\t");

  Serial.print("Digital output : \t");
  Serial.println(digitalRead(d_ir));

  // // for ir sensor
  //   digitalWrite(test_led, digitalRead(d_ir));
}
