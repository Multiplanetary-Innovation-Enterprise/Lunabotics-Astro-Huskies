// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <rev/CANSparkMax.h>
#include <frc2/command/SubsystemBase.h>

#include "Constants.h"

class CAM : public frc2::SubsystemBase {
 public:
  CAM();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void setVelocity(double leftVelocity, double rightVelocity);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  rev::CANSparkMax    m_driveMotor1;
  rev::CANSparkMax    m_driveMotor2;
  rev::CANSparkMax    m_driveMotor3;
  rev::CANSparkMax    m_driveMotor4;
  
  rev::SparkMaxRelativeEncoder m_driveMotor1Encoder;
  rev::SparkMaxRelativeEncoder m_driveMotor2Encoder;
  rev::SparkMaxRelativeEncoder m_driveMotor3Encoder;
  rev::SparkMaxRelativeEncoder m_driveMotor4Encoder;

};