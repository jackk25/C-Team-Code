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
#include "replay.h"
#include <vector>

using namespace vex;

competition mainCompetition;

drivetrain mainDrive(Motor10, Motor11);

void autonCode() {}

std::vector<motor> trackedMotors = {Motor10, Motor11};

std::vector<std::vector<int>> motorData;

void driveCode() {
  Controller1.ButtonA.pressed(nestedListToSD);
  while(true) {
    Motor10.spin(forward, -Controller1.Axis2.position(), pct);
    Motor11.spin(forward, Controller1.Axis3.position(), pct);

    std::vector<int> capturedData;

    for (motor motorVar : trackedMotors) {
      capturedData.push_back(motorVar.velocity(rpm));
    }
    motorData.push_back(capturedData);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  mainCompetition.autonomous(autonCode);
  mainCompetition.drivercontrol(driveCode);
}
