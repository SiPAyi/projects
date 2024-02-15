int sw = A0;
int vry = A1;
int vrx = A2;
int vcc = A3;
int gnd = A4;

int x, y;

void setup() {
  // put your setup code here, to run once:
  pinMode(gnd, OUTPUT);
  pinMode(vcc, OUTPUT);
  pinMode(vrx, INPUT);
  pinMode(vry, INPUT);

  analogWrite(gnd, 0);
  analogWrite(vcc, 255);
  Serial.begin(9600);
  Serial.println("trying to get the potentiometer values");
}

void loop() {
  x = analogRead(vrx);
  y = analogRead(vry);

  Serial.print(" x : ");
  Serial.print(x);
  Serial.print(" y : ");
  Serial.println(y);
  delay(200);
}
