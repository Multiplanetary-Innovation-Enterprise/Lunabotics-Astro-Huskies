// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/CAM.h"

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

CAM::setVelocity(leftVelocity, rightVelocity)