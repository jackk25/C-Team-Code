/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jackk25, RobotKayla                                       */
/*    Created:      Wed Sep 20 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "screen/ScreenContainer.h"

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

void switchAuton(int buttonId){
  Controller1.rumble(".");
  if(buttonId == 2){
    skills = false;
  }
  if(buttonId == 3){
    skills = true;
  }
}

ScreenContainer container;

void runThroughButtons(){
  container.runThroughButtons();
}

void createButtons(){
  // Fun Buttons

  Brain.Screen.setFillColor(blue);
  ScreenButton beepBtn = ScreenButton(0, {20, 100}, rumbleTest, "Beep");
  container.addButton(beepBtn);
  //container.createButton({20, 100}, rumbleTest, "Beep");
  
  Brain.Screen.setFillColor(red);
  ScreenButton buzzButton = ScreenButton(1, {100, 100}, rumbleTest, "Buzz");
  container.addButton(buzzButton);
  //container.createButton({100, 100}, rumbleTest, "Buzz");

  //Auton Control
  Brain.Screen.setFillColor(purple);
  ScreenButton compButton = ScreenButton(2, {100, 200}, switchAuton, "Competition");
  container.addButton(compButton);
  //container.createButton({100, 200}, switchAuton, "Competition");

  Brain.Screen.setFillColor(cyan);
  ScreenButton skillsButton = ScreenButton(3, {300, 200}, switchAuton, "Skills");
  container.addButton(skillsButton);
  //container.createButton({300, 200}, switchAuton, "Skills");

  container.draw();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  createButtons();

  mainCompetition.autonomous(autonControl);
  mainCompetition.drivercontrol(driveCode);
  Brain.Screen.pressed(runThroughButtons);
}
