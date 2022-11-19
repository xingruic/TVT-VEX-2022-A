#include "flywheel.h"
#include "vex.h"

using namespace vex;

double maxFly=0;

void spinFly(int speed){
  MotorF1.spin(forward, speed, percent);
  MotorF2.spin(forward, speed, percent);
  // if(speed>0 && MotorF2.velocity(percent)>speed*0.8 && MotorF2.velocity(percent)>oldFly){
  //   Controller1.rumble(".");
  // }else{
  //   Controller1.rumble(" ");
  // }
  maxFly=maxFly>MotorF2.velocity(percent)?maxFly:MotorF2.velocity(percent);
  Brain.Screen.printAt(30,30,"maximum flywheel speed: %.2f                  ", maxFly);
}

// fire ring
void fireRing(){
  MotorOut.spin(forward, 100, percent);
  wait(275, msec);
  MotorOut.spin(reverse, 100, percent);
  wait(350, msec);
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