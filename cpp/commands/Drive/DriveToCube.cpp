#include "commands/Drive/DriveToCube.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

DriveToCube::DriveToCube(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, double distanceToCube)
{
    AddRequirements({drive,sensor});
    m_drive = drive;
    m_sensors = sensor;
    m_cmd_h = cmd_h;
    m_distanceToCube = distanceToCube;
    //m_position = position;
}

double countDriveToPosition = 0;

void DriveToCube::Initialize()
{
    m_cmd_h->AddCommand("DriveToCube");
    m_drive->SetOmptimizeLevel(2);

    if((m_sensors->IRRightDistance()*10)<m_distanceToCube)
    {
        m_drive->HolonomicDrive(0,-70,0);
    }
    else if((m_sensors->IRRightDistance()*10)>m_distanceToCube)
    {
        m_drive->HolonomicDrive(0,70,0);
    }
}

void DriveToCube::Execute()
{
    if((m_sensors->IRRightDistance()*10)<m_distanceToCube)
    {
        m_drive->HolonomicDrive(0,-60,0);
    }
    else if((m_sensors->IRRightDistance()*10)>m_distanceToCube)
    {
        m_drive->HolonomicDrive(0,60,0);
    }
}

void DriveToCube::End(bool interrupted)
{
    m_drive->HolonomicDrive(0,0,0);
    m_cmd_h->DeleteCommand("DriveToCube");
    global::SearchForCube=false;
}

bool DriveToCube::IsFinished()
{
    if(m_sensors->IRRightDistance()*10 >= m_distanceToCube-0.4 && m_sensors->IRRightDistance()*10 <= m_distanceToCube+0.4)
    {
        End(false);
        return true;
    }
    return false;
}