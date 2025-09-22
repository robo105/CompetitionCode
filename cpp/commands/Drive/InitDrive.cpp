#include "commands/Drive/InitDrive.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

InitDrive::InitDrive(DriveBase* drive,CommandHandler* cmd_h, int optimize_level)
{
    AddRequirements({drive});
    m_drive = drive;
    m_cmd_h = cmd_h;
    m_optimize = optimize_level;
}


void InitDrive::Initialize()
{
    m_cmd_h->AddCommand("InitDrive");
    m_drive->SetOmptimizeLevel(m_optimize);
    //m_drive->SetHandleIMU();
    m_drive->HolonomicDrive(0,0,0);
}

void InitDrive::Execute()
{    
}

void InitDrive::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("InitDrive");
}

bool InitDrive::IsFinished()
{
    return true;
}