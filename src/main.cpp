// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// MotorLF              motor         3
// MotorLB              motor         4
// MotorRF              motor         11
// MotorRB              motor         20
// MotorIntk            motor         5
// MotorF1              motor         6
// MotorF2              motor         7
// MotorOut             motor         8
// Pneu1                digital_out   A
// Pneu2                digital_out   B
// Pneu3                digital_out   C
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// MotorLF              motor         3
// MotorLB              motor         4
// MotorRF              motor         11
// MotorRB              motor         20
// MotorIntk            motor         5
// MotorF1              motor         6
// MotorF2              motor         7
// MotorOut             motor         8
// Pneu1                digital_out   A
// Pneu2                digital_out   B
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "autonomous.h"
#include "expansion.h"
#include "flywheel.h"
#include "intake.h"
#include "vex.h"


using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

bool FlyGlobalBool = 0;

void toggleFly() { FlyGlobalBool = !FlyGlobalBool; }

// give lSpeed and rSpeed in percent
void drive(int lS, int rS) {
  MotorLF.spin(reverse, lS, percent);
  MotorLB.spin(forward, lS, percent);
  MotorRF.spin(reverse, rS, percent);
  MotorRB.spin(forward, rS, percent);
  MotorLB.setBrake(brake);
  MotorLF.setBrake(brake);
  MotorRB.setBrake(brake);
  MotorRF.setBrake(brake);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Pneu1.set(true);
  Pneu2.set(true);
  Pneu3.set(true);

  MotorOut.setBrake(brake);
  MotorF1.setBrake(coast);
  MotorF2.setBrake(coast);

  MotorLF.setVelocity(50, percent);
  MotorLB.setVelocity(50, percent);
  MotorRF.setVelocity(50, percent);
  MotorRB.setVelocity(50, percent);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

  // auton::Half2(); // right side

  auton::Half1();
  auton::Half1Discs(); // left side
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void singleRightDrive() {
  int LR = Controller1.Axis1.position();
  int FB = Controller1.Axis2.position();
  double lD = LR * 0.7;
  double rD = -LR * 0.7;
  lD += FB;
  rD += FB;
  if (lD > 100)
    lD = 100;
  if (rD > 100)
    rD = 100;
  if (lD < -100)
    lD = -100;
  if (rD < -100)
    rD = -100;

  drive(lD, rD);
}

void singleLeftDrive() {
  int LR = Controller1.Axis4.position();
  int FB = Controller1.Axis3.position();
  double lD = LR * 0.7;
  double rD = -LR * 0.7;
  lD += FB;
  rD += FB;
  if (lD > 100)
    lD = 100;
  if (rD > 100)
    rD = 100;
  if (lD < -100)
    lD = -100;
  if (rD < -100)
    rD = -100;

  drive(lD, rD);
}

void splitDrive() {
  int LR = Controller1.Axis1.position();
  float FB = Controller1.Axis3.position() * 0.9;
  double lD = LR * 0.7;
  double rD = -LR * 0.7;
  lD += FB;
  rD += FB;
  if (lD > 100)
    lD = 100;
  if (rD > 100)
    rD = 100;
  if (lD < -100)
    lD = -100;
  if (rD < -100)
    rD = -100;

  drive(lD, rD);
}

int lOld = 0, rOld = 0;
void tankDrive() {
  int l = Controller1.Axis3.position();
  int r = Controller1.Axis2.position();
  if (lOld > 0 && l < lOld)
    l = fmax(lOld - 15, l);
  else if (lOld < 0 && l > lOld)
    l = fmin(lOld + 15, l);
  if (rOld > 0 && r < rOld)
    r = fmax(rOld - 15, r);
  else if (rOld < 0 && r > rOld)
    r = fmin(rOld + 15, r);
  lOld=l;
  rOld=r;
  drive(l, r);
}

void usercontrol(void) {
  bool spinningFly = 0;
  // User control code here, inside the loop

  Controller1.ButtonR1.pressed(fireRing);
  Controller1.ButtonR2.pressed(toggleFly);
  Controller1.ButtonA.pressed(tripleFire);

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    splitDrive();

    if (Controller1.ButtonL1.pressing())
      spinIntk(100);
    else if (Controller1.ButtonL2.pressing())
      spinIntk(-70);
    else
      spinIntk(0);

    if (Controller1.ButtonUp.pressing()) {
      spinningFly = 1;
    } else if (Controller1.ButtonDown.pressing()) {
      spinningFly = 0;
    }
    if (spinningFly) {
      spinFly(77);
    } else {
      spinFly(0);
    }

    if (Controller1.ButtonRight.pressing() && Controller1.ButtonY.pressing()) {
      Pneu1.set(false);
      Pneu2.set(false);
      Pneu3.set(false);
    }

    wait(30, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
