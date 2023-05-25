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
    
    //////////////////////////////////////////////////////// MAIN DRIVER CONTROLS HOPPER ////////////////////////////////////////////////////////////////
    m_driverControllerDriver.RightTrigger()
    .WhileTrue(frc2::cmd::Run([this] {
      m_CAM.setVelocity(-m_driverControllerDriver.GetLeftY(), m_driverControllerDriver.GetRightY());
      },{&m_CAM}))
    .OnFalse(frc2::cmd::Run([this] {
      m_CAM.setVelocity(0, 0);
      },{&m_CAM}));

      m_driverControllerDriver.LeftTrigger()
    .WhileTrue(frc2::cmd::Run([this] {
      m_CAM.setVelocity(m_driverControllerDriver.GetLeftY(), -m_driverControllerDriver.GetRightY());
      },{&m_CAM}))
    .OnFalse(frc2::cmd::Run([this] {
      m_CAM.setVelocity(0, 0);
      },{&m_CAM}));

}

void RobotContainer::ConfigureBindings() {

  //////////////////////////////////////////////////////// CO-DRIVER CONTROLS ////////////////////////////////////////////////////////////////
  /*
  A -> SPIN BUCKETS FORWARD
  B -> SPIN BUCKETS BACKWARD
  X -> EXTEND RIGHT ACME SCREW
  Y -> RETRACT RIGHT ACME SCREW
  */
  
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
  
  //////////////////////////////////////////////////////// AUTONOMOUS CONTROLS /////////////////////////////////////////////////////////////////
  m_driverControllerAuto.A()
  .WhileTrue(frc2::cmd::Run([this] {
    int EXCok = m_CAM.autoChassis(0);
    m_EXC.autoEXCState(EXCok); 
    int CommandVAR = m_EXC.autoExcavator(); 
    //m_HOP.autoHopper(CommandVAR);
    }, {&m_EXC}))
  .OnFalse(frc2::cmd::Run([this] {
    int EXCok = m_CAM.autoChassis(1);
    m_EXC.autoEXCState(EXCok); 
    int CommandVAR = m_EXC.autoExcavator(); 
    //m_HOP.autoHopper(CommandVAR);
    }, {&m_EXC}));

  m_driverControllerAuto.B()
  .WhileTrue(frc2::cmd::RunOnce([this] {
    int EXCok = m_CAM.autoChassis(2);
    m_EXC.autoEXCState(2); 
    int CommandVAR = m_EXC.autoExcavator();
    //m_HOP.autoHopper(CommandVAR);
    }, {&m_EXC}));

      m_driverControllerAuto.X()
  .WhileTrue(frc2::cmd::Run([this] {
    m_EXC.autoEXCState(1); 
    int CommandVAR = m_EXC.autoExcavator(); 
    //m_HOP.autoHopper(CommandVAR);
    }, {&m_EXC}))
  .OnFalse(frc2::cmd::Run([this] {
    int CommandVAR = m_EXC.autoExcavator(); 
    //m_HOP.autoHopper(CommandVAR);
    }, {&m_EXC}));

  m_driverControllerAuto.Y()
  .WhileTrue(frc2::cmd::RunOnce([this] {
    m_EXC.autoEXCState(2); 
    int CommandVAR = m_EXC.autoExcavator();
    //m_HOP.autoHopper(CommandVAR);
    }, {&m_EXC}));

  //////////////////////////////////////////////////////// MAIN DRIVER CONTROLS HOPPER ////////////////////////////////////////////////////////////////
  //HOP Bindings
  m_driverControllerDriver.RightBumper()
  .OnTrue(frc2::cmd::Run([this] { speedAdjust = m_HOP.HopperSpeed(2); }, {&m_HOP}))
  .OnFalse(frc2::cmd::Run([this] { speedAdjust = m_HOP.HopperSpeed(0); }, {&m_HOP}));
  m_driverControllerDriver.LeftBumper()
  .OnTrue(frc2::cmd::Run([this] { speedAdjust = m_HOP.HopperSpeed(1); }, {&m_HOP}))
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
  .WhileTrue(frc2::cmd::Run([this] {m_HOP.SetBeltVelocity(speedAdjust);}, {&m_HOP}))
  .OnFalse(frc2::cmd::RunOnce([this] {m_HOP.SetBeltVelocity(0);}, {&m_HOP}));

}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  //return autos::ExampleAuto(&m_subsystem);
}