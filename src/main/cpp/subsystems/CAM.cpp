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
double startPosition;
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

  double CAM::getCAMPosition() {
    if ( 
      m_driveMotor1Encoder.GetPosition() < -m_driveMotor2Encoder.GetPosition() && 
      m_driveMotor1Encoder.GetPosition() < m_driveMotor3Encoder.GetPosition() &&
      m_driveMotor1Encoder.GetPosition() < -m_driveMotor4Encoder.GetPosition()) {
        return m_driveMotor1Encoder.GetPosition();
      }
    else if (
      -m_driveMotor2Encoder.GetPosition() < m_driveMotor1Encoder.GetPosition() && 
      -m_driveMotor2Encoder.GetPosition() < m_driveMotor3Encoder.GetPosition() &&
      -m_driveMotor2Encoder.GetPosition() < -m_driveMotor4Encoder.GetPosition()) {
        return -m_driveMotor2Encoder.GetPosition();
      }
    else if (
      m_driveMotor3Encoder.GetPosition() < m_driveMotor1Encoder.GetPosition() && 
      m_driveMotor3Encoder.GetPosition() < -m_driveMotor2Encoder.GetPosition() &&
      m_driveMotor3Encoder.GetPosition() < -m_driveMotor4Encoder.GetPosition()) {
        return m_driveMotor3Encoder.GetPosition();
      }
    else if (
      -m_driveMotor4Encoder.GetPosition() < m_driveMotor1Encoder.GetPosition() && 
      -m_driveMotor4Encoder.GetPosition() < -m_driveMotor2Encoder.GetPosition() &&
      -m_driveMotor4Encoder.GetPosition() < m_driveMotor3Encoder.GetPosition()) {
        return -m_driveMotor4Encoder.GetPosition();
      }
    else {
      return m_driveMotor1Encoder.GetPosition();
    }
  }

  int CAM::autoChassis(int Commandvar) {
    if(Commandvar == 1) {
      
      if((CAM::getCAMPosition() - startPosition) <= CAMConstants::excavationZone){
        m_driveMotor2.Set(-0.06); //Right Motors
        m_driveMotor4.Set(-0.06); //Right Motors

        m_driveMotor1.Set(0.06);  //Left Motors
        m_driveMotor3.Set(0.06);  //Left Motors
        return 2;
        string encorderPos = to_string(CAM::getCAMPosition());
        cout<<"\nNot in EXC Zone,     Encoder Positon: "<<encorderPos;
      }
      else {
        m_driveMotor2.Set(0); //Right Motors
        m_driveMotor4.Set(0); //Right Motors

        m_driveMotor1.Set(0);  //Left Motors
        m_driveMotor3.Set(0);  //Left Motors
        return 1;
        string encorderPos = to_string(CAM::getCAMPosition());
        cout<<"\nIn EXC Zone,     Encoder Positon: "<<encorderPos;
      }
    }
    else{
        m_driveMotor2.Set(0); //Right Motors
        m_driveMotor4.Set(0); //Right Motors

        m_driveMotor1.Set(0);  //Left Motors
        m_driveMotor3.Set(0);  //Left Motors
        return 2;
    }
  }