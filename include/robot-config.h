using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor IntakeMotor;
extern motor rightFront;
extern motor leftFront;
extern motor leftBack;
extern motor rightBack;

extern digital_out leftWing;
extern digital_out rightWing;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );