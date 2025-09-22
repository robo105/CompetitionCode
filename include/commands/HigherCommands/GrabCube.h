#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Storage.h"
#include "subsystems/Camera.h"
#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"


class GrabCube
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, GrabCube>
{
    public:

        explicit GrabCube(Storage* storage, Camera* camera, DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, int position, bool vonOben, double distanceToCube = constant::DISTANCE_TO_CUBE);

    private:
        Storage* m_storage;
        Camera* m_camera;
        DriveBase* m_drive;
        Sensors* m_sensor;
        CommandHandler* m_cmd_h;

        int m_position;
        bool m_vonOben;
        double m_distanceToCube;

        //TurnLeftAtCrossing turn_left;
        //TurnRightAtCrossing turn_right;
};