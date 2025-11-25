#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor leftMotorA = motor(PORT5, ratio18_1, false);
motor leftMotorB = motor(PORT7, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT6, ratio18_1, true);
motor rightMotorB = motor(PORT8, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

controller Controller1 = controller(primary);


// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       VexCanEatPissAndDie.cpp                                                  */
/*    Author:       {The amazing and awesome and cool 
/*                  Bermudian Springs 8114A Robotics Team}                                                  */
/*    Created:      {11/25/25}                                                    */
/*    Description:  Vex V5 Push Back 2025-2026 Competition Controller                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;
int axis3Pos;
int axis1Pos; 
int axis4Pos;
motor motors[4] = {leftMotorA, leftMotorB, rightMotorA, rightMotorB};
//variable declaration
void Drive(int speed, int dir[4])
{
  int fixedSpeed = abs(speed);
  for(int i = 0; i < 4; i++)
  {
    motors[i].setVelocity(fixedSpeed,percent);

    switch(dir[i])
    {
      case 0:
      motors[i].spin(forward);
      break;

      case 1:
      motors[i].spin(reverse);
      break;

      default:
      //shit broke, too high a num
      break;
    }
  }

}
//Drive function for bot, sets speed and motor dir then drives

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!.... or do
  vexcodeInit();
  leftMotorA.setMaxTorque(100,percent);
  leftMotorB.setMaxTorque(100,percent);
  rightMotorA.setMaxTorque(100,percent);
  rightMotorB.setMaxTorque(100,percent);


  while (true) {
    axis3Pos = Controller1.Axis3.position();
    axis1Pos = Controller1.Axis1.position();
    axis4Pos = Controller1.Axis4.position();
    //get controller inputs

    if(axis3Pos == 0 && axis1Pos == 0 && axis4Pos == 0)
    {
      leftMotorA.stop();
      leftMotorB.stop();
      rightMotorA.stop();
      rightMotorB.stop();

      leftMotorA.setVelocity(0,percent);
      leftMotorB.setVelocity(0,percent);
      rightMotorA.setVelocity(0,percent);
      rightMotorB.setVelocity(0,percent);
    }
    //no input so bot is stopped

    else 
    {
      if(axis3Pos > 0)
      {
       Drive(axis3Pos, (int[4]){0,0,0,0});
      }
      //drive straight forward
      if(axis3Pos < 0)
      {
        Drive(axis3Pos, (int[4]){1,1,1,1});
      }
      //drive straight backward

      if(axis1Pos > 0)
      {
      Drive(axis1Pos, (int[4]){0,0,1,1});
      }
      //right turn

      if(axis1Pos < 0)
      {
        Drive(axis1Pos, (int[4]){1,1,0,0});
      }
      //left turn

      if(axis4Pos > 0)
      {
        Drive(axis4Pos, (int[4]){0,1,1,0});
      }
      //strafe right

      if(axis4Pos < 0)
      {
        Drive(axis4Pos,(int[4]){1,0,0,1});
      }
      //strafe left
    }


    wait(20,msec);
  }
  
}
