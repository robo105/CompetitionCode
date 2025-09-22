#include "commands/Drive/DriveUntilWall.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

DriveUntilWall::DriveUntilWall(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, double x, double y, double w, int Sensor_ID, double DistanceToWall)
{
    AddRequirements({drive,sensor,cmd_h});
    m_drive = drive;
    m_sensors = sensor;
    m_cmd_h = cmd_h;

    m_Sensor_ID = Sensor_ID;
    m_Distance = DistanceToWall;
    m_x = x;
    m_y = y;
    m_w = w;
    //m_position = position;
}

//double countDriveToPosition = 0;

void DriveUntilWall::Initialize()
{
    m_cmd_h->AddCommand("DriveUntilWall");

    m_drive->SetOmptimizeLevel(2);

    switch(m_Sensor_ID)
    {
        case constant::Sensor_IDs::US_R:
            Distance = m_sensors->USRightDistance();
            break;

        case constant::Sensor_IDs::US_L:
            Distance = m_sensors->USLeftDistance();
            break;

        case constant::Sensor_IDs::IR_L:
            Distance = m_sensors->IRLeftDistance()*10;
            break;

        case constant::Sensor_IDs::IR_R:
            Distance = m_sensors->IRRightDistance()*10;
            break;
    }

    if(Distance < m_Distance)
    {
        m_drive->HolonomicDrive(-m_x,-m_y,-m_w);
        frc::SmartDashboard::PutString("DriveUntilWall","Distance to small");
    }
    else
    {
        m_drive->HolonomicDrive(m_x,m_y,m_w);
        frc::SmartDashboard::PutString("DriveUntilWall","Distance to big");
    }
}

void DriveUntilWall::Execute()
{
    
    if(Distance < m_Distance-10)
    {
        m_drive->HolonomicDrive(-m_x*0.8,-m_y*0.8,-m_w*0.8);
        frc::SmartDashboard::PutString("DriveUntilWall Execute","Distance to small");
    }
    else if(Distance > m_Distance+10)
    {
        m_drive->HolonomicDrive(m_x*0.8,m_y*0.8,m_w*0.8);
        frc::SmartDashboard::PutString("DriveUntilWall Execute","Distance to big");
    }

    switch(m_Sensor_ID)
    {
        case constant::Sensor_IDs::US_R:
            Distance = m_sensors->USRightDistance();
            break;

        case constant::Sensor_IDs::US_L:
            Distance = m_sensors->USLeftDistance();
            break;

        case constant::Sensor_IDs::IR_L:
            Distance = m_sensors->IRLeftDistance()*10;
            break;

        case constant::Sensor_IDs::IR_R:
            Distance = m_sensors->IRRightDistance()*10;
            break;
        
        case constant::Sensor_IDs::IR_RL:
            Distance = (m_sensors->IRLeftDistance()*10 + m_sensors->IRRightDistance()*10)/2;
            break;
    }
}

void DriveUntilWall::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("DriveUntilWall");
    m_drive->HolonomicDrive(0,0,0);
}

bool DriveUntilWall::IsFinished()
{
    if(Distance -10 < m_Distance && Distance +10 > m_Distance)
    {
        return true;
    }
    return false;
}