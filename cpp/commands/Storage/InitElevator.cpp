#include "commands/Storage/InitElevator.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

InitElevator::InitElevator(Storage* storage,CommandHandler* cmd_h)
{
    AddRequirements({storage,m_cmd_h});
    m_storage = storage;
    m_cmd_h = cmd_h;
    //m_position = position;
}


void InitElevator::Initialize()
{
    //frc::SmartDashboard::PutNumber("InitElevator",10);
    m_cmd_h->AddCommand("InitElevator");
    m_storage->SetSpeedElevator(-constant::Elevator::SPEED);

    //global::EnableInitElevator=true;
}

double countInitElevator = 0;

void InitElevator::Execute()
{
    m_storage->SetSpeedElevator(-constant::Elevator::SPEED);
    countInitElevator++;
    //frc::SmartDashboard::PutNumber("CountInitElevator",countInitElevator);
}

void InitElevator::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("InitElevator");
    m_storage->SetSpeedElevator(0.0);
    //m_storage->ElevatorPosition=0;
}

bool InitElevator::IsFinished()
{
    //frc::SmartDashboard::PutNumber("Limit Switch Init Elevator",m_storage->GetLimitSwitch(false));
    if(m_storage->GetLimitSwitch(true)==0.0)
    {
        End(false);
        return true;
    }

    return false;
}