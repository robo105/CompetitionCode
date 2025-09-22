#include "commands/Drive/FollowLine.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

FollowLine::FollowLine(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h)
{
    AddRequirements({drive,sensor});
    m_drive = drive;
    m_sensors = sensor;
    m_cmd_h = cmd_h;
}

void FollowLine::Initialize()
{
    //m_cmd_h->AddCommand("FollowLine");
    m_drive->HolonomicDrive(0,60,0);
    m_drive->SetOmptimizeLevel(1);

    //m_drive->ResetEncoders();

    for(int i=0;i<4;i++)
    {
      lastMeasure[i]=m_sensors->GetCobra(i);
    }
}

/*double LimitValueToBorderLine(double value, double Bottom, double Top)
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

double countLine = 0;

void FollowLine::Execute()
{
    for(int i=0;i<4;i++)
    {
      actMeasure[i]=m_sensors->GetCobra(i);
    }

    if(actMeasure[1]<lastMeasure[1]||actMeasure[0]<lastMeasure[0])
    {
        if(actMeasure[1]>constant::VALUE_LINE)
        {
            speedBack=0;
        }
        else //if(actMeasure>constant::DISTANCE_TO_WALL+0.1*constant::DISTANCE_TO_WALL)
        {
            //speedBack=LimitValueToBorder((actMeasure-lastMeasure),0,25);
            speedBack=25; // 15
        }
        /*else
        {
            speedBack=10;
        }*/
        
    }
    else if(actMeasure[2]<lastMeasure[2]||actMeasure[3]<lastMeasure[3])
    {
        if(actMeasure[2]>constant::VALUE_LINE)
        {
            speedBack=0;
        }
        else //if(actMeasure<constant::DISTANCE_TO_WALL+0.1*constant::DISTANCE_TO_WALL)
        {
            //speedBack=LimitValueToBorder((actMeasure-lastMeasure),-25,0);
            speedBack=-25; // -15
        }
        /*else
        {
            speedBack=-10;
        }*/
    }
    
    for(int i=0;i<4;i++)
    {
      lastMeasure[i]=actMeasure[i];
    }

    if(lastSpeedBack!=speedBack)
    {
        m_drive->HolonomicDrive(0,60,speedBack);
        //lastSpeedBack=speedBack;
    }

    lastSpeedBack=speedBack;

    countLine++;
    /*frc::SmartDashboard::PutNumber("countLine", countLine);
    frc::SmartDashboard::PutNumber("SpeedBack",speedBack);
    frc::SmartDashboard::PutNumber("Cobra Value 0", m_sensors->GetCobra(0));
    frc::SmartDashboard::PutNumber("Cobra Value 1", m_sensors->GetCobra(1));
    frc::SmartDashboard::PutNumber("Cobra Value 2", m_sensors->GetCobra(2));
    frc::SmartDashboard::PutNumber("Cobra Value 3", m_sensors->GetCobra(3));*/
}

void FollowLine::End(bool interrupted)
{
    //m_cmd_h->DeleteCommand("FollowLine");
    m_drive->HolonomicDrive(0,0,0);
}

bool FollowLine::IsFinished()
{
    if(m_sensors->GetCobra(1)<constant::VALUE_LINE&&m_sensors->GetCobra(2)<constant::VALUE_LINE&&m_sensors->GetCobra(3)<constant::VALUE_LINE&&m_sensors->GetCobra(4)<constant::VALUE_LINE)
    {
        frc::SmartDashboard::PutString("FollowLine stopped","End of Line reached");
        return true;
    }

    return false;
}