// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Constants.h"
#include <rev/CANSparkMax.h>
#include <frc/Servo.h>
#include <frc/DigitalInput.h>
#include <frc/DigitalOutput.h>

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
  double getExtendVelocity();
  
  /**
   * Function will return the speed of the bucket motor.
   */
  double getBucketSpeed();
  
  /**
   * Function will set the velocity that the excavator is being raised or lowered by.
   */
  void setExtendVelocity(double speed);
  void setExtendPosition(int position);
  void setRetractPosition(int position);
  
  /**
   * Function will set the speed of the bucket motor.
   */
  void setBucketSpeed(double speed);
  
  /**
   * Function sets linearActuatorPosition.
   */
  void setLinearActuatordirection(double direction);
  void setLinearActuatorspeed(double speed);

  void stowExcavator();
  void deployExcavator();
  
 private:
  // Components (e.g. motor controllers and sensors) 
  rev::CANSparkMax  m_extendMotor1; 
  rev::CANSparkMax  m_extendMotor2; 
  rev::CANSparkMax  m_bucketSpinMotor; 
 
  frc::DigitalOutput  m_linearActuatordir1;
  frc::DigitalOutput  m_linearActuatordir2;
  frc::DigitalOutput  m_linearActuatorSpeed1;
  frc::DigitalOutput  m_linearActuatorSpeed2;

  rev::SparkMaxRelativeEncoder  m_extendEncoder1;
  rev::SparkMaxRelativeEncoder  m_extendEncoder2; 
  rev::SparkMaxRelativeEncoder  m_bucketEncoder; };