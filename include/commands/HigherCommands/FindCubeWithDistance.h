#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Storage.h"
#include "subsystems/Camera.h"
#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"


class FindCubeWithDistance
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, FindCubeWithDistance>
{
    public:

        explicit FindCubeWithDistance(Storage* storage, Camera* camera, DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, int position, double distanceToWall = constant::DISTANCE_TO_WALL);

    private:
        Storage* m_storage;
        Camera* m_camera;
        DriveBase* m_drive;
        Sensors* m_sensor;
        CommandHandler* m_cmd_h;

        double m_distanceToWall;
        int m_position;

        //TurnLeftAtCrossing turn_left;
        //TurnRightAtCrossing turn_right;
};