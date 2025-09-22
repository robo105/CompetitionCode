#include "commands/Camera/EnableCamera.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

EnableCamera::EnableCamera(Camera* camera,CommandHandler* cmd_h, bool enable)
{
    AddRequirements({camera, cmd_h});
    m_camera = camera;
    m_cmd_h = cmd_h;
    m_enable = enable;
}

void EnableCamera::Initialize()
{
    m_camera->EnableCamera(m_enable);
    //m_cmd_h->AddCommand("EnableCamera");
}

void EnableCamera::End(bool interrupted)
{
    //m_cmd_h->DeleteCommand("EnableCamera");
}

bool EnableCamera::IsFinished()
{
    return true;
}