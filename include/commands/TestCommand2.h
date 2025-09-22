#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Storage.h"
#include "subsystems/Sensors.h"
#include "subsystems/DriveBase.h"
#include "subsystems/Camera.h"
#include "subsystems/CommandHandler.h"

class TestCommand2
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, TestCommand2>
{
    public:

        explicit TestCommand2(Storage* store, Sensors* sensor, DriveBase* drive, Camera* camera,CommandHandler* cmd_h);

    private:

        Storage* m_storage;
        Sensors* m_sensors;
        DriveBase* m_drive;
        Camera* m_camera;
        CommandHandler* m_cmd_h;
};