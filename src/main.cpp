// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Motor10              motor         10              
// Motor11              motor         11              
// MyGPS                gps           12              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Motor10              motor         10              
// Motor11              motor         11              
// GPS12                gps           12              
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jackk25, RobotKayla                                       */
/*    Created:      Wed Sep 20 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Motor10              motor         10              
// Motor11              motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition mainCompetition;

drivetrain mainDrive(Motor10, Motor11);

void autonCode() {}

void driveCode() {
  while(true) {
    Motor10.spin(forward, -Controller1.Axis2.position(), pct);
    Motor11.spin(forward, Controller1.Axis3.position(), pct);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  mainCompetition.autonomous(autonCode);
  mainCompetition.drivercontrol(driveCode);
}
