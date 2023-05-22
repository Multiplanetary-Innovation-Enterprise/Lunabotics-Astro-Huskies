// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/HOP.h"
#include <frc/smartdashboard/SmartDashboard.h>

HOP::HOP(): 
    m_beltMotor{HOPConstants::beltMotorID, rev::CANSparkMax::MotorType::kBrushless},
    m_beltEncoder{m_beltMotor.GetEncoder()},
    m_flipMotor{HOPConstants::flipMotorID, rev::CANSparkMax::MotorType::kBrushless},
    m_flipEncoder{m_flipMotor.GetEncoder()} {}

// This method will be called once per scheduler run
void HOP::Periodic() {
    //frc::SmartDashboard::PutNumber("HOP_currentBeltVelocity", HOP::GetBeltVelocity());
    //frc::SmartDashboard::PutNumber("HOP_currentLipPosition", HOP::GetFlipPosition());
}

void HOP::SetFlipVelocity(double flipVelocity) {
    m_flipMotor.Set(flipVelocity);
}


void HOP::SetBeltVelocity(double beltVelocity) {
    m_beltMotor.Set(HOPConstants::beltVelocity);
}


void HOP::SetFlipPosition(int position) {
   if(m_flipEncoder.GetPosition() < position - 5) {
        m_flipMotor.Set(HOPConstants::flipVelocity);
   } 
   else if(m_flipEncoder.GetPosition() > position + 5) {
        m_flipMotor.Set(-HOPConstants::flipVelocity);
   }
   else {m_flipMotor.Set(0);}
}