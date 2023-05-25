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
double startPosition1;
double startPosition2;
double startPosition3;
double startPosition4;
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
    startPosition1 = m_driveMotor1Encoder.GetPosition();
    startPosition2 = m_driveMotor2Encoder.GetPosition();
    startPosition3 = m_driveMotor3Encoder.GetPosition();
    startPosition4 = m_driveMotor4Encoder.GetPosition();

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

    double motor1Position = m_driveMotor1Encoder.GetPosition() - startPosition1;
    double motor2Position = m_driveMotor2Encoder.GetPosition() - startPosition2;
    double motor3Position = m_driveMotor3Encoder.GetPosition() - startPosition3;
    double motor4Position = m_driveMotor4Encoder.GetPosition() - startPosition4;

    if ( 
      motor1Position < -motor2Position && 
      motor1Position < motor3Position &&
      motor1Position < -motor4Position) {
        return motor1Position;
      }
    else if (
      -motor2Position < motor1Position && 
      -motor2Position < motor3Position &&
      -motor2Position < -motor4Position) {
        return -motor2Position;
      }
    else if (
      motor3Position < motor1Position && 
      motor3Position < -motor2Position &&
      motor3Position < -motor4Position) {
        return motor3Position;
      }
    else if (
      -motor4Position < motor1Position && 
      -motor4Position < -motor2Position &&
      -motor4Position < motor3Position) {
        return -motor4Position;
      }
    else {
      return motor1Position;
    }
  }

  int CAM::autoChassis(int Commandvar) {
    if(Commandvar == 1) {
      
      if((CAM::getCAMPosition()) <= CAMConstants::excavationZone){
        m_driveMotor2.Set(-0.06); //Right Motors
        m_driveMotor4.Set(-0.06); //Right Motors

        m_driveMotor1.Set(0.06);  //Left Motors
        m_driveMotor3.Set(0.06);  //Left Motors
        return 0;
        string encorderPos = to_string(CAM::getCAMPosition());
        cout<<"\nNot in EXC Zone,     Encoder Positon: "<<encorderPos;
      }
      else {
        m_driveMotor2.Set(0); //Right Motors
        m_driveMotor4.Set(0); //Right Motors

        m_driveMotor1.Set(0);  //Left Motors
        m_driveMotor3.Set(0);  //Left Motors
        string encorderPos = to_string(CAM::getCAMPosition());
        cout<<"\nIn EXC Zone,     Encoder Positon: "<<encorderPos;
        return 1;
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