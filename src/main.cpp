// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// IntakeMotor          motor         11              
// rightFront           motor         14              
// leftFront            motor         13              
// leftBack             motor         1               
// rightBack            motor         12              
// GPS15                gps           15              
// Launcher1            motor         2               
// Launcher2            motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// IntakeMotor          motor         11              
// rightFront           motor         14              
// leftFront            motor         13              
// leftBack             motor         1               
// rightBack            motor         12              
// GPS15                gps           15              
// Launcher1            motor         2               
// Motor3               motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// IntakeMotor          motor         11              
// rightFront           motor         14              
// leftFront            motor         13              
// leftBack             motor         1               
// rightBack            motor         12              
// GPS15                gps           15              
// Motor2               motor         2               
// Motor3               motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// IntakeMotor          motor         11              
// rightFront           motor         14              
// leftFront            motor         13              
// leftBack             motor         1               
// rightBack            motor         12              
// GPS15                gps           15              
// Motor2               motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----
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

int launcher() {
  Launcher1.setVelocity(10, percent);
  Launcher2.setVelocity(10, percent);
  while(true){
    Launcher1.spin(reverse);
    Launcher2.spin(forward);
  }
  return 0;
}
