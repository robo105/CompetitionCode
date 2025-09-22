#include "commands/Camera/SearchForColor.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

SearchForColor::SearchForColor(DriveBase* drive, Camera* camera, Storage* storage,CommandHandler* cmd_h,double x, double y, double w)
{
    AddRequirements({camera});
    m_camera = camera;
    m_drive = drive;
    m_storage = storage;

    m_x = x;
    m_y = y;
    m_w = w;
}

void SearchForColor::Initialize()
{
    m_camera->SearchforCube();
    global::CountSearchColor=0;
}

void SearchForColor::Execute()
{
    m_camera->SearchforCube();

    m_drive->HolonomicDrive(m_x,m_y,m_w);
}

void SearchForColor::End(bool interrupted)
{
    //m_cmd_h->DeleteCommand("PictureQRCode");
    m_drive->HolonomicDrive(0,0,0);
    m_storage->SetSpeedElevator(0);
}

bool SearchForColor::IsFinished()
{
    if(m_camera->GetDetectedColor()==constant::Camera::BLUE||m_camera->GetDetectedColor()==constant::Camera::RED||m_camera->GetDetectedColor()==constant::Camera::YELLOW)
    {
        frc::SmartDashboard::PutNumber("ColorDetected",m_camera->GetDetectedColor());
        return true;
    }
    else if(global::CountSearchColor > 25)
    {
        global::CountSearchColor=0;

        return true;
    }

    return false;
}