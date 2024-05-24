/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo
Servo myservo5;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;  // variable to store the servo position
int count = 0;

void setup() {
  Serial.begin(9600);
  myservo1.attach(3);   // attaches the servo on pin 9 to the servo object
  myservo2.attach(5);   // attaches the servo on pin 9 to the servo object
  myservo3.attach(6);   // attaches the servo on pin 9 to the servo object
  myservo4.attach(9);   // attaches the servo on pin 9 to the servo object
  myservo5.attach(10);  // attaches the servo on pin 9 to the servo object
  analogWrite(A4, 255);
  Serial.println("hello guys");
}

void loop() {
  // myservo.write(180);              // tell servo to go to position in variable 'pos'
  // delay(1000);
  myservo1.write(0);  // tell servo to go to position in variable 'pos'
  myservo2.write(0);  // tell servo to go to position in variable 'pos'
  myservo3.write(0);  // tell servo to go to position in variable 'pos'
  myservo4.write(0);  // tell servo to go to position in variable 'pos'
  myservo5.write(0);  // tell servo to go to position in variable 'pos'

  for (pos = 0; pos <= 180; pos += 10) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);  // tell servo to go to position in variable 'pos'
    myservo2.write(pos);  // tell servo to go to position in variable 'pos'
    myservo3.write(pos);  // tell servo to go to position in variable 'pos'
    myservo4.write(pos);  // tell servo to go to position in variable 'pos'
    myservo5.write(pos);  // tell servo to go to position in variable 'pos'
    count++;
    Serial.println(count);
    delay(05);  // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 10) {  // goes from 180 degrees to 0 degrees
    myservo1.write(pos);                  // tell servo to go to position in variable 'pos'
    myservo2.write(pos);                  // tell servo to go to position in variable 'pos'
    myservo3.write(pos);                  // tell servo to go to position in variable 'pos'
    myservo4.write(pos);                  // tell servo to go to position in variable 'pos'
    myservo5.write(pos);                  // tell servo to go to position in variable 'pos'
    Serial.println(count);
    count++;
    delay(50);  // waits 15 ms for the servo to reach the position
  }
  // Serial.println(count);
  // delay(150);  // waits 15 ms for the servo to reach the position
}
