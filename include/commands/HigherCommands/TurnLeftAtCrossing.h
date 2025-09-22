#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Sensors.h"
#include "subsystems/DriveBase.h"
#include "subsystems/CommandHandler.h"

class TurnLeftAtCrossing
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, TurnLeftAtCrossing>
{
    public:

        explicit TurnLeftAtCrossing(Sensors* sensor, DriveBase* drive,CommandHandler* cmd_h);

    private:
        Sensors* m_sensors;
        DriveBase* m_drive;
        CommandHandler* m_cmd_h;
};