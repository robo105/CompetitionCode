#include "commands/Camera/PictureQRCodeSideways.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

PictureQRCodeSideways::PictureQRCodeSideways(DriveBase* drive,Sensors* sensor, Camera* camera, Storage* storage,CommandHandler* cmd_h,double x, double y, double w, bool QRCodeProoved)
{
    AddRequirements({camera});
    m_camera = camera;
    m_drive = drive;
    m_storage = storage;
    m_sensor = sensor;

    m_x = x;
    m_y = y;
    m_w = w;
    m_QRCodeProoved = QRCodeProoved;
}

void PictureQRCodeSideways::Initialize()
{
    //m_cmd_h->AddCommand("PictureQRCode");

    m_camera->TakePictureForQRCode();
    m_drive->SetOmptimizeLevel(2);

    global::CameraEnabled=true;

    if(m_storage->GetElevatorEncoder()>constant::Elevator::POSITON_QR_CODE)
    {
        m_storage->SetSpeedElevator(-constant::Elevator::SPEED);
    }
    else if(m_storage->GetElevatorEncoder()<constant::Elevator::POSITON_QR_CODE)
    {
        m_storage->SetSpeedElevator(constant::Elevator::SPEED);
    }

    direction1 = true;

    m_drive->ResetEncoders();
}

void PictureQRCodeSideways::Execute()
{
    m_camera->TakePictureForQRCode();

    if(m_sensor->USRightDistance() < Length && m_x > 0)
    {
        direction1 != direction1;
        //m_drive->ResetEncoders();
        m_x = -m_x;
        CountAttempts++;
    }
    else if(m_sensor->USLeftDistance() < Length && m_x < 0)
    {
        direction1 != direction1;
        //m_drive->ResetEncoders();
        m_x = -m_x;
        CountAttempts++;
    }

    /*if(direction1 == true)
    {
        m_drive->HolonomicDrive(m_x,m_y,m_w);
    }
    else
    {
        m_drive->HolonomicDrive(-m_x,-m_y,-m_w);
    }*/

    m_drive->HolonomicDrive(m_x,m_y,m_w);
    
    m_storage->SetGreifarm(constant::Greifarm::GERADE);

    if(m_storage->GetElevatorEncoder()>=constant::Elevator::POSITON_QR_CODE) //+20
    {
        m_storage->SetSpeedElevator(-(constant::Elevator::SPEED*1));
    }
    else if(m_storage->GetElevatorEncoder()<constant::Elevator::POSITON_QR_CODE) //-20
    {
        m_storage->SetSpeedElevator((constant::Elevator::SPEED*1));
    }

    /*count++;
    frc::SmartDashboard::PutNumber("PictureQRCode",count);*/
}

void PictureQRCodeSideways::End(bool interrupted)
{
    //m_cmd_h->DeleteCommand("PictureQRCode");
    m_drive->HolonomicDrive(0,0,0);
    m_storage->SetSpeedElevator(0);

    global::CameraEnabled=false;
}

bool PictureQRCodeSideways::IsFinished()
{
    if(m_camera->GetLastNumberRead()!=-1)
    {
        return true;
    }
    else if(CountAttempts>2 && m_QRCodeProoved == false)
    {
        fstream file;
        file.open("/home/pi/Desktop/QR_Codes.txt", ios_base::out | ios_base::app);
        file << "-1\n";
        file.close();
        return true;
    }

    return false;
}