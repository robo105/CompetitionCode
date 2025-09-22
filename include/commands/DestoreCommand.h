#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Storage.h"
#include "subsystems/Sensors.h"
#include "subsystems/DriveBase.h"
#include "subsystems/CommandHandler.h"

class DestoreCommand
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, DestoreCommand>
{
    public:

        explicit DestoreCommand(Storage* store, Sensors* sensor, DriveBase* drive,CommandHandler* cmd_h, int position);

    private:

        Storage* m_storage;
        Sensors* m_sensors;
        DriveBase* m_drive;
        CommandHandler* m_cmd_h;

        int m_position;
};