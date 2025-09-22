#include "commands/Camera/ChangeColorDetectionRed.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

ChangeColorDetectionRed::ChangeColorDetectionRed(Camera* camera,CommandHandler* cmd_h, int number)
{
    AddRequirements({camera, cmd_h});
    m_camera = camera;
    m_cmd_h = cmd_h;
    m_number = number;
}

void ChangeColorDetectionRed::Initialize()
{
    global::SelectRed = m_number;
}

void ChangeColorDetectionRed::End(bool interrupted)
{
    
}

bool ChangeColorDetectionRed::IsFinished()
{
    return true;
}