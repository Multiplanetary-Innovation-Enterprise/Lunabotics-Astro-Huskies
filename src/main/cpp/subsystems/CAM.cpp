// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/CAM.h"
#include <iostream>
#include <string.h>
#include "Constants.h"
using namespace std;
time_t time2;
time_t time3;
CAM::CAM() : 

m_driveMotor1{CAMConstants::driveMotor1ID, rev::CANSparkMax::MotorType::kBrushless},
m_driveMotor2{CAMConstants::driveMotor2ID, rev::CANSparkMax::MotorType::kBrushless},
m_driveMotor3{CAMConstants::driveMotor3ID, rev::CANSparkMax::MotorType::kBrushless},
m_driveMotor4{CAMConstants::driveMotor4ID, rev::CANSparkMax::MotorType::kBrushless},

m_driveMotor1Encoder{m_driveMotor1.GetEncoder()},
m_driveMotor2Encoder{m_driveMotor2.GetEncoder()},
m_driveMotor3Encoder{m_driveMotor3.GetEncoder()},
m_driveMotor4Encoder{m_driveMotor4.GetEncoder()} {}

// This method will be called once per scheduler run
void CAM::Periodic() {}

// Or we just have two arguments, leftVelocity and rightVelocity
// The function doesn't run whenever we touch the joystick
// The function continullay runs and reads the joystick value

  void CAM::setVelocity(double leftVelocity, double rightVelocity) {
    string leftspeed = to_string(leftVelocity);
    cout<<"\n Speed  "<<leftspeed;
    if(leftVelocity > 0.05 || leftVelocity < -0.05){
      m_driveMotor1.Set(leftVelocity*0.4);
      m_driveMotor3.Set(leftVelocity*0.4);
    }
    else {
      m_driveMotor1.Set(0);
      m_driveMotor3.Set(0);
    }
    if(rightVelocity > 0.05 || rightVelocity < -0.05){
      m_driveMotor2.Set(rightVelocity*0.4);
      m_driveMotor4.Set(rightVelocity*0.4);
    }
    else {
      m_driveMotor2.Set(0);
      m_driveMotor4.Set(0);
    }
}
void CAM::autoChassis(int Commandvar) {
    // 0 -> Don't do anything
    // 1 -> Set Flipper to Tumble
    // 2 -> Drive Belt & CAM
    // 3 -> Turn off Belt & CAM
    // 4 -> Set Flipper to Dump
    // 5 -> CAM and HOP off
  if (Commandvar == 1) {
    time(&time2);
  }
  if (Commandvar == 2) {
    time(&time3);

    if(((time3 - time2) % 3) == 1) {
      string timer = to_string(((time3 - time2) % 4) == 1);
      cout<<"\nCAM time  "<<timer;
      CAM::setVelocity(-0.6, 0.6);
    } 
    else {
      CAM::setVelocity(0,0);
      cout<<"\nCAM off";
    }
  }
  else if(Commandvar == 3) {
    CAM::setVelocity(0,0);
  }
  else if(Commandvar == 5) {
    CAM::setVelocity(0,0);
  }
}