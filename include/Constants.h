/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace constant
{
    class DriveTrainIDs{
        public:
            static constexpr int FRONT_LEFT     = 3;    //3
            static constexpr int FRONT_RIGHT    = 1;    //1
            static constexpr int BACK           = 2;    //2
    };
    //Motors
    static constexpr int TITAN_ID       = 42;

    class StorageIDs{
        public:
            static constexpr int ELEVATOR       = 0;
            static constexpr int GREIFZANGE     = 4; // 3
            static constexpr int GREIFARM       = 3; // 4
            static constexpr int LAGERUNG       = 2;
    };
    

    class Encoder{
        private:
            static constexpr double WHEEL_RADIUS    = 51; //mm
            static constexpr double PULSE_PER_REV   = 1464;
            static constexpr double GEAR_RATIO      = 1/1;
            static constexpr double ENCODER_PULSE_RATIO = PULSE_PER_REV * GEAR_RATIO;
        
        public:
            static constexpr double DIST_PER_TICK   =   (M_PI * 2 * WHEEL_RADIUS) / ENCODER_PULSE_RATIO;
    };

    class IRSensors{
        public:
                static constexpr int LEFT   = 1;
                static constexpr int RIGHT  = 0;
    };

    class USSensors{
        public:
            static constexpr int LEFT_TRIG  = 8;
            static constexpr int LEFT_ECHO  = 9;

            static constexpr int RIGHT_TRIG  = 10;
            static constexpr int RIGHT_ECHO  = 11;
    };

    class Elevator{
        public:
            static constexpr double SPEED = 0.3;
            static constexpr int POSITION_GRAB_CUBE = 3871-3750;//7739-7700; //-3750; // ev. 3650
            static constexpr int POSITON_QR_CODE = 2359;//956;//3871-880;//7739-2278; //-920; // -880
    };

    
    class Greifzange{
        private:
            static constexpr int MAX = 200.0;
            static constexpr int MIN = 107.0;

        public:
            static constexpr int ZU      = MIN;
            static constexpr int OFFEN   = MAX;
    };

    class Greifarm{
        private:
            static constexpr int MAX   = 243; //247
            static constexpr int MIN   = 90.0;

        public:
            static constexpr int OBEN = MAX;
            static constexpr int GERADE   = 155.5; //155
            static constexpr int GRAB_CUBE = 152;
            static constexpr int UNTEN = 130; //130
            static constexpr int MINIMUM = MIN;
    };
    
    class Lagerung{
        public:
            static constexpr int MAX_LAGERUNG   = 5;
            static constexpr int MAX_A_LAGERUNG = 300;
            static constexpr int MIN_A_LAGERUNG = 0;
            static constexpr double ANGLE[] = {14,71.5,129,186,250,312}; // {13,70.5,129,186,250,312}, {14,71.5,132,190,250,312}
            static constexpr int HANDLE_STORAGE = -1;
    };

    class Debug{
        public:
            // subsystems
            static constexpr bool DRIVE_BASE = true;
            static constexpr bool CAMERA = true;
            static constexpr bool SENSORS = true;
            static constexpr bool STORAGE = true;

            // commands
            
    };

    class Sensor_IDs{
        public:
            static constexpr int NONE = -1;
            static constexpr int US_R = 0;
            static constexpr int US_L = 1;
            static constexpr int IR_L = 2;
            static constexpr int IR_R = 3;
            static constexpr int IR_RL = 4;
            static constexpr int COBRA = 5;
    };

    class Camera{
        public:
            static constexpr int BLUE = 0;
            static constexpr int RED = 1;
            static constexpr int YELLOW = 2;
            static constexpr int GREEN = 3;
    };

    

    static constexpr double DISTANCE_TO_CUBE = 245; //25
    static constexpr double DISTANCE_TO_WALL = 260;  //260,160
    static constexpr double VALUE_LINE      = 2030;

    static constexpr double VALUE_WALL = 500;  // 500
    static constexpr double VALUE_WALL_MIN = 120;
    static constexpr double VALUE_WALL_MIN_US = 150;
    static constexpr double VALUE_WALL_MIN_BACK = 50;

    static constexpr int COBRA  = 0;

    static constexpr int DIAMETER = 16.3;

    static constexpr double ERROR_CHANGE = 0.00001;

    static constexpr double STARTING_ANGLE = 400;
}

//bool teleop = false;

namespace global
{
    //bool teleop;
   // int test_global;
   inline int test_global;

   inline double US_Left_Distance;
   inline double US_Right_Distance;
   inline double IR_Left_Distance;
   inline double IR_Right_Distance;
   inline double Elevator_Distance;

   inline double savedAngle;
   inline double lastAngle;

   inline bool SearchForCube;

   inline bool EnableInitElevator;

   inline bool EnablePControl;

   inline bool CameraEnabled;
   inline bool SearchForLine;

   inline int StoragePlace;
   inline int SelectRed;

   inline int CountSearchColor;
}
