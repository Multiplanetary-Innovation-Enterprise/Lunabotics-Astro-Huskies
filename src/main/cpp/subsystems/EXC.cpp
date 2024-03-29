// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/EXC.h"
#include "Constants.h"
#include <frc/DigitalOutput.h>
#include "RobotContainer.h"
#include <iostream>
#include "subsystems/HOP.h"
#include "subsystems/CAM.h"
#include <string.h>
#include <math.h>

using namespace std;
time_t time0;
time_t time1;
time_t time05;

int state = 0;
int isAuto = 0;
int Commandvar = 0;
// 0 -> CAM & HOP off
// 1 -> Set Flipper to Tumble
// 2 -> Drive Belt & CAM
// 3 -> Turn off Belt & CAM
// 4 -> Set Flipper to Dump

EXC::EXC(): 
    m_extendMotor1{EXCConstants::extendMotor1ID, rev::CANSparkMax::MotorType::kBrushless},
    m_extendMotor2{EXCConstants::extendMotor2ID, rev::CANSparkMax::MotorType::kBrushless},
    m_bucketSpinMotor{EXCConstants::bucketSpinMotorID, rev::CANSparkMax::MotorType::kBrushless},
    
    m_linearActuatordir1{EXCConstants::linearActuatorID_dir}, 
    m_linearActuatordir2{EXCConstants::linearActuatorID2_dir},
    m_linearActuatorSpeed1{EXCConstants::linearActuatorID_speed}, 
    m_linearActuatorSpeed2{EXCConstants::linearActuatorID_speed2},

    //m_linearActuatorPosition1{EXCConstants::linearActuatorID1Pot},
    //m_linearActuatorPosition2{EXCConstants::linearActuatorID2Pot},

    m_extendEncoder1{m_extendMotor1.GetEncoder()},
    m_extendEncoder2{m_extendMotor2.GetEncoder()}, 
    m_bucketEncoder{m_bucketSpinMotor.GetEncoder()} {}

// This method will be called once per scheduler run
void EXC::Periodic() {
    
}

int EXC::getExcavatorDepth() {
    if(m_extendEncoder1.GetPosition() >= m_extendEncoder2.GetPosition()) {
        return m_extendEncoder1.GetPosition();
    } else {return m_extendEncoder2.GetPosition();}
}

double EXC::getLinearActuatorPosition() {
    if(m_linearActuatorPosition1.GetValue() <= m_linearActuatorPosition2.GetValue()) {
        return m_linearActuatorPosition1.GetValue(); 
    } else { return m_linearActuatorPosition2.GetValue();}
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

void EXC::extendRightScrew(double speed){
    m_extendMotor1.Set(speed);
    /*string rightScrew = to_string(m_extendEncoder1.GetPosition());
    cout<<"\nRight Screw Encoder Value "<<rightScrew;
    string leftScrew = to_string(m_extendEncoder2.GetPosition());
    cout<<"\nLeftt Screw Encoder Value "<<leftScrew;*/
}

void EXC::setExtendVelocity(double speed) {
    if(abs(m_extendEncoder1.GetPosition()) - abs(m_extendEncoder2.GetPosition()) < 130){
        if(speed > 0){
            if(m_extendEncoder1.GetPosition() >= m_extendEncoder2.GetPosition()){
                m_extendMotor1.Set(speed*0.7);
                m_extendMotor2.Set(speed);
                
            }
            else if(m_extendEncoder1.GetPosition() <= m_extendEncoder2.GetPosition()){
                m_extendMotor1.Set(speed);
                m_extendMotor2.Set(speed*0.7);
            }
        }   
        else if(speed < 0){
            if(m_extendEncoder1.GetPosition() <= m_extendEncoder2.GetPosition()){
                m_extendMotor1.Set(speed*0.7);
                m_extendMotor2.Set(speed);
            }
            else if(m_extendEncoder1.GetPosition() >= m_extendEncoder2.GetPosition()){
                m_extendMotor1.Set(speed);
                m_extendMotor2.Set(speed*0.7);
            }
        } 
        else{
            m_extendMotor1.Set(0);
            m_extendMotor2.Set(0);
            string rightScrew = to_string(m_extendEncoder1.GetPosition());
            cout<<"\nRight Screw Encoder Value "<<rightScrew;
            string leftScrew = to_string(m_extendEncoder2.GetPosition());
            cout<<"\nLeftt Screw Encoder Value "<<leftScrew;
        }
    }
    else{
        m_extendMotor1.Set(0);
        m_extendMotor2.Set(0);
        string rightScrew = to_string(m_extendEncoder1.GetPosition());
        cout<<"\nRight Screw Encoder Value "<<rightScrew;
        string leftScrew = to_string(m_extendEncoder2.GetPosition());
        cout<<"\nLeftt Screw Encoder Value "<<leftScrew;
    }
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
    
    if(EXC::getLinearActuatorPosition() > EXCConstants::linearActuatorMin) {
        EXC::setLinearActuatordirection(EXCConstants::linearActuatorRetractValue);
        EXC::setLinearActuatorspeed(EXCConstants::linearActuatorVelocity);
    } 
    else {
        EXC::setLinearActuatordirection(0);
        EXC::setLinearActuatorspeed(0);
    }
}

void EXC::deployExcavator() {
    if(EXC::getLinearActuatorPosition() < EXCConstants::linearActuatorMax){
        EXC::setLinearActuatordirection(EXCConstants::linearActuatorForwardValue);
        EXC::setLinearActuatorspeed(EXCConstants::linearActuatorVelocity);
    }
    else {
        EXC::setLinearActuatordirection(0);
        EXC::setLinearActuatorspeed(0);
    }
    
    
}

void EXC::autoEXCState(int autoState) {
    isAuto = autoState;
}

int EXC::autoExcavator() {
    /*string AutoisAuto = to_string(autostate);
    cout<<"\nis auto?  "<<AutoisAuto;*/
    int autostate = isAuto;
    if(autostate == 1){
        //state = 0 ->initialize
        //state = 1 ->deploy
        //state = 2 ->extend & dig
        //state = 3 ->dig & drive //NOT IN USE
        //state = 4 ->retract & dig
        //state = 5 ->stow
        //state = 6 ->shutdown

        if(state == 0){     
            state = 1;
            time(&time0); //GetCurrentTime
        }
        
        else if (state == 1){
            if(EXC::getLinearActuatorPosition() >= EXCConstants::linearActuatorMax) {
                state = 2;
                EXC::setLinearActuatorspeed(0);
            } else{
                EXC::deployExcavator();
                Commandvar = 1;
            }
        }
        
        else if(state == 2){
            if(EXC::getExcavatorDepth() < EXCConstants::maxExtension){
                state = 4;
                EXC::setExtendVelocity(0);
                EXC::setBucketSpeed(0);
            }
            else{
                EXC::setBucketSpeed(EXCConstants::bucketSpinMotorSpeed);
                Commandvar = 2;
                time(&time05);
            if(((time05 - time0) % 3) == 1){
                EXC::setExtendVelocity(EXCConstants::extendVelocity);
            } else {EXC::setExtendVelocity(0);}
            
            }
        }
        
        else if(state == 3){
            time(&time1); //GetTimePassed
            if(time1 - time0 > 300){
                string timePassed = to_string(time1 - time0);
                cout<<"\nTime "<<timePassed;
                state = 4;
                EXC::setBucketSpeed(0);
                Commandvar = 3;
            } 
            else{
                 EXC::setBucketSpeed(EXCConstants::bucketSpinMotorSpeed);
                } 
                
                Commandvar = 2;
            }
        
        else if(state == 4){
            if(EXC::getExcavatorDepth() > EXCConstants::maxRetraction){
                state = 5;
                EXC::setExtendVelocity(0);
                Commandvar = 0;
            } 
            else{
                EXC::setExtendVelocity(EXCConstants::retractVelocity);
                Commandvar = 4;
            }
        }
        
        else if(state == 5){
            if(EXC::getLinearActuatorPosition() <= EXCConstants::linearActuatorMin) {
                state = 6;
                EXC::setLinearActuatorspeed(0);
            } else{EXC::stowExcavator();}
        }
        
        else if(state == 6){
            EXC::setBucketSpeed(0);
            EXC::setExtendVelocity(0);
            EXC::setLinearActuatorspeed(0);
            isAuto = 0;
            state = 6;
            Commandvar = 0;
        }
        
    }
    else if(autostate == 2) {               // PAUSE AUTONOMY
        EXC::setBucketSpeed(0);
        EXC::setExtendVelocity(0);
        EXC::setLinearActuatorspeed(0);
        isAuto = 0;
        Commandvar = 5;
    }
    
    else{                                   // END AUTONOMY
        EXC::setBucketSpeed(0);
        EXC::setExtendVelocity(0);
        EXC::setLinearActuatorspeed(0);
        Commandvar = 0;
        isAuto = 0; 

    }
    
    return Commandvar;                      // RETURNS INDICATOR FOR HOPPER
}