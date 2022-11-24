#include "autonomous.h"
#include "intake.h"
#include "flywheel.h"
#include "vex.h"

using namespace vex;

void _drive(int lS, int rS){
  MotorLF.spin(reverse,lS,percent);
  MotorLB.spin(forward,lS,percent);
  MotorRF.spin(reverse,rS,percent);
  MotorRB.spin(forward,rS,percent);
}

void driveInch(double inches){
  double pi = 3.1415926;
  int D = 4;
  MotorLF.spinFor(reverse, inches/pi/D, rev, false);
  MotorLB.spinFor(forward, inches/pi/D, rev, false);
  MotorRF.spinFor(reverse, inches/pi/D, rev, false);
  MotorRB.spinFor(forward, inches/pi/D, rev, true);
}

void spinInch(double inches){ // spins clockwise for how many inches
  double pi = 3.1415926;
  int D = 4;
  MotorLF.spinFor(reverse, inches/pi/D, rev, false);
  MotorLB.spinFor(forward, inches/pi/D, rev, false);
  MotorRF.spinFor(forward, inches/pi/D, rev, false);
  MotorRB.spinFor(reverse, inches/pi/D, rev, true);
}

void auton::Half1Discs(){
  driveInch(-5);
  spinInch(8);
  driveInch(-60);
  spinInch(12.1);
  driveInch(8);
  spinFly(100);
  wait(3300,msec);
  fireRing();
  wait(1300,msec);
  fireRing();
  fireRing();
  wait(100,msec);
  spinFly(0);
}

void auton::Half1(){
  // roller
  _drive(20,20);
  wait(200, msec);
  _drive(5, 5);
  spinIntk(-40);
  wait(400, msec);
  spinIntk(0);
  _drive(0,0);

  // NOTE: please do NOT add additional code here, I re-used this code for Half2()
  // if you want the discs code, call Half1Discs() after this
}

void auton::Half2(){
  // roller
  driveInch(28);
  spinInch(13.3);
  
  // Half1();
  // _drive(20,20);
  // wait(200, msec);
  // _drive(5, 5);
  // spinIntk(-40);
  // wait(400, msec);
  // spinIntk(0);
  // _drive(0,0);


}