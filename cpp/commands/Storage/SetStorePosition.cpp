#include "commands//Storage/SetStorePosition.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

SetStorePosition::SetStorePosition(Storage* storage,CommandHandler* cmd_h, int position)
{
    AddRequirements({storage,m_cmd_h});
    m_storage = storage;
    m_position = position;
    m_cmd_h = cmd_h;
}


void SetStorePosition::Initialize()
{
    enable=false;
    endPosition=0;
    helpPosition=0;
    actPosition=0;
    m_cmd_h->AddCommand("SetStorePosition");

    actPosition=m_storage->GetAngleLagerung();

    if(m_position==constant::Lagerung::HANDLE_STORAGE)
    {
        m_position=global::StoragePlace;
        global::StoragePlace++;
    }
    /*if(m_position>=0&&m_position<=constant::Lagerung::MAX_LAGERUNG)
    {
        //helpPosition=60*m_position;
        helpPosition=constant::Lagerung::ANGLE[m_position];
        if(helpPosition>=constant::Lagerung::MIN_A_LAGERUNG&&helpPosition<=constant::Lagerung::MAX_A_LAGERUNG)
        {
            endPosition=helpPosition;
            actPosition=m_storage->GetAngleLagerung();
            enable=true;
            //frc::SmartDashboard::PutNumber("actPosition",actPosition);
            //frc::SmartDashboard::PutNumber("endPosition",endPosition); 
        }
    }*/

    if(m_position>=0&&m_position<=constant::Lagerung::MAX_LAGERUNG)
    {
        enable==true;
        endPosition=constant::Lagerung::ANGLE[m_position];
    }
}

double CountSetStorePosition = 0;

void SetStorePosition::Execute()
{
    actPosition=m_storage->GetAngleLagerung();
    //frc::SmartDashboard::PutNumber("actPosition_new",actPosition);
    //frc::SmartDashboard::PutBoolean("enabled",enable);
    /*if(actPosition >= endPosition-5 && actPosition <= endPosition+5)
    {
        m_storage->SetStorageAngle(endPosition);
    }
    else*/ 
    if(actPosition>endPosition&&enable==true)
    {
        actPosition=m_storage->GetAngleLagerung();
        m_storage->SetStorageAngle(actPosition-3);
        //m_storage->SetStorageAngle(endPosition);
    }
    else if(actPosition<endPosition&&enable==true)
    {
        actPosition=m_storage->GetAngleLagerung();
        m_storage->SetStorageAngle(actPosition+3);
        //m_storage->SetStorageAngle(endPosition);
    }

    CountSetStorePosition++;
    //frc::SmartDashboard::PutNumber("CountSetStorePosition",CountSetStorePosition);
}

void SetStorePosition::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("SetStorePosition");
    m_storage->SetStoragePosition(m_position);
}

bool SetStorePosition::IsFinished()
{
    if(m_storage->GetAngleLagerung() >= endPosition-2 && m_storage->GetAngleLagerung() <= endPosition+2)
    {
        return true;
    }

    if(enable==false)
    {
        return true;
    }
    return false;
}