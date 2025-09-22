#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Storage.h"
#include "subsystems/Sensors.h"
#include "subsystems/DriveBase.h"
#include "subsystems/Camera.h"
#include "subsystems/CommandHandler.h"

class FindCubeOben
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, FindCubeOben>
{
    public:

        explicit FindCubeOben(Storage* store, Sensors* sensor, DriveBase* drive, Camera* camera, CommandHandler* cmd_h,bool search_right, int position, double distanceToWall = constant::DISTANCE_TO_CUBE);

    private:

        Storage* m_storage;
        Sensors* m_sensors;
        DriveBase* m_drive;
        Camera* m_camera;
        CommandHandler* m_cmd_h;

        int m_position;
        bool m_search_right;
        double m_distanceToWall;
};