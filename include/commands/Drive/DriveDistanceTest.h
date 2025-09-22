#pragma once

#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class DriveDistanceTest : public frc2::CommandHelper<frc2::SequentialCommandGroup, DriveDistanceTest>
{
    public:
        DriveDistanceTest(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h);
};