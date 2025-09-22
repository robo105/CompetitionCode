/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "Constants.h"
#include <cmath>

double countHolonomic = 0;
#define DEBUG true

DriveBase::DriveBase() {
  ResetEncoders();
  GetInverseMatrix();
  MotorLeft.InvertRPM();
  MotorRight.InvertRPM();
  MotorBack.InvertRPM();

  ResetIMU();
  SetHandleIMU();

  global::EnablePControl=false;

  if(constant::Debug::DRIVE_BASE)
  {
    frc::SmartDashboard::PutBoolean("Encoder Left Direction",EncoderLeft.GetDirection());
  }
  
  //TODO: Drehrichtung von Motoren anpassen
}

//int count = 0;
int countLeftSpeed=0;

bool DriveToTarget = false;

double SpeedLeft = 0;
double SpeedRight = 0;
double SpeedBack = 0;

double RPM = 100;
double SpeedTestLeft = 0;
double SpeedTestRight = 0;
double SpeedTestBack = 0;

double AimBack=0;
double AimLeft=0;
double AimRight=0;

double SpeedMAimBack=0;
double SpeedMAimRight=0;
double SpeedMAimLeft=0;

double DistanceAimBack=0;
double DistanceAimRight=0;
double DistanceAimLeft=0;

float Map(float value, float From1, float To1, float From2, float To2)
{
    return (value - From1) / (To1 - From1) * (To2 - From2) + From2;
}

double LimitValue(double value, double Bottom, double Top)
{
  if(value > Top)
  {
    return Top;
  }
  else if(value < Bottom)
  {
    return Bottom;
  }

  return value;  
}

/*
Setzen der Geschwindigkeit
Anpassen der Geschwindigkeit
*/

double Error_Help_Left = 0;
double Error_Help_Right = 0;
double Error_Help_Back = 0;

double Error_Left = 0.5*0.96*1.015*1.28*1.11*0.98*0.93*0.8*1.019*1.05;
double Error_Right = 0.5*1.12*1.013*1.35*1.28*0.98*0.74*0.8;
double Error_Back = 0.95*0.78*0.8*0.9;

double Start_Left = 0;
double Start_Right = 0;
double Start_Back = 0;

double save_Error_Left = 0;
double save_Error_Right = 0;
double save_Error_Back = 0;

int OptimizeLevel = 0;

//#define P_CONTROL 1


void DriveBase::SetSpeedBack(double speed, bool enable_ow)
{
  if(DistanceToSmall==true)
  {
    if(enable_ow==true)
    {
      MotorBack.Set(speed);
    }
    /*else
    {
      MotorBack.Set(0);
    }*/
  }
  else
  {
    MotorBack.Set(speed);
  }
}

void DriveBase::SetSpeedLeft(double speed, bool enable_ow)
{
  if(DistanceToSmall==true)
  {
    if(enable_ow==true)
    {
      MotorLeft.Set(speed);
    }
    /*else
    {
      MotorLeft.Set(0);
    }*/
  }
  else
  {
    MotorLeft.Set(speed);
  }
}

void DriveBase::SetSpeedRight(double speed, bool enable_ow)
{
  if(DistanceToSmall==true)
  {
    if(enable_ow==true)
    {
      MotorRight.Set(speed);
    }
    /*else
    {
      MotorRight.Set(0);
    }*/
  }
  else
  {
    MotorRight.Set(speed);
  }
}

void DriveBase::HandleDistanceToSmall()
{
  frc::SmartDashboard::PutNumber("DistanceToSmall Sensor",DistanceToSmallSensor);
  if(DistanceToSmall==true)
  {
    EnableMotorsOW=true;
    /*if(DistanceToSmallSensor==constant::Sensor_IDs::IR_R)
    {
      HolonomicDrive(0,-80,0,true);

      if((global::IR_Right_Distance*10)>(constant::VALUE_WALL_MIN+70))
      {
        DistanceToSmall=false;
      }
    }*/
    /*else if(DistanceToSmallSensor==constant::Sensor_IDs::IR_B)
    {
      HolonomicDrive(0,80,0,true);

      if((global::IR_Back_Distance*10)>(constant::VALUE_WALL_MIN_BACK+50))
      {
        DistanceToSmall=false;
      }
    }
    else*/ if(DistanceToSmallSensor==constant::Sensor_IDs::US_R)
    {
      HolonomicDrive(-80,0,0,true);

      if(global::US_Right_Distance>(constant::VALUE_WALL_MIN+50))
      {
        frc::SmartDashboard::PutNumber("Distance to Small false US Right",global::US_Right_Distance);
        DistanceToSmall=false;
      }
    }
    else if(DistanceToSmallSensor==constant::Sensor_IDs::US_L)
    {
      HolonomicDrive(80,0,0,true);

      if(global::US_Left_Distance>(constant::VALUE_WALL_MIN+50))
      {
        DistanceToSmall=false;
      }
    }
  }
  
  if(DistanceToSmall_Last==true && DistanceToSmall==false)
  {
    
    DistanceToSmall=false;
    //HolonomicDrive(0,0,0);
    DistanceToSmallSensor=constant::Sensor_IDs::NONE;
    EnableMotorsOW=false;
    /*EnableLeft=false;
    EnableRight=false;
    EnableBack=false;*/
  }

  DistanceToSmall_Last=DistanceToSmall;
}

/*
  0 = nix
  1 = Drehzahlen anpassen
  2 = 1 + IMU
*/
void DriveBase::SetOmptimizeLevel(int level)
{
  OptimizeLevel=level;
}

void DriveBase::SetFrontLeftSpeed(double speed, bool enable_ow)
{
  if(SpeedAimLeft!=speed||GetFrontLeftRPM()==0)
  {
    if(enable_ow==true||DistanceToSmall==false)
    {
      SpeedAimLeft=speed;
      SpeedSetLeft=Map(speed*Error_Left,-100,100,-1.0,1.0);

      #ifndef P_CONTROL
        SetSpeedLeft(SpeedSetLeft, enable_ow);
      #endif
      if(global::EnablePControl==false)
      {
        SetSpeedLeft(SpeedSetLeft, enable_ow);
      }

      Start_Left = speed*Error_Left;
    }

    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("Speed Aim Left",SpeedAimLeft);
    }
  }
}

void DriveBase::SetFrontRightSpeed(double speed, bool enable_ow)
{
  if(SpeedAimRight!=speed||GetFrontRightRPM()==0)
  {
    if(enable_ow==true||DistanceToSmall==false)
    {
      SpeedAimRight=speed;
      SpeedSetRight=Map(speed*Error_Right,-100,100,-1.0,1.0);

      #ifndef P_CONTROL
        SetSpeedRight(SpeedSetRight, enable_ow);
      #endif

      if(global::EnablePControl==false)
      {
        SetSpeedRight(SpeedSetRight, enable_ow);
      }

      Start_Right = speed*Error_Right;
    }
    
    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("Speed Aim Right",SpeedAimRight);
    }
  }
}

void DriveBase::SetBackSpeed(double speed, bool enable_ow)
{
  if(SpeedAimBack!=speed||GetBackRPM())
  {
    if(enable_ow==true||DistanceToSmall==false)
    {
      SpeedAimBack=speed;
      SpeedSetBack=Map(speed*Error_Back,-100,100,-1.0,1.0);

      #ifndef P_CONTROL
        SetSpeedBack(SpeedSetBack, enable_ow);
      #endif

      if(global::EnablePControl==false)
      {
        SetSpeedBack(SpeedSetBack, enable_ow);
      }
      
      Start_Back = speed*Error_Back;
    }

    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("Speed Aim Back",SpeedAimBack);
    }
  }
}

void DriveBase::OptimizeFrontLeftSpeedPControl()
{
    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("Differenz Speed Front Left",GetFrontLeftRPM()-SpeedAimLeft);
    }

    static double LastSpeed=0;
    static double LastSpeedSet=0;
    static double LastCount=0;
    static double Count=0;

    Count++;

    double change = 0;
    //SpeedAimLeft=CalculateIMU(SpeedAimLeft);
    if(LastSpeed!=GetFrontLeftRPM()|| LastSpeedSet!=SpeedAimLeft || countLeftSpeed-LastCount>50)
    {
      change = Map(SpeedAimLeft-GetFrontLeftRPM(),-100,100,-1,1)*0.2;
      SpeedSetLeft+=change;
      
      SpeedSetLeft=LimitValue(SpeedSetLeft,-1,1);
      LastSpeedSet = SpeedAimLeft;
      LastSpeed = GetFrontLeftRPM();
      LastCount = Count;
    }

    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("CountLeftSpeed",countLeftSpeed);
      frc::SmartDashboard::PutNumber("Speed Front Left change",change);
      frc::SmartDashboard::PutNumber("SpeedSetLeft",SpeedSetLeft);
      frc::SmartDashboard::PutNumber("Error Left",SpeedSetLeft/Map(Start_Left,-100,100,-1.0,1.0));
      frc::SmartDashboard::PutNumber("Saved Error Left",save_Error_Left);
      frc::SmartDashboard::PutNumber("RPM Left Optimize",GetFrontLeftRPM());
      frc::SmartDashboard::UpdateValues();
    }

    /*SpeedAimLeft=CalculateIMU(SpeedAimLeft);
    SetSpeedLeft(SpeedSetLeft,EnableMotorsOW);*/
    SetSpeedLeft(SpeedSetLeft,EnableMotorsOW);
}

void DriveBase::OptimizeFrontRightSpeedPControl()
{
    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("Differenz Speed Front Left",GetFrontRightRPM()-SpeedAimRight);
    }

    static double LastSpeed=0;
    static double LastSpeedSet=0;
    static double LastCount=0;
    static double Count=0;

    double change = 0;
    Count++;
    //SpeedAimRight=CalculateIMU(SpeedAimRight);
    if(LastSpeed!=GetFrontRightRPM()|| LastSpeedSet!=SpeedAimRight || Count-LastCount>50)
    {
      change = Map(SpeedAimRight-GetFrontRightRPM(),-100,100,-1,1)*0.2;
      SpeedSetRight+=change;
      
      SpeedSetRight=LimitValue(SpeedSetRight,-1,1);
      LastSpeedSet = SpeedAimRight;
      LastSpeed = GetFrontRightRPM();
      LastCount=Count;
    }

    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("Speed Front Right change",change);
      frc::SmartDashboard::PutNumber("RPM Right Optimize",GetFrontRightRPM());
      frc::SmartDashboard::UpdateValues();
    }
    
    /*SpeedAimRight=CalculateIMU(SpeedAimRight);
    SetSpeedRight(SpeedSetRight,EnableMotorsOW);*/
    SetSpeedRight(SpeedSetRight,EnableMotorsOW);
}

void DriveBase::OptimizeBackSpeedPControl()
{
    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("Differenz Speed Front Left",GetBackRPM()-SpeedAimBack);
    }

    static double LastSpeed=0;
    static double LastSpeedSet=0;
    static double LastCount=0;
    static double Count=0;

    double change = 0;
    Count++;
    //SpeedAimBack=CalculateIMU(SpeedAimBack);
    if(LastSpeed!=GetBackRPM()|| LastSpeedSet!=SpeedAimBack || Count-LastCount>50)
    {
      change = Map(SpeedAimBack-GetBackRPM(),-100,100,-1,1)*0.2;
      SpeedSetBack+=change;
      
      SpeedSetBack=LimitValue(SpeedSetBack,-1,1);
      LastSpeedSet = SpeedAimBack;
      LastSpeed = GetBackRPM();
      LastCount=Count;
    }

    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("Speed Back change",change);
      frc::SmartDashboard::PutNumber("RPM Back Optimize",GetBackRPM());
      frc::SmartDashboard::UpdateValues();
    }
    /*SpeedAimBack=CalculateIMU(SpeedAimBack);
    SetSpeedBack(SpeedSetBack,EnableMotorsOW);*/
    SetSpeedBack(SpeedSetBack,EnableMotorsOW);

}

void DriveBase::OptimizeFrontLeftSpeed()
{
    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("Differenz Speed Front Left",GetFrontLeftRPM()-SpeedAimLeft);
    }

    /*static double LastSpeed=0;
    static double LastSpeedSet=0;
    static double LastCount=0;*/
    
    if(GetFrontLeftRPM()<SpeedAimLeft)
    {
      SpeedSetLeft+=constant::ERROR_CHANGE;

      if(GetFrontLeftRPM()==0)
      {
        SpeedSetLeft+=constant::ERROR_CHANGE*1000;
      }
      //SpeedSetLeft=Map(GetFrontLeftRPM(),-100,100,-1.0,1.0)+
    }
    else if(GetFrontLeftRPM()>SpeedAimLeft)
    {
      SpeedSetLeft-=constant::ERROR_CHANGE;

      if(GetFrontLeftRPM()==0)
      {
        SpeedSetLeft-=constant::ERROR_CHANGE*1000;
      }
    }

    /*if(LastSpeed!=GetFrontLeftRPM()|| LastSpeedSet!=SpeedAimLeft || countLeftSpeed-LastCount>50)
    {
      SpeedSetLeft+=Map(SpeedAimLeft-GetFrontLeftRPM(),-100,100,-1,1)*0.8;
      LastSpeedSet = SpeedAimLeft;
      LastSpeed = GetFrontLeftRPM();
      LastCount = countLeftSpeed;
    }*/

    countLeftSpeed++;
    
    if(SpeedSetLeft/Map(Start_Left,-100,100,-1.0,1.0)>0.005&&SpeedSetLeft/Map(Start_Left,-100,100,-1.0,1.0)!=INFINITY)
    {
      save_Error_Left=SpeedSetLeft/Map(Start_Left,-100,100,-1.0,1.0);
    }

    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("CountLeftSpeed",countLeftSpeed);
      frc::SmartDashboard::UpdateValues();
      frc::SmartDashboard::PutNumber("SpeedSetLeft",SpeedSetLeft);
      frc::SmartDashboard::PutNumber("Error Left",SpeedSetLeft/Map(Start_Left,-100,100,-1.0,1.0));
      frc::SmartDashboard::PutNumber("Saved Error Left",save_Error_Left);
      frc::SmartDashboard::PutNumber("RPM Left Optimize",GetFrontLeftRPM());
    }

    SetSpeedLeft(CalculateIMU(SpeedSetLeft),EnableMotorsOW);
}

void DriveBase::OptimizeFrontRightSpeed()
{
    if(GetFrontRightRPM()<SpeedAimRight)
    {
      SpeedSetRight+=constant::ERROR_CHANGE;

      if(GetFrontRightRPM()==0)
      {
        SpeedSetRight+=constant::ERROR_CHANGE*1000;
      }
    }
    else if(GetFrontRightRPM()>SpeedAimRight)
    {
      SpeedSetRight-=constant::ERROR_CHANGE;

      if(GetFrontRightRPM()==0)
      {
        SpeedSetRight-=constant::ERROR_CHANGE*1000;
      }
    }
    SetSpeedRight(CalculateIMU(SpeedSetRight),EnableMotorsOW);

    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("SpeedSetRight",SpeedSetRight);
      frc::SmartDashboard::PutNumber("Error Right",SpeedSetRight/Map(Start_Right,-100,100,-1.0,1.0));
      frc::SmartDashboard::PutNumber("Saved Error Right",save_Error_Right);
    }
    
    if(SpeedSetRight/Map(Start_Right,-100,100,-1.0,1.0)>0.005&&SpeedSetRight/Map(Start_Right,-100,100,-1.0,1.0)!=INFINITY)
    {
      save_Error_Right=SpeedSetRight/Map(Start_Right,-100,100,-1.0,1.0);
    }
}

void DriveBase::OptimizeBackSpeed()
{
  if(GetBackRPM()<SpeedAimBack)
  {
    SpeedSetBack+=constant::ERROR_CHANGE;

    if(GetBackRPM()==0)
    {
      SpeedSetBack+=constant::ERROR_CHANGE*1000;
    }
  }
  else if(GetBackRPM()>SpeedAimBack)
  {
    SpeedSetBack-=constant::ERROR_CHANGE;

    if(GetBackRPM()==0)
    {
      SpeedSetBack-=constant::ERROR_CHANGE*1000;
    }
  }
  
  SetSpeedBack(CalculateIMU(SpeedSetBack),EnableMotorsOW);

  if(SpeedSetBack/Map(Start_Back,-100,100,-1.0,1.0)>0.005&&SpeedSetBack/Map(Start_Back,-100,100,-1.0,1.0)!=INFINITY)
  {
    save_Error_Back=SpeedSetBack/Map(Start_Back,-100,100,-1.0,1.0);
  }

  if(constant::Debug::DRIVE_BASE)
  {
    frc::SmartDashboard::PutNumber("SpeedSetBack",SpeedSetBack);
    frc::SmartDashboard::PutNumber("Error Back",SpeedSetBack/Map(Start_Back,-100,100,-1.0,1.0));
    frc::SmartDashboard::PutNumber("Saved Error Back",save_Error_Back);
  }
}

int GetGreatest(double a, double b, double c)
{
  if(a>b&&a>c)
  {
    return 0;
  }
  else if(b>a&&b>c)
  {
    return 1;
  }
  else if(c>a&&c>b)
  {
    return 2;
  }

  return 2;
}

double Drive_DistanceLeft=0, Drive_DistanceRight=0, Drive_DistanceBack =0;
double Drive_SpeedMultiLeft=0, Drive_SpeedMultiRight=0, Drive_SpeedMultiBack =0;
double Drive_speed = 50;

void DriveBase::SetPositionX(double x)
{
  Position_x = x;
}

double DriveBase::GetPositionX()
{
  return Position_x;
}

void DriveBase::HandelSpeeds()
{
  //DistanceToSmall_Last=DistanceToSmall;
  //DistanceToSmall=false;
  //DistanceToSmallSensor=constant::Sensor_IDs::NONE;

  if(global::US_Left_Distance<constant::VALUE_WALL_MIN_US)
  {
    SetBackSpeed(0);
    SetFrontLeftSpeed(0);
    SetFrontRightSpeed(0);

    DistanceToSmallSensor=constant::Sensor_IDs::US_L;
    DistanceToSmall=true;
    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("DistanceToSmall US Left",global::US_Left_Distance);
    }
  }
  else if(global::US_Right_Distance<constant::VALUE_WALL_MIN_US)
  {
    SetBackSpeed(0);
    SetFrontLeftSpeed(0);
    SetFrontRightSpeed(0);

    DistanceToSmallSensor=constant::Sensor_IDs::US_R;
    DistanceToSmall=true;
    if(constant::Debug::DRIVE_BASE)
    {
      frc::SmartDashboard::PutNumber("DistanceToSmall US Right",global::US_Right_Distance);
    }
  }
  /*else if(global::IR_Right_Distance<(constant::VALUE_WALL_MIN/10))
  {
    if(global::Elevator_Distance<-850 && global::SearchForCube==false)
    {
      SetBackSpeed(0);
      SetFrontLeftSpeed(0);
      SetFrontRightSpeed(0);

      DistanceToSmallSensor=constant::Sensor_IDs::IR_L;
      DistanceToSmall=true;
      if(constant::Debug::DRIVE_BASE)
      {
        frc::SmartDashboard::PutNumber("DistanceToSmall IR Left",global::IR_Left_Distance);
      }
    }
  }*/
  /*else if(global::IR_Right_Distance<(constant::VALUE_WALL_MIN_BACK/10))
  {
    SetBackSpeed(0);
    SetFrontLeftSpeed(0);
    SetFrontRightSpeed(0);

    DistanceToSmallSensor=constant::Sensor_IDs::IR_R;
    DistanceToSmall=true;
    if(constant::Debug::DRIVE_BASE)
    {
      //frc::SmartDashboard::PutNumber("DistanceToSmall IR Right",global::IR_Right_Distance);
    }
  }*/

  if(constant::Debug::DRIVE_BASE)
  {
    frc::SmartDashboard::PutBoolean("DistanceToSmall",DistanceToSmall);
    frc::SmartDashboard::PutNumber("DriveBase IR Left saved",global::IR_Left_Distance);
    frc::SmartDashboard::PutNumber("DriveBase IR Right saved",global::IR_Right_Distance);
    frc::SmartDashboard::PutNumber("DriveBase US Left saved",global::US_Left_Distance);
    frc::SmartDashboard::PutNumber("DriveBase US Right saved",global::US_Right_Distance);
  }
  
}

void DriveBase::Periodic() {
  
  if(OptimizeLevel>=1)
  {
    /*if(global::EnablePControl==true)
    {
      OptimizeBackSpeedPControl();
      OptimizeFrontLeftSpeedPControl();
      OptimizeFrontRightSpeedPControl();
    }
    else
    {
      OptimizeBackSpeed();
      OptimizeFrontLeftSpeed();
      OptimizeFrontRightSpeed();
    }*/

    #ifdef P_CONTROL
      OptimizeFrontLeftSpeedPControl();
      OptimizeFrontRightSpeedPControl();
      OptimizeBackSpeedPControl();
    #else
      OptimizeFrontLeftSpeed();
      OptimizeFrontRightSpeed();
      OptimizeBackSpeed();
    #endif
    
  }
  
  
  //HandleDistanceToSmall();
  //HandelSpeeds();

  if(constant::Debug::DRIVE_BASE)
  {
    frc::SmartDashboard::PutNumber("Yaw",GetYaw());
    frc::SmartDashboard::PutNumber("startingAngle",startingAngle);
    
    /*frc::SmartDashboard::PutNumber("Matrix X Distance",GetXDistanceRaw());
    frc::SmartDashboard::PutNumber("Matrix Y Distance",GetYDistanceRaw());
    frc::SmartDashboard::PutNumber("Matrix W Distance",GetWDistanceRaw());*/
    frc::SmartDashboard::PutNumber("OptimizeLevel",OptimizeLevel);
    frc::SmartDashboard::PutNumber("RPM Left",GetFrontLeftRPM());
    frc::SmartDashboard::PutNumber("RPM Right",GetFrontRightRPM());
    frc::SmartDashboard::PutNumber("RPM Back",GetBackRPM());

    //frc::SmartDashboard::PutNumber("Global",global::test_global);
  }
}

#define SPEED_LEFT 1.0
#define SPEED_RIGHT 1.0

void DriveBase::HolonomicDrive(double xSpeed, double ySpeed, double wSpeed, bool enable_ow)
{
  xSpeed = -xSpeed;
  ySpeed = -ySpeed;
  float a = cos(240*(M_PI/180));   float b = cos(120*(M_PI/180));   float c = cos(0*(M_PI/180));
  float d = sin(240*(M_PI/180));    float e = sin(120*(M_PI/180));    float f = sin(0*(M_PI/180));
  float g = 1;                float h = 1;               float i = 1;

  float det = a * e * i + b * f * g + c * d * h - c * e * g - a * f * h - b * d * i; 

  float a_inverse = (e * i - f * h) / det;    float b_inverse = (h * c - i * b) / det;   float c_inverse = (b * f - c * e)  / det;
  float d_inverse = (g * f - d * i) / det;    float e_inverse = (a * i - g * c) / det;   float f_inverse = (d * c - a * f) / det;
  float g_inverse = (d * h - g * e) / det;  float h_inverse = (g * b - a * h) / det; float i_inverse = (a * e - d * b)  / det;

  countHolonomic++;

  double SpeedFrontLeft = a_inverse * xSpeed + b_inverse * ySpeed + c_inverse * wSpeed;
  double SpeedFrontRight = d_inverse * xSpeed + e_inverse * ySpeed + f_inverse * wSpeed;
  double SpeedBack = g_inverse * xSpeed + h_inverse * ySpeed + i_inverse * wSpeed;

  //SpeedFrontLeft*=SPEED_LEFT;
  //SpeedFrontRight*=SPEED_RIGHT;

  frc::SmartDashboard::PutNumber("SpeedFrontLeft",SpeedFrontLeft);
  frc::SmartDashboard::PutNumber("SpeedFrontRight",SpeedFrontRight);
  frc::SmartDashboard::PutNumber("SpeedBack",SpeedBack);

  SetFrontLeftSpeed(SpeedFrontLeft, enable_ow);
  SetFrontRightSpeed(SpeedFrontRight, enable_ow);
  SetBackSpeed(SpeedBack, enable_ow);
  
  //TODO: PID Controller hinzufügen
}

void DriveBase::HolonomicDriveWithoutOptimize(double xSpeed, double ySpeed, double wSpeed)
{
  xSpeed = -xSpeed;
  //ySpeed = ySpeed;

  float a = cos(240*(M_PI/180));   float b = cos(120*(M_PI/180));   float c = cos(0*(M_PI/180));
  float d = sin(240*(M_PI/180));    float e = sin(120*(M_PI/180));    float f = sin(0*(M_PI/180));
  float g = 1;                float h = 1;               float i = 1;

  float det = a * e * i + b * f * g + c * d * h - c * e * g - a * f * h - b * d * i; 

  float a_inverse = (e * i - f * h) / det;    float b_inverse = (h * c - i * b) / det;   float c_inverse = (b * f - c * e)  / det;
  float d_inverse = (g * f - d * i) / det;    float e_inverse = (a * i - g * c) / det;   float f_inverse = (d * c - a * f) / det;
  float g_inverse = (d * h - g * e) / det;  float h_inverse = (g * b - a * h) / det; float i_inverse = (a * e - d * b)  / det;

  countHolonomic++;

  double SpeedFrontLeft = a_inverse * xSpeed + b_inverse * ySpeed + c_inverse * wSpeed;
  double SpeedFrontRight = d_inverse * xSpeed + e_inverse * ySpeed + f_inverse * wSpeed;
  double SpeedBack = g_inverse * xSpeed + h_inverse * ySpeed + i_inverse * wSpeed;

  //frc::SmartDashboard::PutNumber("xSpeed Set",xSpeed);

  SetSpeedLeft(SpeedFrontLeft, false);
  SetSpeedRight(SpeedFrontRight, false);
  SetSpeedBack(SpeedBack, false);
  
  //TODO: PID Controller hinzufügen
}

void DriveBase::SetHandleIMU()
{
  startingAngle=GetYaw();
  //startingAngle=180;
}

double DriveBase::GetStartingAngle()
{
  return startingAngle;
}

double DriveBase::CalculateIMU(double speed)
{
  static double LastYaw=0;
  static double LastSpeedSet=0;
  static double LastCount=0;
  static int CountIMU=0;

  CountIMU++;

  frc::SmartDashboard::PutBoolean("CalculateIMU",false);

  if(OptimizeLevel>=2)
  {
    //frc::SmartDashboard::PutNumber("savedAngle",global::savedAngle);

    
    /*if(global::savedAngle>GetYaw())
    {
      if(constant::Debug::DRIVE_BASE)
      {
        frc::SmartDashboard::PutNumber("Yaw zu klein",global::savedAngle-GetYaw());
        frc::SmartDashboard::PutBoolean("CalculateIMU",true);
      }
      
      return speed+(0.03);// 0.02 //0.035 //+abs(startingAngle-GetYaw()/10000000));
    }
    else if(global::savedAngle<GetYaw())
    {
      if(constant::Debug::DRIVE_BASE)
      {
        frc::SmartDashboard::PutNumber("Yaw zu groß",global::savedAngle-GetYaw());
        frc::SmartDashboard::PutBoolean("CalculateIMU",true);
      }
      
      return speed-(0.03);//0.02 //0.035 //+abs(startingAngle-GetYaw()/10000000));
    }*/
    if(LastYaw!=GetYaw()|| LastSpeedSet!=SpeedAimLeft || CountIMU-LastCount>50)
    {
      double t;
      t = global::savedAngle - GetYaw();
      double t1 = (t - (((int)(t / 180)) * 360));

      double change = LimitValue((t1)*0.05,-0.05,0.05); // 0.05
      
      frc::SmartDashboard::PutNumber("CalculateIMU change",change);
      frc::SmartDashboard::PutBoolean("CalculateIMU",true);
      //LastSpeedSet = SpeedAimLeft;
      LastYaw = GetYaw();
      LastCount = CountIMU;
      
      return speed+=change;
    }
    
  }
  
  return speed;
}

double DriveBase::GetFrontLeftEncoder() {
  return EncoderLeft.GetEncoderDistance();
}

double DriveBase::GetFrontRightEncoder() {
  return EncoderRight.GetEncoderDistance();
}

double DriveBase::GetBackEncoder() {
  return EncoderBack.GetEncoderDistance();
}

double DriveBase::GetFrontLeftEncoderRaw() {
  return EncoderLeft.GetRaw();
}

double DriveBase::GetFrontRightEncoderRaw() {
  return EncoderRight.GetRaw();
}

double DriveBase::GetBackEncoderRaw() {
  return EncoderBack.GetRaw();
}

int DriveBase::GetFrontLeftRPM() {
  const int RunningAverageCount = 16;               // Anzahl der in den Laufenden-Mettelwert aufgenommenen Messungen
  static double RunningAverageBuffer[RunningAverageCount];
  static int NextRunningAverage;

  //double RunningAverageDistance = calculateAverage(RunningAverageBuffer,&NextRunningAverage,US_Right.GetRangeMM());

  double RawDistance = MotorLeft.GetRPM();
 
  RunningAverageBuffer[NextRunningAverage++] = RawDistance;
  if (NextRunningAverage >= RunningAverageCount)
  {
      NextRunningAverage = 0; 
  }
  float RunningAverageDistance = 0;
  for(int i=0; i< RunningAverageCount; ++i)
  {
      RunningAverageDistance += RunningAverageBuffer[i];
  }
  RunningAverageDistance /= RunningAverageCount;

  return RunningAverageDistance;
}

int DriveBase::GetFrontRightRPM() {
  const int RunningAverageCount = 16;               // Anzahl der in den Laufenden-Mettelwert aufgenommenen Messungen
  static double RunningAverageBuffer[RunningAverageCount];
  static int NextRunningAverage;

  //double RunningAverageDistance = calculateAverage(RunningAverageBuffer,&NextRunningAverage,US_Right.GetRangeMM());

  double RawDistance = MotorRight.GetRPM();
 
  RunningAverageBuffer[NextRunningAverage++] = RawDistance;
  if (NextRunningAverage >= RunningAverageCount)
  {
      NextRunningAverage = 0; 
  }
  float RunningAverageDistance = 0;
  for(int i=0; i< RunningAverageCount; ++i)
  {
      RunningAverageDistance += RunningAverageBuffer[i];
  }
  RunningAverageDistance /= RunningAverageCount;
  
  return RunningAverageDistance;
}

int DriveBase::GetBackRPM() {
  const int RunningAverageCount = 16;               // Anzahl der in den Laufenden-Mettelwert aufgenommenen Messungen
  static double RunningAverageBuffer[RunningAverageCount];
  static int NextRunningAverage;

  //double RunningAverageDistance = calculateAverage(RunningAverageBuffer,&NextRunningAverage,US_Right.GetRangeMM());

  double RawDistance = MotorBack.GetRPM();
 
  RunningAverageBuffer[NextRunningAverage++] = RawDistance;
  if (NextRunningAverage >= RunningAverageCount)
  {
      NextRunningAverage = 0; 
  }
  float RunningAverageDistance = 0;
  for(int i=0; i< RunningAverageCount; ++i)
  {
      RunningAverageDistance += RunningAverageBuffer[i];
  }
  RunningAverageDistance /= RunningAverageCount;
  
  return RunningAverageDistance;
}

void DriveBase::ResetEncoders() {
  EncoderLeft.Reset();
  EncoderRight.Reset();
  EncoderBack.Reset();
}

bool DriveBase::GetInverseMatrix()
{
  mat[0][0]=0;
  mat[0][1]=1;
  mat[0][2]=constant::DIAMETER;

  mat[1][0]=-sin(60*(M_PI/180));
  mat[1][1]=-0.5;
  mat[1][2]=constant::DIAMETER;

  mat[2][0]=sin(60*(M_PI/180));
  mat[2][1]=-0.5;
  mat[2][2]=constant::DIAMETER;

  double d = 0;

  for(int i = 0; i < 3; i++)
    d = d + (mat[0][i] * (mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3] * mat[2][(i+1)%3]));
    
  if(d>0)
  {
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
        {
          inv_mat[i][j]=((mat[(j+1)%3][(i+1)%3] * mat[(j+2)%3][(i+2)%3]) - (mat[(j+1)%3][(i+2)%3] * mat[(j+2)%3][(i+1)%3]))/ d;
        }
     }
     return true;
  }
  return false;
}

double DriveBase::GetXDistance()
{
  //double distance = (EncoderBack.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][0]+(EncoderRight.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][1]+(EncoderLeft.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][2];
  double distance = EncoderBack.GetEncoderDistance()*inv_mat[1][0]+EncoderRight.GetEncoderDistance()*inv_mat[1][1]+EncoderLeft.GetEncoderDistance()*inv_mat[1][2];

  return distance;
}

double DriveBase::GetXDistanceRaw()
{
  //double distance = (EncoderBack.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][0]+(EncoderRight.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][1]+(EncoderLeft.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][2];
  double distance = (EncoderBack.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[1][0]+(EncoderRight.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[1][1]+(EncoderLeft.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[1][2];

  return distance;
}

/*double DriveBase::GetYDistance()
{
  double distance = (EncoderBack.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][0]+(EncoderRight.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][1]+(EncoderLeft.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][2];
  
  
  return distance;
}*/

double DriveBase::GetYDistance()
{
  double distance = EncoderBack.GetEncoderDistance()*inv_mat[0][0]+EncoderRight.GetEncoderDistance()*inv_mat[0][1]+EncoderLeft.GetEncoderDistance()*inv_mat[0][2];

  return distance;
}

double DriveBase::GetYDistanceRaw()
{
  double distance = (EncoderBack.GetRaw()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][0]+(EncoderRight.GetRaw()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][1]+(EncoderLeft.GetRaw()*constant::Encoder::DIST_PER_TICK)*inv_mat[0][2];
  //double distance = (EncoderBack.GetRaw()*constant::Encoder::DIST_PER_TICK)*inv_mat[1][0]+(EncoderRight.GetRaw()*constant::Encoder::DIST_PER_TICK)*inv_mat[1][1]+(EncoderLeft.GetRaw()*constant::Encoder::DIST_PER_TICK)*inv_mat[1][2];
  
  return distance;
}

double DriveBase::GetYEncoder()
{
  double distance = (EncoderBack.GetEncoderDistance())*inv_mat[0][0]+(EncoderRight.GetEncoderDistance())*inv_mat[0][1]+(EncoderLeft.GetEncoderDistance())*inv_mat[0][2];
  //double distance = (EncoderBack.GetEncoderDistance())*inv_mat[1][0]+(EncoderRight.GetEncoderDistance())*inv_mat[1][1]+(EncoderLeft.GetEncoderDistance())*inv_mat[1][2];
  
  return distance;
}

double DriveBase::GetWDistance()
{
  double distance = EncoderBack.GetEncoderDistance()*inv_mat[2][0]+EncoderRight.GetEncoderDistance()*inv_mat[2][1]+EncoderLeft.GetEncoderDistance()*inv_mat[2][2];

  return distance;
}

double DriveBase::GetWDistanceRaw()
{
  double distance = (EncoderBack.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[2][0]+(EncoderRight.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[2][1]+(EncoderLeft.GetEncoderDistance()*constant::Encoder::DIST_PER_TICK)*inv_mat[2][2];

  return distance;
}

float DriveBase::GetYaw()
{
  const int RunningAverageCount = 16;               // Anzahl der in den Laufenden-Mettelwert aufgenommenen Messungen
  static double RunningAverageBuffer[RunningAverageCount];
  static int NextRunningAverage;

  //double RunningAverageDistance = calculateAverage(RunningAverageBuffer,&NextRunningAverage,US_Right.GetRangeMM());

  double RawDistance = (navX.GetYaw())+180;
 
  RunningAverageBuffer[NextRunningAverage++] = RawDistance;
  if (NextRunningAverage >= RunningAverageCount)
  {
      NextRunningAverage = 0; 
  }
  float RunningAverageDistance = 0;
  for(int i=0; i< RunningAverageCount; ++i)
  {
      RunningAverageDistance += RunningAverageBuffer[i];
  }
  RunningAverageDistance /= RunningAverageCount;

  return RunningAverageDistance;
}

void DriveBase::ResetDisplacement()
{
  navX.ResetDisplacement();
}

float DriveBase::GetYDisplacementIMU()
{
  return navX.GetDisplacementX();
}

void DriveBase::ResetIMU()
{
  navX.Reset();
  navX.Calibrate();

  while(navX.IsCalibrating());
}