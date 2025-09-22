#include "commands/Camera/TakePictureQRCode_Line.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

TakePictureQRCode_Line::TakePictureQRCode_Line(Camera* camera,CommandHandler* cmd_h, bool direction)
{
    AddRequirements({camera});
    m_camera = camera;
    m_direction = direction;
}


void TakePictureQRCode_Line::Initialize()
{
    m_camera->TakePictureForQRCode();
    //m_cmd_h->AddCommand("TakePictureQRCode_Line");
}

void TakePictureQRCode_Line::Execute()
{
    
}

void TakePictureQRCode_Line::End(bool interrupted)
{
    //m_cmd_h->DeleteCommand("TakePictureQRCode_Line");
}

bool TakePictureQRCode_Line::IsFinished()
{
    return true;
}