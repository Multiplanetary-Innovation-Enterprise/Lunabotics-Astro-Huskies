// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
/*
#include "subsystems/HOP.h"
#include <frc/smartdashboard/SmartDashboard.h>

HOP::HOP()
    : m_beltMotor{HOPConstants::beltMotorID, rev::CANSparkMax::MotorType::kBrushless},
    m_beltEncoder{m_beltMotor.GetEncoder()},
    m_beltPIDController{m_beltMotor.GetPIDController()},
    m_lipMotor{HOPConstants::lipMotorID, rev::CANSparkMax::MotorType::kBrushless},
    m_lipEncoder{m_lipMotor.GetEncoder()},
    m_lipPIDController{m_lipMotor.GetPIDController()} {

// This method will be called once per scheduler run
void HOP::Periodic() {
    frc::SmartDashboard::PutNumber("HOP_currentBeltVelocity", HOP::GetBeltVelocity());
    frc::SmartDashboard::PutNumber("HOP_currentLipPosition", HOP::GetLipPosition());
}


void HOP::SetBeltVelocity(double beltVelocity) {
    m_beltPIDController.SetReference(beltVelocity, rev::CANSparkMax::ControlType::kVelocity);
}


double HOP::GetBeltVelocity() {
    return m_beltEncoder.GetVelocity();
}


void HOP::SetLipPosition(int targetLipPosition) {
    m_lipPIDController.SetReference(targetLipPosition, rev::CANSparkMax::ControlType::kPosition);
}


int HOP::GetLipPosition() {
    return m_lipEncoder.GetPosition();
}