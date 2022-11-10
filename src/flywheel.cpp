#include "flywheel.h"
#include "vex.h"

using namespace vex;

int oldFly;

void spinFly(int speed){
  MotorF1.spin(forward, speed, percent);
  MotorF2.spin(forward, speed, percent);
  // if(speed>0 && MotorF2.velocity(percent)>speed*0.8 && MotorF2.velocity(percent)>oldFly){
  //   Controller1.rumble(".");
  // }else{
  //   Controller1.rumble(" ");
  // }
  oldFly=MotorF2.velocity(percent);
  Brain.Screen.printAt(30,30,"flywheel speed: %.2f                  ", MotorF2.velocity(percent));
}

// fire ring
void fireRing(){
  MotorOut.spin(forward, 100, percent);
  wait(150, msec);
  MotorOut.spin(reverse, 100, percent);
  wait(200, msec);
  MotorOut.spin(forward, 0, percent);
}

void tripleFire(){
  fireRing();
  wait(30,msec);
  fireRing();
  wait(30,msec);
  fireRing();
  wait(30,msec);
}