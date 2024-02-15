#include <Servo.h>

Servo x, y; // to controll servos or arduinos based on the gyro input


  // for (int i = 0; i < 90; i++) {
  //   x.write(i);
  //   y.write(90);
  //   delay(50);
  // }
  // for (int i = 90; i > 0; i--) {
  //   x.write(90);
  //   y.write(i);
  //   delay(50);
  // }
  // for (int i = 90; i > 0; i--) {
  //   x.write(i);
  //   y.write(0);
  //   delay(50);
  // }
  // for (int i = 0; i < 90; i++) {
  //   x.write(0);
  //   y.write(i);
  //   delay(50);
  // }

  //  for(int i=0; i<360; i++){
  //    int xa = 45*cos((i*22)/(180*7));
  //    int ya = 45*sin((i*22)/(180*7));
  //    x.write(xa);
  //    y.write(ya);
  //    delay(100);
  //  }