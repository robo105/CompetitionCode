#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Storage.h"
#include "subsystems/Sensors.h"
#include "subsystems/DriveBase.h"
#include "subsystems/CommandHandler.h"

class StoreCommand
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, StoreCommand>
{
    public:

        explicit StoreCommand(Storage* store, Sensors* sensor, DriveBase* drive,CommandHandler* cmd_h, int position, double distanceToCube = constant::DISTANCE_TO_CUBE);

    private:

        Storage* m_storage;
        Sensors* m_sensors;
        DriveBase* m_drive;
        CommandHandler* m_cmd_h;

        int m_position;
        double m_distanceToCube;
};