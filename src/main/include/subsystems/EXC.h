// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Constants.h"
#include <rev/CANSparkMax.h>
#include <frc/Servo.h>
#include <frc/DigitalInput.h>

class EXC : public frc2::SubsystemBase {
 public:
  EXC();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Function will return the depth of the excavator.
   */
  int getExcavatorDepth();

  /**
   * Function will return the velocity that the excavator is being raised or lowered.
   */
  double getDigVelocity();
  
  /**
   * Function will return the speed of the bucket motor.
   */
  double getBucketSpeed();
  
  /**
   * Function will set the velocity that the excavator is being raised or lowered by.
   */
  void setDigVelocity(double speed);
  
  /**
   * Function will set the speed of the bucket motor.
   */
  void setBucketSpeed(double speed);
  
  /**
   * Function sets linearActuatorPosition.
   */
  void setLinearActuatordirection(double direction);
  void setLinearActuatorspeed(double speed);

  /**
   * Function returns true or false if the excavator is extended or not.
   
  bool isExtended();
  
  
   * Function returns true or false if the excavator is retracted or not.
    bool isRetracted();
    */

 private:
  // Components (e.g. motor controllers and sensors) 
  rev::CANSparkMax  m_digMotor1; 
  rev::CANSparkMax  m_digMotor2; 
  rev::CANSparkMax  m_bucketSpinMotor; 
 
  frc::Servo  m_linearActuatordir1;
  frc::Servo  m_linearActuatordir2;
  frc::Servo  m_linearActuatorSpeed1;
  frc::Servo  m_linearActuatorSpeed2;
 
  rev::SparkMaxRelativeEncoder  m_digEncoder1;
  rev::SparkMaxRelativeEncoder  m_digEncoder2; 
  rev::SparkMaxRelativeEncoder  m_bucketEncoder; 
}

class EXC_Stow
    : public frc2::CommandHelper<frc2::CommandBase, EXC_Stow> {
 public:
  EXC_Stow();

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
};
class EXC_Dig
    : public frc2::CommandHelper<frc2::CommandBase, EXC_Dig> {
 public:
  EXC_Dig();

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
};
class EXC_Deploy
    : public frc2::CommandHelper<frc2::CommandBase, EXC_Deploy> {
 public:
  EXC_Deploy();

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
};