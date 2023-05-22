// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/button/Trigger.h>

#include <frc2/command/Commands.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/XboxController.h>

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureBindings();

    m_CAM.SetDefaultCommand(frc2::cmd::Run(
      [this] {
        m_CAM.setVelocity(-m_driverController.GetLeftY(),
                            -m_driverController.GetRightY());
      },
      {&m_CAM}));
}

void RobotContainer::ConfigureBindings() {
  // EXC Bndings
  m_driverController.LeftBumper()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.setDigVelocity(frc::SmartDashboard::GetNumber("EXC_reverseDigVelocity", EXCConstants::retractVelocity));}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setDigVelocity(0);}, {&m_EXC}));
  m_driverController.LeftTrigger()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.setDigVelocity(frc::SmartDashboard::GetNumber("EXC_forwardDigVelocity", EXCConstants::extendVelocity));}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setDigVelocity(0);}, {&m_EXC}));
  m_driverController.RightTrigger()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.setLinearActuatorVelocity(frc::SmartDashboard::GetNumber("EXC_LinearActuatorVelocity", EXCConstants::LinearActuatorVelocity));}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setLinearActuatorVelocity(0);}, {&m_EXC}));

  //HOP Bindings
  m_driverController.A().OnTrue(frc2::cmd::RunOnce([this] 
    {m_HOP.SetLipPosition(frc::SmartDashboard::GetNumber("HOP_stowPosition", HOPConstants::stowPosition));}, {&m_HOP}));
  m_driverController.B().OnTrue(frc2::cmd::RunOnce([this] 
    {m_HOP.SetBeltVelocity(frc::SmartDashboard::GetNumber("HOP_beltVelocity", HOPConstants::beltVelocity));}, {&m_HOP}))
    .OnFalse(frc2::cmd::RunOnce([this] {m_HOP.SetBeltVelocity(0);}, {&m_HOP}));
  m_driverController.X().OnTrue(frc2::cmd::RunOnce([this] 
    {m_HOP.SetLipPosition(frc::SmartDashboard::GetNumber("HOP_tumblePosition", HOPConstants::tumblePosition));}, {&m_HOP}));
  m_driverController.Y().OnTrue(frc2::cmd::RunOnce([this] 
    {m_HOP.SetLipPosition(frc::SmartDashboard::GetNumber("HOP_dumpPosition", HOPConstants::dumpPosition));}, {&m_HOP}));

  //CAM Bindings
  m_driverController.LeftStick().OnTrue(frc2::cmd::RunOnce([this]
     {m_CAM.setVelocity(0.1, 0);}, {&m_CAM} ));

  m_driverController.RightStick().OnTrue(frc2::cmd::RunOnce([this]
     {m_CAM.setVelocity(0, 0.1);}, {&m_CAM}));
}
  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  
  /*
  frc2::Trigger([this] {
    return m_subsystem.ExampleCondition();
  }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  m_driverController.B().WhileTrue(m_subsystem.ExampleMethodCommand());
} 

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return autos::ExampleAuto(&m_subsystem);
}
*/