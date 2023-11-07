#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor IntakeMotor = motor(PORT11, ratio18_1, false);
motor rightFront = motor(PORT14, ratio18_1, true);
motor leftFront = motor(PORT13, ratio18_1, false);
motor leftBack = motor(PORT1, ratio18_1, false);
motor rightBack = motor(PORT12, ratio18_1, true);
gps GPS15 = gps(PORT15, 0.00, 0.00, mm, 180);
motor Launcher1 = motor(PORT2, ratio18_1, false);
motor Launcher2 = motor(PORT3, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}