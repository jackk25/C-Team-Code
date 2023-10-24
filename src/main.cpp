/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jackk25, RobotKayla                                       */
/*    Created:      Wed Sep 20 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

competition mainCompetition;

motor_group leftDrive(leftFront, leftBack);
motor_group rightDrive(rightFront, rightBack);
drivetrain mainDrive(leftDrive, rightDrive, 320, 365, 260, mm, 1);

void autonCode() {}

void motorSpin(motor dstMotor, bool positiveButtonState, bool negativeButtonState, int spinRate){
  int motorSpeed = (positiveButtonState * spinRate) - (negativeButtonState * spinRate);
  dstMotor.spin(forward, motorSpeed, percent);
}

void driveCode() {
  while(true) {
    leftDrive.spin(forward, Controller1.Axis3.position(), pct);
    rightDrive.spin(forward, -Controller1.Axis2.position(), pct);
    motorSpin(IntakeMotor, Controller1.ButtonL1.pressing(), Controller1.ButtonR1.pressing(), 100);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  mainCompetition.autonomous(autonCode);
  mainCompetition.drivercontrol(driveCode);
}
