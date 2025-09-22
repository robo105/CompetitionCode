#include "commands/Storage/SetElevator.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

SetElevator::SetElevator(Storage* storage,CommandHandler* cmd_h, double position)
{
    AddRequirements({storage,m_cmd_h});
    m_storage = storage;
    m_cmd_h = cmd_h;
    m_position = position;
}

double SetElevatorSpeed = 0;

void SetElevator::Initialize()
{
    //m_cmd_h->AddCommand("SetElevator");
    enable=false;

    /*if(m_position==constant::ELEVATOR_UNTEN||m_position==constant::ELEVATOR_OBEN||m_position==constant::ELEVATOR_OBEN_W)
    {
        enable=true;
    }*/
    if(m_storage->GetElevatorEncoder()>m_position||m_storage->GetElevatorEncoder()<m_position)
    {
        if(m_storage->GetElevatorEncoder()>m_position)
        {
            SetElevatorSpeed=-constant::Elevator::SPEED;
        }else if(m_storage->GetElevatorEncoder()<m_position)
        {
            SetElevatorSpeed=constant::Elevator::SPEED;
        }   
        m_storage->SetSpeedElevator(SetElevatorSpeed);
    }
    
}

double countSetElevator = 0;

void SetElevator::Execute()
{
    countSetElevator++;
    frc::SmartDashboard::PutNumber("countSetElevator",countSetElevator);
    //frc::SmartDashboard::PutBoolean("Elevator Position OK",m_storage->GetElevatorEncoder() >= m_position-10 && m_storage->GetElevatorEncoder() <= m_position+10);
    //frc::SmartDashboard::PutNumber("Elevator Position",m_storage->GetElevatorEncoder());

    if(m_storage->GetElevatorEncoder()>m_position+10)
    {
        SetElevatorSpeed=-constant::Elevator::SPEED;
    }else if(m_storage->GetElevatorEncoder()<m_position-10)
    {
        SetElevatorSpeed=constant::Elevator::SPEED;
    }

    m_storage->SetSpeedElevator(SetElevatorSpeed);

}

void SetElevator::End(bool interrupted)
{
    //m_cmd_h->DeleteCommand("SetElevator");
    m_storage->SetSpeedElevator(0.0);
}

bool SetElevator::IsFinished()
{
    /*if(m_storage->GetElevatorEncoder() >= m_position-10 && m_storage->GetElevatorEncoder() <= m_position+10)
    {
        //End(false);
        m_storage->SetSpeedElevator(0.0);
        return true;
    }*/

    if(SetElevatorSpeed>0)
    {
        if(m_storage->GetElevatorEncoder() >= m_position)
        {
            return true;
        }
    }
    else if(SetElevatorSpeed<0)
    {
        if(m_storage->GetElevatorEncoder() <= m_position)
        {
            return true;
        }
    }

    /*if(m_storage->GetElevatorEncoder() < m_position)
    {
        return true;
    }*/
    
    return false;
}