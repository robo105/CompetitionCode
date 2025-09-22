/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Storage.h"
#include <cmath>

studica::Servo ServoGreifzange{constant::StorageIDs::GREIFZANGE};
studica::Servo ServoGreifarm {constant::StorageIDs::GREIFARM};
studica::Servo ServoLagerung {constant::StorageIDs::LAGERUNG};

#define DEBUG1 true

Storage::Storage() {
}

double countStorage=0;

void setStorAngle(int angle)
{
  ServoLagerung.SetAngle(angle);
}

void setGreifarmAngle(int angle)
{
  ServoGreifarm.SetAngle(angle);
}

void setGreifzangeAngle(int angle)
{
  ServoGreifzange.SetAngle(angle);
}

double getGreifzangeAngle()
{
    return ServoGreifzange.GetAngle();
}

double getGreifarmAngle()
{
    return ServoGreifarm.GetAngle();
}

double getStorAngle()
{
    return ServoLagerung.GetAngle();
}

void Storage::Periodic() {
  // Implementation of subsystem periodic method goes here.
  GreifarmWinkel = getGreifarmAngle();
  GreifzangeWinkel = getGreifzangeAngle();
  LagerungWinkel = getStorAngle();

  HandleSpeedElevator();

  countStorage++;

  global::Elevator_Distance=GetElevatorEncoder();

  if(DEBUG1)
  {
    if(constant::Debug::STORAGE)
    {
        frc::SmartDashboard::PutNumber("countStorage", countStorage);
        frc::SmartDashboard::PutNumber("Angle Greifzange", GreifzangeWinkel);
        frc::SmartDashboard::PutNumber("Angle Greifarm", GreifarmWinkel);
        frc::SmartDashboard::PutNumber("Angle Lagerung", LagerungWinkel);
        frc::SmartDashboard::PutNumber("Encoder Lift", GetElevatorEncoder());
        frc::SmartDashboard::PutNumber("aktuelle Lagerung",global::StoragePlace);
    }
    
    if(GetLimitSwitch(true)==0)
    {
        //ElevatorPosition=0;
        EncoderElevator.Reset();
        //global::EnableInitElevator=false;
    }
  }
}

int Storage::GetElevatorRPM()
{
    return MotorElevator.GetRPM();
}

void Storage::SetSpeedElevator(double speed)
{
    lastSpeed=speed;
    if(EncoderElevator.GetRaw()>-1500&&speed>0)
    {
        speed*=0.5;
    }

    /*if(EncoderElevator.GetRaw()<10||speed<0)
    {
        MotorElevator.Set(speed);
    }*/

    if(GetLimitSwitch(false)!=0||speed<0)
    {
      MotorElevator.Set(speed);
    }
    
}

void Storage::HandleSpeedElevator()
{
    /*if(EncoderElevator.GetRaw()>=10&&lastSpeed>0&&global::EnableInitElevator==false)
    {
        MotorElevator.Set(-0.15);
    }*/
    /*else if(EncoderElevator.GetRaw()>-1500&&lastSpeed>0)
    {
        MotorElevator.Set(lastSpeed*0.5);
    }*/

    /*if(GetLimitSwitch(false)==0)
    {
        MotorElevator.Set(0);
    }*/
}

void Storage::SetHigh(double high)
{
    MotorElevator.Set(0);
    
}

double Storage::GetElevatorEncoder()
{
    if(constant::Debug::STORAGE)
    {
        frc::SmartDashboard::PutNumber("EncoderElevator",EncoderElevator.GetRaw());
    }
    
    return EncoderElevator.GetRaw();
}

void Storage::ResetElevatorEncoder() {
  EncoderElevator.Reset();
}

void Storage::SetStoragePosition(int Position)
{
    if(Position>=0&&Position<=constant::Lagerung::MAX_LAGERUNG)
    {
        setStorAngle(constant::Lagerung::ANGLE[Position]);
    }
}

void Storage::SetStorageAngle(double Angle)
{
    if((Angle<=constant::Lagerung::MAX_A_LAGERUNG&&Angle>=constant::Lagerung::MIN_A_LAGERUNG))
    {
        setStorAngle(Angle);
    }

    if(constant::Debug::STORAGE)
    {
        frc::SmartDashboard::PutNumber("Lagerung Winkel setzen",Angle);
    }
}

void Storage::SetGreifarm(double Position)
{
    if(Position<=constant::Greifarm::OBEN&&Position>=constant::Greifarm::MINIMUM)
    {
        setGreifarmAngle(Position);
    }
}

void Storage::SetGreifzange(bool zu)
{
    if(zu == true)
    {
        setGreifzangeAngle(constant::Greifzange::ZU);
    }
    else if(zu == false)
    {
        setGreifzangeAngle(constant::Greifzange::OFFEN);
    }
}

void Storage::SetServo(double Position)
{
       // Greifzange.SetAngle(Position);
    //}
}

double Storage::GetAngleGreifarm()
{
    return GreifarmWinkel;
}

double Storage::GetAngleGreifzange()
{
    return GreifzangeWinkel;
}

double Storage::GetAngleLagerung()
{
    return LagerungWinkel;
}

double Storage::GetLimitSwitch(bool oben)
{
    return MotorElevator.GetLimitSwitch(oben);
}

/*int Storage::GetFreeStorage()
{
    //TODO: Verwaltung der Lagerung
    return 0;
}*/