#include "vex.h"
#include "main.h"

using namespace vex;

int driveToPoint() {
  Controller1.Screen.setCursor(1, 1);

  //gets x position of the GPS and saves as xPlacement
  double xPlacement = GPS15.xPosition(inches);
  Controller1.Screen.print(xPlacement);

  Controller1. Screen.print(", ");

  //gets y position of GPS and saves as yPlacement
  double yPlacement = GPS15.yPosition(inches);
  //prints y position to controller screen
  Controller1.Screen.print(yPlacement);

  //where robot should drive to
  double whereIWantToGoY = 34;
  double whereIWantToGoX = 43;

  //finds distance between robot and point it should go to w/ distance formula
  double w = sqrt((whereIWantToGoX - xPlacement) * (whereIWantToGoX - xPlacement) + (whereIWantToGoY - yPlacement) * (whereIWantToGoY - yPlacement));
  //finds distance between robot and point m
  double v = whereIWantToGoY - yPlacement;

  //finds the angle with acos() same as inverse cosine 
  double robotAngle = acos(v/w);
  Controller1.Screen.print(robotAngle);

  //instructs robot to drive to new position
  mainDrive.turnFor(right, robotAngle, degrees);
  mainDrive.driveFor(forward, w, inches);

  return 0;
}
