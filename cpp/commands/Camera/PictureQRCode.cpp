#include "commands/Camera/PictureQRCode.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

PictureQRCode::PictureQRCode(DriveBase* drive, Camera* camera, Storage* storage,CommandHandler* cmd_h)
{
    AddRequirements({camera});
    m_camera = camera;
    m_drive = drive;
    m_storage = storage;
}

void PictureQRCode::Initialize()
{
    //m_cmd_h->AddCommand("PictureQRCode");


    m_camera->TakePictureForQRCode();

    if(m_storage->GetElevatorEncoder()>=constant::Elevator::POSITON_QR_CODE)
    {
        m_storage->SetSpeedElevator(-constant::Elevator::SPEED);
    }
    else if(m_storage->GetElevatorEncoder()<constant::Elevator::POSITON_QR_CODE)
    {
        m_storage->SetSpeedElevator(constant::Elevator::SPEED);
    }
}

void PictureQRCode::Execute()
{
    m_camera->TakePictureForQRCode();
    

    m_storage->SetGreifarm(constant::Greifarm::GERADE);
    
    if(count<25)
    {
        m_drive->HolonomicDrive(0,0,0);
    }
    else
    {
        m_drive->HolonomicDrive(0,-30,0);
    }

    if(m_storage->GetElevatorEncoder()>=constant::Elevator::POSITON_QR_CODE+20) //+20
    {
        m_storage->SetSpeedElevator(-(constant::Elevator::SPEED*0.8));
    }
    else if(m_storage->GetElevatorEncoder()<constant::Elevator::POSITON_QR_CODE-20) //-20
    {
        m_storage->SetSpeedElevator((constant::Elevator::SPEED*0.8));
    }

    count++;
    frc::SmartDashboard::PutNumber("PictureQRCode",count);
}

void PictureQRCode::End(bool interrupted)
{
    //m_cmd_h->DeleteCommand("PictureQRCode");
    m_drive->HolonomicDrive(0,0,0);
    m_storage->SetSpeedElevator(0);
}

bool PictureQRCode::IsFinished()
{
    if(m_camera->GetLastNumberRead()!=-1)
    {
        return true;
    }
    return false;
}