#include "commands/Storage/SetGreifarm.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

SetGreifarm::SetGreifarm(Storage* storage,CommandHandler* cmd_h, double position)
{
    AddRequirements({storage,m_cmd_h});
    m_storage = storage;
    m_position = position;
    m_cmd_h = cmd_h;
}


void SetGreifarm::Initialize()
{
    enable=false;
    endPosition=0;
    helpPosition=0;
    actPosition=0;

    m_cmd_h->AddCommand("SetGreifarm");

    m_storage->SetSpeedElevator(0.0);

    /*if(m_position==constant::Greifarm::GERADE||m_position==constant::Greifarm::UNTEN||m_position==constant::Greifarm::OBEN)
    {*/
        enable=true;
        endPosition=m_position;
        actPosition=m_storage->GetAngleGreifarm();
        //m_storage->SetGreifarm(m_position);
    //}

    /*if(enable==true)
    {
        m_storage->SetGreifarm(m_position);
    }*/

    //frc::SmartDashboard::PutBoolean("Enable Greifarm",enable);
    //frc::SmartDashboard::PutNumber("Position Greifarm",m_position);
}

double countSetGreifarm = 0;

void SetGreifarm::Execute()
{
    actPosition=m_storage->GetAngleGreifarm();

    if(actPosition>endPosition&&enable==true)
    {
        actPosition=m_storage->GetAngleGreifarm();
        m_storage->SetGreifarm(actPosition-2);
        //m_storage->SetStorageAngle(endPosition);
    }
    else if(actPosition<endPosition&&enable==true)
    {
        actPosition=m_storage->GetAngleGreifarm();
        m_storage->SetGreifarm(actPosition+2);
        //m_storage->SetStorageAngle(endPosition);
    }

    countSetGreifarm++;
    //frc::SmartDashboard::PutNumber("countSetGreifarm",countSetGreifarm);
}

void SetGreifarm::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("SetGreifarm");
    m_storage->SetGreifarm(m_position);
}

bool SetGreifarm::IsFinished()
{
    if(m_storage->GetAngleGreifarm() >= endPosition-3 && m_storage->GetAngleGreifarm() <= endPosition+3)
    {
        End(false);
        m_storage->SetSpeedElevator(0.0);
        return true;
    }
    return false;
}