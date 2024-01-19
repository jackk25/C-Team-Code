/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jackk25, RobotKayla                                       */
/*    Created:      Wed Sep 20 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "replay.h"
#include "screen.h"
#include <vector>

using namespace vex;

competition mainCompetition;

motor_group leftDrive(leftFront, leftBack);
motor_group rightDrive(rightFront, rightBack);
drivetrain mainDrive = drivetrain(leftDrive, rightDrive, 319.19, 320, 260, mm, 1);

motor intake = motor(PORT9, ratio18_1, false);
motor launcherMotorA = motor(PORT10, ratio18_1, false);
motor launcherMotorB = motor(PORT20, ratio18_1, true);
motor_group launcher = motor_group(launcherMotorA, launcherMotorB);

void autonControl(){
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
  launcher.spin(forward);
  Brain.Screen.print("AUton 1");
}

void autonControl2(){
  mainDrive.driveFor(forward, 46, inches);
  launcher.spin(forward);
  Brain.Screen.print("AUton 2");
}

void motorSpin(motor_group dstMotor, 
              bool positiveButtonState, bool negativeButtonState, int spinRate){
  int motorSpeed = (positiveButtonState * spinRate) - (negativeButtonState * spinRate);
  dstMotor.spin(forward, motorSpeed, percent);
}

bool oppositeSigns(int x, int y)
{
  return ((x ^ y) < 0);
}

void driveCode() {
  Controller1.ButtonA.pressed(nestedListToSD);
  while(true) {
    int32_t leftDriveStrength = Controller1.Axis3.position()/1.25;
    int32_t rightDriveStrength = Controller1.Axis2.position()/1.25;

    //Drive strength modifier for turning
    if(oppositeSigns(leftDriveStrength, rightDriveStrength)){
      leftDriveStrength = leftDriveStrength/1.5;
      rightDriveStrength = rightDriveStrength/1.5;
    }

    leftDrive.spin(forward, leftDriveStrength, pct);
    rightDrive.spin(forward, rightDriveStrength, pct);

    motorSpin(intake, Controller1.ButtonL1.pressing(), Controller1.ButtonL2.pressing(), 100);
    motorSpin(launcher, false, Controller1.ButtonR1.pressing(), 100);
  }
}

void rumbleTest(int id){
  if(id == 0 || id == 2) {
      Controller1.rumble(".");
  }
  else if(id == 1 || id == 3){
      Controller1.rumble("..");
  }
}

std::vector<void (*)()> autonList = {
  autonControl,
  autonControl2
};

int currentAutonId = 0;

void switchAuton(int buttonId){
  if(buttonId == 2){
    // Push it left
    currentAutonId--;
    Controller1.rumble(".");
  }
  if(buttonId == 3){
    // Push it right
    currentAutonId++;
    Controller1.rumble(".");
  }
}

ScreenContainer container;

void runThroughButtons(){
  container.runThroughButtons();
}

void getAuton(){
  mainCompetition.autonomous(autonList[currentAutonId]);
  mainCompetition.test_auton();
}

void createButtons(){
  // Fun Buttons
  Brain.Screen.setFillColor(blue);
  container.createButton({20, 100}, rumbleTest, "Beep");
  Brain.Screen.setFillColor(red);
  container.createButton({100, 100}, rumbleTest, "Buzz");
  Brain.Screen.setFillColor(green);

  //Auton Control
  container.createButton({100, 200}, switchAuton, "<");
  container.createButton({300, 200}, switchAuton, ">");
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  createButtons();

  mainCompetition.autonomous(autonControl);
  mainCompetition.drivercontrol(driveCode);
  Brain.Screen.pressed(runThroughButtons);
}
