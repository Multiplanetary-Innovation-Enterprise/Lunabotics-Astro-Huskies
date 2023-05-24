// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/button/Trigger.h>
#include <iostream>
#include <string.h>
#include <frc2/command/Commands.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/XboxController.h>
using namespace std;
double speedAdjust;
RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureBindings();

    string EXCencorders = to_string(m_EXC.getExcavatorDepth());
    string HOPFlip = to_string(m_HOP.GetFlipPosition());
    string EXClinearActuator = to_string(m_EXC.getLinearActuatorPosition());

    cout<<"\nEXC extend encoders  "<<EXCencorders;
    cout<<"\nEXC Linear Actuator Position  "<<EXClinearActuator;
    cout<<"\nHOP Flipper Position  "<<HOPFlip;    
    
    
    m_CAM.SetDefaultCommand(frc2::cmd::Run(
      [this] {
        m_CAM.setVelocity(-m_driverControllerDriver.GetLeftY(),
                            m_driverControllerDriver.GetRightY());
      },
      {&m_CAM}));

}

void RobotContainer::ConfigureBindings() {
  // EXC Bndings
  // Spin Buckets

  m_driverControllerCoDriver.A()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.setBucketSpeed(EXCConstants::bucketSpinMotorSpeed);}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setBucketSpeed(0);}, {&m_EXC}));
  m_driverControllerCoDriver.B()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.setBucketSpeed(-EXCConstants::bucketSpinMotorSpeed);}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setBucketSpeed(0);}, {&m_EXC}));
  //Stow Excavator
  m_driverControllerCoDriver.RightBumper()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.stowExcavator();}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setLinearActuatorspeed(0);}, {&m_EXC}));
  //Deploy Excavator
  m_driverControllerCoDriver.LeftBumper()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.deployExcavator();}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setLinearActuatorspeed(0);}, {&m_EXC}));
  //Extend Excavator
  m_driverControllerCoDriver.LeftTrigger()
  .WhileTrue(frc2::cmd::Run([this] {m_EXC.setExtendVelocity(EXCConstants::extendVelocity);}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setExtendVelocity(0);}, {&m_EXC}));
  m_driverControllerCoDriver.RightTrigger()
  .WhileTrue(frc2::cmd::Run([this] {m_EXC.setExtendVelocity(EXCConstants::retractVelocity);}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.setExtendVelocity(0);}, {&m_EXC}));
  
  m_driverControllerCoDriver.X()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.extendRightScrew(EXCConstants::extendVelocity);}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.extendRightScrew(0);}, {&m_EXC}));
  m_driverControllerCoDriver.Y()
  .OnTrue(frc2::cmd::RunOnce([this] {m_EXC.extendRightScrew(-EXCConstants::extendVelocity);}, {&m_EXC}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_EXC.extendRightScrew(0);}, {&m_EXC}));
  
  m_driverControllerDriver.RightBumper()
  .WhileTrue(frc2::cmd::Run([this] {
    m_EXC.autoEXCState(1); 
    int CommandVAR = m_EXC.autoExcavator(); 
    m_HOP.autoHopper(CommandVAR);
    m_CAM.autoChassis(CommandVAR);
    }, {&m_EXC}))
  .OnFalse(frc2::cmd::Run([this] {
    int CommandVAR = m_EXC.autoExcavator(); 
    m_HOP.autoHopper(CommandVAR);
    //m_CAM.autoChassis(CommandVAR);
    }, {&m_EXC}));

  m_driverControllerDriver.LeftBumper()
  .WhileTrue(frc2::cmd::RunOnce([this] {
    m_EXC.autoEXCState(2); 
    int CommandVAR = m_EXC.autoExcavator();
    m_HOP.autoHopper(CommandVAR);
    //m_CAM.autoChassis(CommandVAR);
    }, {&m_EXC}));

  //HOP Bindings
  m_driverControllerDriver.RightTrigger()
  .OnTrue(frc2::cmd::RunOnce([this] { speedAdjust = m_HOP.HopperSpeed(2); }, {&m_HOP}))
  .OnFalse(frc2::cmd::Run([this] { speedAdjust = m_HOP.HopperSpeed(0); }, {&m_HOP}));
  m_driverControllerDriver.LeftTrigger()
  .OnTrue(frc2::cmd::RunOnce([this] { speedAdjust = m_HOP.HopperSpeed(1); }, {&m_HOP}))
  .OnFalse(frc2::cmd::Run([this] { speedAdjust = m_HOP.HopperSpeed(0); }, {&m_HOP}));
  m_driverControllerDriver.B()
  .WhileTrue(frc2::cmd::Run([this] {m_HOP.setFlipStow();}, {&m_HOP}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_HOP.SetFlipVelocity(0);}, {&m_HOP}));
  m_driverControllerDriver.Y()
  .WhileTrue(frc2::cmd::Run([this] {m_HOP.setFlipDump();}, {&m_HOP}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_HOP.SetFlipVelocity(0);}, {&m_HOP}));
  m_driverControllerDriver.X()
  .WhileTrue(frc2::cmd::Run([this] {m_HOP.setFlipTumble();}, {&m_HOP}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_HOP.SetFlipVelocity(0);}, {&m_HOP}));
  m_driverControllerDriver.A()
  .WhileTrue(frc2::cmd::Run([this] {m_HOP.SetBeltVelocity(HOPConstants::beltVelocity);}, {&m_HOP}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_HOP.SetBeltVelocity(0);}, {&m_HOP}));

  //CAM Bindings
 //m_driverControllerDriver.POVUp().

  (m_driverControllerDriver.RightTrigger() && m_driverControllerDriver.LeftTrigger() && m_driverControllerDriver.LeftStick())
  .OnTrue(frc2::cmd::RunOnce([this]{m_CAM.setVelocity(-0.1, 0);}, {&m_CAM} ));
  (m_driverControllerDriver.RightTrigger() && m_driverControllerDriver.RightTrigger() && m_driverControllerDriver.LeftStick())
  .OnTrue(frc2::cmd::RunOnce([this]{m_CAM.setVelocity(0, -0.1);}, {&m_CAM} ));

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