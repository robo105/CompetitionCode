#include "commands/Storage/ReleaseCube.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

ReleaseCube::ReleaseCube(Storage* storage,CommandHandler* cmd_h)
{
    AddRequirements({storage,m_cmd_h});
    m_storage = storage;
    m_cmd_h = cmd_h;
}

void ReleaseCube::Initialize()
{
    m_cmd_h->AddCommand("ReleaseCube");
    /*if(m_storage->GetElevatorEncoder()>m_position)
    {
        SetElevatorSpeed=-constant::Elevator::SPEED;
    }else if(m_storage->GetElevatorEncoder()<m_position)
    {
        SetElevatorSpeed=constant::Elevator::SPEED;
    }
    */
    m_storage->SetSpeedElevator(constant::Elevator::SPEED);
}

void ReleaseCube::Execute()
{
    /*countSetElevator++;
    frc::SmartDashboard::PutNumber("countSetElevator",countSetElevator);
    //frc::SmartDashboard::PutBoolean("Elevator Position OK",m_storage->GetElevatorEncoder() >= m_position-10 && m_storage->GetElevatorEncoder() <= m_position+10);
    //frc::SmartDashboard::PutNumber("Elevator Position",m_storage->GetElevatorEncoder());

    if(m_storage->GetElevatorEncoder()>m_position)
    {
        SetElevatorSpeed=-constant::Elevator::SPEED;
    }else if(m_storage->GetElevatorEncoder()<m_position)
    {
        SetElevatorSpeed=constant::Elevator::SPEED;
    }

    m_storage->SetSpeedElevator(SetElevatorSpeed);*/

    m_storage->SetSpeedElevator(constant::Elevator::SPEED);
}

void ReleaseCube::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("ReleaseCube");
    m_storage->SetSpeedElevator(0.0);
}

bool ReleaseCube::IsFinished()
{
    /*if(m_storage->GetElevatorEncoder() >= m_position-10 && m_storage->GetElevatorEncoder() <= m_position+10)
    {
        //End(false);
        m_storage->SetSpeedElevator(0.0);
        return true;
    }*/

    if(m_storage->GetElevatorEncoder() >= constant::Elevator::POSITION_GRAB_CUBE)
    {
        return true;
    }

    /*if(m_storage->GetElevatorEncoder() < m_position)
    {
        return true;
    }*/
    
    return false;
}