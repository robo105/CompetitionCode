#include "commands//Storage/SetGreifzange.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

SetGreifzange::SetGreifzange(Storage* storage,CommandHandler* cmd_h, bool greifen)
{
    AddRequirements({storage,m_cmd_h});
    m_storage = storage;
    m_cmd_h = cmd_h;
    m_greifen = greifen;
}


void SetGreifzange::Initialize()
{
    m_cmd_h->AddCommand("SetGreifzange");
    m_storage->SetGreifzange(m_greifen);
}

double countSetGreifzange = 0;

void SetGreifzange::Execute()
{
    //m_storage->SetGreifzange(m_greifen);
    countSetGreifzange++;
    //frc::SmartDashboard::PutNumber("countSetGreifzange", countSetGreifzange);
}

void SetGreifzange::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("SetGreifzange");
}

bool SetGreifzange::IsFinished()
{
    switch(m_greifen)
    {
        case true:
            if(m_storage->GetAngleGreifzange() >= constant::Greifzange::ZU-3&& m_storage->GetAngleGreifzange() <= constant::Greifzange::ZU+3)
            {
                return true;
            }
            break;

        case false:
            if(m_storage->GetAngleGreifzange() >= constant::Greifzange::OFFEN-3 && m_storage->GetAngleGreifzange() <= constant::Greifzange::OFFEN+3)
            {
                return true;
            }
            break;
    }
    
    return false;
}