#include "commands/Storage/SetElevatorToTop.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

SetElevatorToTop::SetElevatorToTop(Storage* storage,CommandHandler* cmd_h, bool top)
{
    AddRequirements({storage,m_cmd_h});
    m_storage = storage;
    m_cmd_h = cmd_h;
    m_top = top;
}


void SetElevatorToTop::Initialize()
{
    m_cmd_h->AddCommand("SetElevatorToTop");
    if(m_top==true)
    {
        m_storage->SetSpeedElevator(-constant::Elevator::SPEED);
    }
    else if(m_top==false)
    {
        m_storage->SetSpeedElevator(constant::Elevator::SPEED);
    }
}

double countElevator = 0;

void SetElevatorToTop::Execute()
{
    if(m_top==true)
    {
        m_storage->SetSpeedElevator(-constant::Elevator::SPEED);
    }
    else if(m_top==false)
    {
        m_storage->SetSpeedElevator(constant::Elevator::SPEED);
    }
    countElevator++;
    //frc::SmartDashboard::PutNumber("countSetElevatorToTop",countElevator);
}

void SetElevatorToTop::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("SetElevatorToTop");
    m_storage->SetSpeedElevator(0.0);
}

bool SetElevatorToTop::IsFinished()
{
    if((m_top==true&&m_storage->GetLimitSwitch(true)==0.0)||(m_top==false&&m_storage->GetLimitSwitch(false)==0.0))
    {
        End(false);
        return true;
    }
    
    return false;
}