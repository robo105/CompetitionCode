#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"

#include "commands/HigherCommands/TurnLeftAtCrossing.h"
#include "commands/Drive/DriveToPosition.h"
#include "commands/Drive/DriveToLine.h"

TurnLeftAtCrossing::TurnLeftAtCrossing(Sensors* sensor, DriveBase* drive,CommandHandler* cmd_h)
{

    m_drive = drive;
    m_sensors = sensor;
    m_cmd_h = cmd_h;

    AddRequirements({sensor,drive,cmd_h});


    AddCommands(

            frc2::WaitCommand(1.0_s),

            DriveToPosition(m_drive, m_cmd_h,0,0,-16),

            frc2::WaitCommand(0.2_s),

            DriveToLine(m_drive,m_sensors,m_cmd_h,50,0,0),

            frc2::WaitCommand(1.0_s)
        
        );
}

