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
}

class ScreenContainer;
class ScreenButton;

struct Point{
  int x, y;
};

typedef struct Point Point;

class ScreenButton{
  Point p1;
  Point p2;
  char buttonText[256];

  void (*execute)();

  void draw(){
    int width = p2.x-p1.x;
    int height = p2.y+p1.y;
    Brain.Screen.drawRectangle(p1.x, p1.y, width, height);

    // Center aligned vertically, left aligned horizontally
    Brain.Screen.setCursor(p1.y + (height / 2), p1.x);
    Brain.Screen.print(buttonText);
  }

  public:
    ScreenButton(Point topLeftPosition, int width, int height, void (*execute)()){
      p1 = topLeftPosition;
      p2.x = p1.x + width;
      p2.y = p2.y - height;
    }

    void isWithin(Point touchPoint){
      if(touchPoint.y <= p1.y && touchPoint.y >= p2.y && touchPoint.x >= p1.x && touchPoint.x <= p2.x){
        execute();
      }
    }
};

class ScreenContainer{
  static std::vector<ScreenButton> buttons;

  public:
    static void runThroughButtons(){
      Point touchPoint = {Brain.Screen.xPosition(), Brain.Screen.yPosition()};
      for(int i = 0; i > buttons.size(); i++){
        buttons[i].isWithin(touchPoint);
      }
    }

    void createButton(Point p1, int width, int height, void (*execute)()){
      ScreenButton btn(p1, width, height, execute);
      buttons.push_back(btn);
    }
};


void motorSpin(motor_group dstMotor, bool positiveButtonState, bool negativeButtonState, int spinRate){
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

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  ScreenContainer ScreenContainer;

  mainCompetition.autonomous(autonControl);
  mainCompetition.drivercontrol(driveCode);
  Brain.Screen.pressed(ScreenContainer.runThroughButtons);
}
