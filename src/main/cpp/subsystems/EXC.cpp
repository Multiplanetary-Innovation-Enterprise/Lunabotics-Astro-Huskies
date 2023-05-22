// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/EXC.h"
#include "Constants.h"
#include <frc/DigitalOutput.h>

EXC::EXC(): 
    m_extendMotor1{EXCConstants::extendMotor1ID, rev::CANSparkMax::MotorType::kBrushless},
    m_extendMotor2{EXCConstants::extendMotor2ID, rev::CANSparkMax::MotorType::kBrushless},
    m_bucketSpinMotor{EXCConstants::bucketSpinMotorID, rev::CANSparkMax::MotorType::kBrushless},
    
    m_linearActuatordir1{EXCConstants::linearActuatorID_dir}, 
    m_linearActuatordir2{EXCConstants::linearActuatorID2_dir},
    m_linearActuatorSpeed1{EXCConstants::linearActuatorID_speed}, 
    m_linearActuatorSpeed2{EXCConstants::linearActuatorID_speed2},
    
    m_extendEncoder1{m_extendMotor1.GetEncoder()},
    m_extendEncoder2{m_extendMotor2.GetEncoder()}, 
    m_bucketEncoder{m_bucketSpinMotor.GetEncoder()} {}

// This method will be called once per scheduler run
void EXC::Periodic() {
    
}

int EXC::getExcavatorDepth() {
    if(m_extendEncoder1.GetPosition() >= m_extendEncoder2.GetPosition()) {
        return m_extendEncoder1.GetPosition();
    } else {
        return m_extendEncoder2.GetPosition();
    }
}

double EXC::getExtendVelocity() {
    if(m_extendEncoder1.GetVelocity() >= m_extendEncoder2.GetVelocity()) {
        return m_extendEncoder1.GetVelocity();
    } else {
        return m_extendEncoder2.GetVelocity();
    }
}

double EXC::getBucketSpeed() {
    return m_bucketEncoder.GetVelocity();
}

void EXC::setExtendVelocity(double speed) {
    m_extendMotor1.Set(speed);
    m_extendMotor2.Set(speed);
}

void EXC::setExtendPosition(int position) {
    if(m_extendEncoder1.GetPosition() < position) {
        setExtendVelocity(EXCConstants::extendVelocity);
    } else{ setExtendVelocity(0);}
}

void EXC::setRetractPosition(int position) {
    if(m_extendEncoder1.GetPosition() > position) {
        setExtendVelocity(EXCConstants::retractVelocity);
    } else{ setExtendVelocity(0);}
}

void EXC::setBucketSpeed(double speed) {
    m_bucketSpinMotor.Set(speed);
}

void EXC::setLinearActuatordirection(double direction) {
    m_linearActuatordir1.Set(direction);
    m_linearActuatordir2.Set(direction);
}

void EXC::setLinearActuatorspeed(double speed) {
    m_linearActuatorSpeed1.Set(speed);
    m_linearActuatorSpeed2.Set(speed);
}

void EXC::stowExcavator() {
    EXC::setLinearActuatordirection(EXCConstants::linearActuatorRetractValue);
    EXC::setLinearActuatorspeed(EXCConstants::linearActuatorVelocity);
}

void EXC::deployExcavator() {
    EXC::setLinearActuatordirection(EXCConstants::linearActuatorForwardValue);
    EXC::setLinearActuatorspeed(EXCConstants::linearActuatorVelocity);
}
