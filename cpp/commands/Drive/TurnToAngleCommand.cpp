#include "commands/Drive/TurnToAngleCommand.h"
#include "commands/Drive/TurnToAngle.h"
#include "commands/Drive/InitDrive.h"
#include "commands/Drive/SaveAngle.h"

#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"

TurnToAngleCommand::TurnToAngleCommand(DriveBase* drive,CommandHandler* cmd_h, double angle)
{
    m_angle = angle;
    m_drive = drive;
    m_cmd_h = cmd_h;

    AddCommands
    (
        InitDrive(m_drive,m_cmd_h,1),

        TurnToAngle(m_drive,m_cmd_h,m_angle,35,3),

        frc2::WaitCommand(0.5_s),

        TurnToAngle(m_drive,m_cmd_h,m_angle,10,0.2),

        InitDrive(m_drive,m_cmd_h,2),

        SaveAngle(m_drive,m_cmd_h,false)
    );
}