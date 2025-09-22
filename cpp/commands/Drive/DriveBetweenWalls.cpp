#include "commands/Drive/DriveBetweenWalls.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

DriveBetweenWalls::DriveBetweenWalls(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h)
{
    AddRequirements({drive,sensor,cmd_h});
    m_drive = drive;
    m_sensors = sensor;
    m_cmd_h = cmd_h;
}


void DriveBetweenWalls::Initialize()
{
    //m_drive->SetHandleIMU();
    m_drive->SetOmptimizeLevel(1);
    m_drive->HolonomicDrive(0,0,0);
    //m_cmd_h->AddCommand("DriveBetweenWalls");

    //m_drive->ResetEncoders();

    /*lastMeasure_r = (int)(m_sensors->USRightDistance()*10);
    lastMeasure_l = (int)(m_sensors->USLeftDistance()*10);

    lastMeasure_r/=10.0;
    lastMeasure_l/=10.0;*/

    lastMeasure_l=0;
    lastMeasure_r=0;

    countLastMeasure = 0;
}

//BUG: Follow Wall geht nur rechts

/*double LimitValueToBorder(double value, double Bottom, double Top)
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
}*/


void DriveBetweenWalls::Execute()
{
    actMeasure_r = (int)(m_sensors->USRightDistance()*10);
    actMeasure_l = (int)(m_sensors->USLeftDistance()*10);

    actMeasure_r/=10.0;
    actMeasure_l/=10.0;

    if(actMeasure_l>actMeasure_r)
    {
        if(actMeasure_l<lastMeasure_l)
        {
            speedBack=0;
        }
        else
        {
            speedBack=-30;
        }
    }
    else if(actMeasure_r>actMeasure_l)
    {
        if(actMeasure_r<lastMeasure_r)
        {
            speedBack=0;
        }
        else
        {
            speedBack=30;
        }
    }
    
    if(countLastMeasure>5)
    {
        lastMeasure_r = actMeasure_r;
        lastMeasure_l = actMeasure_l;

        countLastMeasure=0;
    }
    else
    {
        countLastMeasure++;
    }
    
    if(lastSpeedBack!=speedBack)
    {
        m_drive->HolonomicDrive(0,70,speedBack);
        lastSpeedBack=speedBack;
    }

    /*frc::SmartDashboard::PutNumber("US Right Distance Walls", actMeasure_r);
    frc::SmartDashboard::PutNumber("US Right Last Distance Walls", lastMeasure_r);
    frc::SmartDashboard::PutNumber("US Left Distance Walls", actMeasure_l);
    frc::SmartDashboard::PutNumber("US Left Last Distance Walls", lastMeasure_l);
    frc::SmartDashboard::PutNumber("SpeedBack Walls",speedBack);*/
}

void DriveBetweenWalls::End(bool interrupted)
{
    m_drive->HolonomicDrive(0,0,0);
    //m_cmd_h->DeleteCommand("DriveBetweenWalls");
}

bool DriveBetweenWalls::IsFinished()
{
    if(m_sensors->USLeftDistance()>constant::VALUE_WALL||m_sensors->USRightDistance()>constant::VALUE_WALL)
    {
        return true;
    }

    return false;
}