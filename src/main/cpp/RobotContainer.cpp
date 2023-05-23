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

    m_driverControllerCoDriver.RightTrigger()
    .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.autoEXCState(1);}));
    m_driverControllerCoDriver.RightBumper()
      .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.autoEXCState(2);}));
    
    m_EXC.autoExcavator();

    
    m_CAM.SetDefaultCommand(frc2::cmd::Run(
      [this] {
        m_CAM.setVelocity(-m_driverControllerDriver.GetLeftY(),
                            -m_driverControllerDriver.GetRightY());
      },
      {&m_CAM}));
}

void RobotContainer::ConfigureBindings() {
  // EXC Bndings
  // Spin Buckets
  m_driverControllerCoDriver.LeftTrigger()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.setBucketSpeed(EXCConstants::bucketSpinMotorSpeed);}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setBucketSpeed(0);}, {&m_EXC}));
  //Stow Excavator
  m_driverControllerCoDriver.A()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.stowExcavator();}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setLinearActuatorspeed(0);}, {&m_EXC}));
  //Deploy Excavator
  m_driverControllerCoDriver.B()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.deployExcavator();}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setLinearActuatorspeed(0);}, {&m_EXC}));
  //Extend Excavator
  m_driverControllerCoDriver.X()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.setExtendVelocity(EXCConstants::extendVelocity);}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setExtendVelocity(0);}, {&m_EXC}));
  m_driverControllerCoDriver.Y()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.setExtendVelocity(EXCConstants::retractVelocity);}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setExtendVelocity(0);}, {&m_EXC}));


  //HOP Bindings
  m_driverControllerDriver.A()
  .OnTrue(frc2::cmd::RunOnce([this] {m_HOP.SetFlipVelocity(HOPConstants::flipVelocity);}, {&m_HOP}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_HOP.SetFlipVelocity(0);}, {&m_HOP}));
  m_driverControllerDriver.B()
  .OnTrue(frc2::cmd::RunOnce([this] {m_HOP.SetFlipVelocity(-HOPConstants::flipVelocity);}, {&m_HOP}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_HOP.SetFlipVelocity(0);}, {&m_HOP}));
  m_driverControllerDriver.X()
  .OnTrue(frc2::cmd::RunOnce([this] {m_HOP.SetBeltVelocity(HOPConstants::beltVelocity);}, {&m_HOP}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_HOP.SetBeltVelocity(0);}, {&m_HOP}));

  //CAM Bindings
  m_driverControllerDriver.LeftStick().OnTrue(frc2::cmd::RunOnce([this]
     {m_CAM.setVelocity(0.1, 0);}, {&m_CAM} ));

  m_driverControllerDriver.RightStick().OnTrue(frc2::cmd::RunOnce([this]
     {m_CAM.setVelocity(0, 0.1);}, {&m_CAM}));

}

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  



frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  //return autos::ExampleAuto(&m_subsystem);
}