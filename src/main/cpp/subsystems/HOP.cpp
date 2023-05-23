// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/HOP.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <string.h>
using namespace std;

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
    string HOPFlip = to_string(HOP::GetFlipPosition());
    cout<<"\nHOP Flipper Position  "<<HOPFlip;
    /*if(m_flipEncoder.GetPosition() < HOPConstants::stowPosition && flipVelocity > 0){
        m_flipMotor.Set(flipVelocity);
    }
    else if(m_flipEncoder.GetPosition() > HOPConstants::tumblePosition && flipVelocity < 0){
        m_flipMotor.Set(flipVelocity);
    }
    else{
        m_flipMotor.Set(0);
    }*/
    
}

double HOP::GetFlipPosition(){
    return m_flipEncoder.GetPosition();
}




void HOP::SetBeltVelocity(double speed) {
    m_beltMotor.Set(speed);
}

void HOP::setFlipStow() {
    
    if(m_flipEncoder.GetPosition() > HOPConstants::stowPositionMax) {
        m_flipMotor.Set(0);
    } 
    else if(m_flipEncoder.GetPosition() < HOPConstants::stowPositionMin) {
        m_flipMotor.Set(HOPConstants::flipVelocity);
        }
   else {m_flipMotor.Set(0);}
}

void HOP::setFlipDump() {
   
    if(m_flipEncoder.GetPosition() < HOPConstants::dumpPositionMin) {
        m_flipMotor.Set(HOPConstants::flipVelocity);
    } 
    else if(m_flipEncoder.GetPosition() > HOPConstants::dumpPositionMax) {
        m_flipMotor.Set(-HOPConstants::flipVelocity);
        }
   else {m_flipMotor.Set(0);}
}

void HOP::setFlipTumble() {
    if(m_flipEncoder.GetPosition() < HOPConstants::tumblePositionMax) {
        m_flipMotor.Set(0);
    } 
    else if(m_flipEncoder.GetPosition() > HOPConstants::tumblePositionMin) {
        m_flipMotor.Set(-HOPConstants::flipVelocity);
        }
   else {m_flipMotor.Set(0);}
}
