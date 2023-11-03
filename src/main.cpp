/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jackk25, RobotKayla                                       */
/*    Created:      Wed Sep 20 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "gps.h"

using namespace vex;

competition mainCompetition;

motor_group leftDrive(leftFront, leftBack);
motor_group rightDrive(rightFront, rightBack);
smartdrive mainDrive(leftDrive, rightDrive, GPS15, 320, 365, 260, mm, 1);

void autonCode() {
  hopeThisWorks();
}

void driveCode() {
  while(true) {
    leftDrive.spin(forward, Controller1.Axis3.position(), pct);
    rightDrive.spin(forward, Controller1.Axis2.position(), pct);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  mainCompetition.autonomous(autonCode);
  mainCompetition.drivercontrol(driveCode);
}
