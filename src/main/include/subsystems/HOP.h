// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <rev/CANSparkMax.h>
#include <frc2/command/SubsystemBase.h>

#include "Constants.h"

class HOP : public frc2::SubsystemBase {
 public:
  HOP();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Subsytem will run at a given speed
  */
  void SetBeltVelocity(double speed);

  double GetBeltVelocity();
  double GetFlipPosition();

   /**
   * Subsytem will move the flip to the target position
  */
  void SetFlipPosition(int targetFlipPosition);
  void setFlipStow();
  void setFlipDump();
  void setFlipTumble();

  void SetFlipVelocity(double flipVelocity);


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.'
  rev::CANSparkMax              m_beltMotor;
  rev::SparkMaxRelativeEncoder  m_beltEncoder;

  rev::CANSparkMax              m_flipMotor;
  rev::SparkMaxRelativeEncoder  m_flipEncoder;
};