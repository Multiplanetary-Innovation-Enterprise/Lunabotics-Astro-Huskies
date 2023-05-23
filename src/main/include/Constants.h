// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <time.h>
#include <iostream>


/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace OperatorConstants {

constexpr int kDriverControllerPort = 0;
constexpr int jDriverControllerPort = 1;

}  // namespace OperatorConstants

namespace CAMConstants {
    //Chassis CAN IDs
    constexpr int driveMotor1ID = 13;
    constexpr int driveMotor2ID = 21;
    constexpr int driveMotor3ID = 20;
    constexpr int driveMotor4ID = 15;
}

namespace HOPConstants {
    //Hopper CAN IDs
    constexpr int beltMotorID = 22; 
    constexpr int flipMotorID = 14; 

    //Motor Speeds
    constexpr double beltVelocity = 0.4;
    constexpr double flipVelocity = 0.2;

    //Flipper Rotation Positions
    constexpr int stowPositionMin = -3;         // NOT FINALISED
    constexpr int stowPositionMax = 3;
    constexpr int dumpPositionMin = -95;        // NOT FINALISED
    constexpr int dumpPositionMax = -85;
    constexpr int tumblePositionMin = -140;     // NOT FINALISED
    constexpr int tumblePositionMax = -130;
}

namespace EXCConstants {
    //DIO ports
    static const int linearActuatorID_dir = 1;
    static const int linearActuatorID2_dir = 3;
    static const int linearActuatorID_speed = 0;
    static const int linearActuatorID_speed2 = 2;

    //Analog ports
    //static const int linearActuatorID1Pot = 1;
    //static const int linearActuatorID2Pot = 2;
    
    //CAM IDs
    constexpr int extendMotor1ID = 24;
    constexpr int extendMotor2ID = 25;
    constexpr int bucketSpinMotorID = 23;

    //Motor Speeds
    static const double extendVelocity = -0.3;
    static const double retractVelocity = 0.5;

    static const double linearActuatorVelocity = 0.5;
    static const double linearActuatorForwardValue = 0.5;
    static const double linearActuatorRetractValue = 0;

    static const double bucketSpinMotorSpeed = -0.26;

    //Excavator Extension Positions
    constexpr int maxRetraction = 0;
    constexpr int maxExtension = -3000;       //NOT FINALIZED
    constexpr double linearActuatorMax = 2100;
    constexpr double linearActuatorMin = 250;

    //Timers
    }

