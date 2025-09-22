#pragma once

#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveBase.h"
#include "subsystems/CommandHandler.h"

class TurnToAngleCommand : public frc2::CommandHelper<frc2::SequentialCommandGroup, TurnToAngleCommand>
{
    public:
        TurnToAngleCommand(DriveBase* drive,CommandHandler* cmd_h, double angle);

    private:
        double m_angle;
        DriveBase* m_drive;
        CommandHandler* m_cmd_h;
};