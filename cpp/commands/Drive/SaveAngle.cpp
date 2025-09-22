#include "commands/Drive/SaveAngle.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

SaveAngle::SaveAngle(DriveBase* drive,CommandHandler* cmd_h, bool reset, bool overwrite)
{
    AddRequirements({drive});
    m_drive = drive;
    m_reset = reset;
    m_cmd_h = cmd_h;
    m_overwrite = overwrite;
}

void SaveAngle::Initialize()
{
    m_cmd_h->AddCommand("SaveAngle");
    if(m_reset==false)
    {
        if(m_overwrite==false)
        {
            global::savedAngle = global::lastAngle;
        }
        else
        {
            global::savedAngle = m_drive->GetYaw();
        }
    }
    else
    {
        m_drive->ResetIMU();
        m_drive->SetHandleIMU();
        global::savedAngle = m_drive->GetStartingAngle();
    }
}

void SaveAngle::Execute()
{   

}

void SaveAngle::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("SaveAngle");
}

bool SaveAngle::IsFinished()
{
    return true;
}