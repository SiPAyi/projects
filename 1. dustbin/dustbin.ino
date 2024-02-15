#include <Servo.h>
Servo servo;

int servo_pin = 8;

int ir = 9;
int ir_gnd = 10;
int ir_vcc = 11;


void setup() {
  servo.attach(servo_pin);
  pinMode(ir_gnd, OUTPUT);
  pinMode(ir_vcc, OUTPUT);
  pinMode(ir, INPUT);

  digitalWrite(ir_vcc, HIGH);
  digitalWrite(ir_gnd, LOW);

  Serial.begin(9600);
}


void loop() {
  

  if(digitalRead(ir)==0){
    Serial.println("someone is here, opening dustbin");
    for(int i=0; i<=90; i+=5){
      servo.write(i);
      delay(50);
    }
    delay(2000);

        for(int i=90; i>=0; i-=5){
      servo.write(i);
      delay(50);
    }

  }
  else{
    Serial.println("no one is here, closing dustbin");
  servo.write(0);
  }

  delay(1000);

}
