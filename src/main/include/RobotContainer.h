// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>

#include "subsystems/EXC.h"
#include "subsystems/CAM.h"
#include "subsystems/HOP.h"

#include "Constants.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and trigger mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::CommandPtr GetAutonomousCommand();

 private:
  // Replace with CommandPS4Controller or CommandJoystick if needed
  frc2::CommandXboxController m_driverControllerDriver{
      OperatorConstants::kDriverControllerPort};
  frc2::CommandXboxController m_driverControllerCoDriver{
      OperatorConstants::jDriverControllerPort};
  frc2::CommandXboxController m_driverControllerAuto{
      OperatorConstants::iDriverControllerPort};

  // The robot's subsystems are defined here...
  // ExampleSubsystem m_subsystem;
  CAM m_CAM;
  EXC m_EXC;
  HOP m_HOP;

  void ConfigureBindings();
};
