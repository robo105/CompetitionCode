#include "commands/Drive/FollowWall.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

FollowWall::FollowWall(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, bool RightSide, double Distance, int SensorID, bool StopAtTwoWalls, double DistanceToWall)
{
    AddRequirements({drive,sensor});
    m_drive = drive;
    m_sensors = sensor;
    m_RightSide = RightSide;
    m_distance = Distance;
    m_SensorID = SensorID;

    m_StopAtTwoWalls = StopAtTwoWalls;
    m_DistanceToWall = DistanceToWall;
}

void FollowWall::Initialize()
{
    m_drive->HolonomicDrive(0,0,0);
    m_drive->SetOmptimizeLevel(1);

    m_drive->ResetEncoders();

    /*if(m_sensors->USRightDistance()<constant::VALUE_WALL)
    {
        m_RightSide=true;
    }
    else if(m_sensors->USLeftDistance()<constant::VALUE_WALL)
    {
        m_RightSide=false;
    }*/    

    if(m_RightSide==true)
    {
        lastMeasure = m_sensors->USRightDistance();
    }
    else
    {
        lastMeasure = m_sensors->USLeftDistance();
    }
    
    startingDistance = m_drive->GetYDistanceRaw();
}

double LimitValueToBorder(double value, double Bottom, double Top)
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

void FollowWall::Execute()
{
    if(m_RightSide==true)
    {
        actMeasure = m_sensors->USRightDistance();
    }
    else
    {
        actMeasure = m_sensors->USLeftDistance();
    }

    if(actMeasure>lastMeasure)
    {
        if(actMeasure<m_DistanceToWall)
        {
            speedBack=0;
        }
        else //if(actMeasure>constant::DISTANCE_TO_WALL+0.1*constant::DISTANCE_TO_WALL)
        {
            //speedBack=LimitValueToBorder((actMeasure-lastMeasure),0,25);
            if(m_RightSide==true)
            {
                speedBack=20;
            }
            else
            {
                speedBack=-20;
            }
            //speedBack=20;
        }

    }
    else if(actMeasure<lastMeasure)
    {
        if(actMeasure>m_DistanceToWall)
        {
            speedBack=0;
        }
        else //if(actMeasure<constant::DISTANCE_TO_WALL+0.1*constant::DISTANCE_TO_WALL)
        {
            //speedBack=LimitValueToBorder((actMeasure-lastMeasure),-25,0);
            if(m_RightSide==true)
            {
                speedBack=-20;
            }
            else
            {
                speedBack=20;
            }
            //speedBack=-20;
        }
    }
    
    lastMeasure = actMeasure;

    if(lastSpeedBack!=speedBack)
    {
        m_drive->HolonomicDrive(0,60,speedBack);
        /*m_drive->SetFrontLeftSpeed(70);
        m_drive->SetFrontRightSpeed(-70);
        m_drive->SetBackSpeed(speedBack);*/
        lastSpeedBack=speedBack;
    }

    switch(m_SensorID)
    {
        case constant::Sensor_IDs::US_R:
            MeasuredDistance = m_sensors->USRightDistance();
            break;

        case constant::Sensor_IDs::US_L:
            MeasuredDistance = m_sensors->USLeftDistance();
            break;

        case constant::Sensor_IDs::IR_L:
            MeasuredDistance = m_sensors->IRLeftDistance()*10;
            break;

        case constant::Sensor_IDs::IR_R:
            MeasuredDistance = m_sensors->IRRightDistance()*10;
            break;
    }

    frc::SmartDashboard::PutNumber("Speed Back Follow Wall",speedBack);
    //frc::SmartDashboard::PutNumber("Y Distance", ((m_drive->GetYDistanceRaw()-startingDistance)));
}

void FollowWall::End(bool interrupted)
{
    m_drive->HolonomicDrive(0,0,0);
}

bool FollowWall::IsFinished()
{
    if(m_SensorID==-1)
    {
        if(((m_drive->GetYDistanceRaw()-startingDistance))>m_distance&&m_distance!=0)
        {   
            frc::SmartDashboard::PutString("End Follow Wall","y Distance");
            return true;
        }
    }
    else
    {
        if(MeasuredDistance<m_distance)
        {
            frc::SmartDashboard::PutString("End Follow Wall","Sensor Distance");
            return true;
        }
    }
    
    if(m_distance==0&&m_sensors->USLeftDistance()<constant::VALUE_WALL&&m_sensors->USRightDistance()<constant::VALUE_WALL&&m_StopAtTwoWalls==true)
    {
        frc::SmartDashboard::PutString("End Follow Wall","Stop at two Walls");
        return true;
    }

    if(actMeasure>constant::VALUE_WALL)
    {
        frc::SmartDashboard::PutString("End Follow Wall","no Wall");
        return true;
    }

    return false;
}