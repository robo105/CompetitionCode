#include "commands/Drive/DriveToLine.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

DriveToLine::DriveToLine(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, double x, double y, double w, bool WatchAllTime)
{
    AddRequirements({drive,sensor});
    m_drive = drive;
    m_sensors = sensor;
    m_cmd_h = cmd_h;

    m_x = x;
    m_y = y;
    m_w = w;
    m_WatchAllTime = WatchAllTime;
    //m_position = position;
}

//double countDriveToPosition = 0;

void DriveToLine::Initialize()
{
    m_cmd_h->AddCommand("DriveToLine");

    global::SearchForLine=true;

    if(m_y>0)
    {
        global::SearchForCube=true;
    }
    m_drive->HolonomicDrive(m_x,m_y,m_w);

    
}

void DriveToLine::Execute()
{
    /*if(m_sensors->GetIRFRontDistance()<constant::DISTANCE_TO_CUBE&&constant::DISTANCE_TO_CUBE-m_sensors->GetIRFRontDistance()<5)
    {
        m_drive->HolonomicDrive(0,-25,0);
    }
    else */
    /*if(m_sensors->GetIRFRontDistance()<constant::DISTANCE_TO_CUBE)
    {
        m_drive->HolonomicDrive(0,-50,0);
        countDriveToCube++;
        frc::SmartDashboard::PutNumber("Count Drive To Cube",countDriveToCube);
    }
    else
    {*/
        //m_drive->HolonomicDrive(0,50,0);
    //}
    m_drive->HolonomicDrive(m_x,m_y,m_w);
    frc::SmartDashboard::PutNumber("Distance Line 0",m_sensors->GetCobra(0));
    frc::SmartDashboard::PutNumber("Distance Line 1",m_sensors->GetCobra(1));
    frc::SmartDashboard::PutNumber("Distance Line 2",m_sensors->GetCobra(2));
    frc::SmartDashboard::PutNumber("Distance Line 3",m_sensors->GetCobra(3));
}

void DriveToLine::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("DriveToLine");
    m_drive->HolonomicDrive(0,0,0);
    global::SearchForLine=false;
}

bool DriveToLine::IsFinished()
{
    if((m_sensors->GetCobra(0) > constant::VALUE_LINE || m_sensors->GetCobra(1) > constant::VALUE_LINE ||m_sensors->GetCobra(2) > constant::VALUE_LINE ||m_sensors->GetCobra(3) > constant::VALUE_LINE) && m_WatchAllTime == true)
    {
        End(false);
        return true;
    }
    else if((m_sensors->GetCobra(0) > constant::VALUE_LINE || m_sensors->GetCobra(1) > constant::VALUE_LINE || m_sensors->GetCobra(2) > constant::VALUE_LINE || m_sensors->GetCobra(3) > constant::VALUE_LINE) && m_WatchAllTime == false && m_sensors->IRRightDistance() < 35)
    {
        End(false);
        return true;
    }

    return false;
}