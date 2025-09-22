#include "commands//Storage/SetStorageAngle.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

SetStorageAngle::SetStorageAngle(Storage* storage,CommandHandler* cmd_h, double angle)
{
    AddRequirements({storage,m_cmd_h});
    m_storage = storage;
    m_angle = angle;
    m_cmd_h = cmd_h;
    //m_position = position;
}


void SetStorageAngle::Initialize()
{
    m_cmd_h->AddCommand("SetStorageAngle");
    if(m_angle>=constant::Lagerung::MIN_A_LAGERUNG&&m_angle<=constant::Lagerung::MAX_A_LAGERUNG)
    {
        m_storage->SetStorageAngle(m_angle);
    }
}

void SetStorageAngle::Execute()
{
}

void SetStorageAngle::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("SetStorageAngle");
}

bool SetStorageAngle::IsFinished()
{
    return true;
}