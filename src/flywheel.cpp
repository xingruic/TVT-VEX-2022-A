#include "flywheel.h"
#include "vex.h"

using namespace vex;

double maxFly=0;

int FSpeed=0;
int prev_error=-1;
int tbh=0;
const double gain=0.1;
int getFlywheelSpeed(int speed){
  FSpeed=MotorF2.velocity(percent);
  int error=speed-FSpeed;
  int output=FSpeed+error*gain;
  if(signbit(error)!=signbit(prev_error)){
    output=0.5*(output+tbh);
    tbh=output;
    prev_error=error;
  }
  return output;
}

void spinFly(int speed){
  speed=getFlywheelSpeed(speed);
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
  MotorOut.spin(reverse, 100, percent);
  wait(80, msec);
  MotorOut.spin(forward, 100, percent);
  wait(140, msec);
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