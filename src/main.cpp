/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jackk25, RobotKayla                                       */
/*    Created:      Wed Sep 20 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "screen.h"
#include "img.h"

using namespace vex;

competition mainCompetition;

motor_group leftDrive(leftFront, leftBack);
motor_group rightDrive(rightFront, rightBack);
drivetrain mainDrive = drivetrain(leftDrive, rightDrive, 319.19, 320, 260, mm, 1);

motor intake = motor(PORT9, ratio18_1, false);
motor launcher = motor(PORT20, ratio6_1, true);

bool skills = false;

void autonControl(){
  if (skills == false){
    Brain.Screen.print("Competition!");
    mainDrive.driveFor(forward, 46, inches);
    mainDrive.turnFor(right, 45, degrees);
    mainDrive.driveFor(forward, 6, inches);
    intake.spin(reverse);
    mainDrive.driveFor(reverse, 12, inches);
    //DESTROY THE GOAL!!!!
    mainDrive.setDriveVelocity(75, pct);
    mainDrive.driveFor(forward, 20, inches);
    mainDrive.setDriveVelocity(50, pct);
    mainDrive.driveFor(reverse, 12, inches);
    intake.spin(forward);
  }
  if (skills){
    Brain.Screen.print("Skills!");
    launcher.setVelocity(100, pct);
    launcher.spin(forward);
  }
}

void possibleAuton(){
  intake.spinFor(left, 3, seconds);
  mainDrive.turnFor(left, 45, degrees);
  mainDrive.driveFor(forward, 6, inches);
  leftWing.set(true);
  mainDrive.turnFor(right, 10, degrees);
  mainDrive.driveFor(forward, 6, inches);
  mainDrive.turnFor(right, 35, degrees);
  mainDrive.driveFor(forward, 12, inches);
  intake.spinFor(reverse, 3, seconds);
  mainDrive.driveFor(reverse, 15, inches);
  mainDrive.turnFor(right, 90, degrees);
  mainDrive.driveFor(forward, 32, inches);
}

void possible 

void motorSpin(motor_group dstMotor, bool positiveButtonState, bool negativeButtonState, int spinRate){
  int motorSpeed = (positiveButtonState * spinRate) - (negativeButtonState * spinRate);
  dstMotor.spin(forward, motorSpeed, percent);
}

bool oppositeSigns(int x, int y)
{
  return ((x ^ y) < 0);
}

void driveCode() {
  while(true) {
    int32_t leftDriveStrength = Controller1.Axis3.position();
    int32_t rightDriveStrength = Controller1.Axis2.position();

    //Drive strength modifier for turning
    if(oppositeSigns(leftDriveStrength, rightDriveStrength)){
      leftDriveStrength = leftDriveStrength/1.5;
      rightDriveStrength = rightDriveStrength/1.5;
    }

    leftDrive.spin(forward, leftDriveStrength, pct);
    rightDrive.spin(forward, rightDriveStrength, pct);

    motorSpin(intake, Controller1.ButtonL1.pressing(), Controller1.ButtonL2.pressing(), 100);
    motorSpin(launcher, false, Controller1.ButtonR1.pressing(), 85);
    
    if(Controller1.ButtonUp.pressing()){
      leftWing.set(true);
      rightWing.set(true);
    }
    if (Controller1.ButtonDown.pressing()) {
      leftWing.set(false);
      rightWing.set(false);
    }
    
  }
}

void switchAuton(int buttonId){
  Controller1.rumble(".");
  if(buttonId <= 3){
    skills = false;
  }
  if(buttonId == 4){
    skills = true;
  }
}

ScreenContainer container;

void runThroughButtons(){
  container.runThroughButtons();
}

void createButtons(){
  //Colors
  color blueColor = color(110, 200, 250);
  color redColor = color(250, 105, 130);
  color purpleColor = color(220, 110, 165);

  //Auton Control
  Brain.Screen.setFillColor(redColor);
  container.createButton({42, 238}, switchAuton); //id: 0 
  container.createButton({42, 60}, switchAuton); //id: 1

  Brain.Screen.setFillColor(blueColor);
  container.createButton({224, 238}, switchAuton); //id: 2
  container.createButton({224, 60}, switchAuton); //id: 3

  Brain.Screen.setFillColor(purpleColor);
  container.createButton({352, 163}, switchAuton); //id: 4
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Brain.Screen.drawImageFromBuffer(screenBackground, 0, 0, 75468);

  leftWing.set(false);
  rightWing.set(false);

  createButtons();

  mainCompetition.autonomous(autonControl);
  mainCompetition.drivercontrol(driveCode);
  Brain.Screen.pressed(runThroughButtons);
}
