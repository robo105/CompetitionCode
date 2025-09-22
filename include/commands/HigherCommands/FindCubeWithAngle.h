#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Storage.h"
#include "subsystems/Camera.h"
#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"


class FindCubeWithAngle
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, FindCubeWithAngle>
{
    public:

        explicit FindCubeWithAngle(Storage* storage, Camera* camera, DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, double angle, int position);

    private:
        Storage* m_storage;
        Camera* m_camera;
        DriveBase* m_drive;
        Sensors* m_sensor;
        CommandHandler* m_cmd_h;

        double m_angle;
        int m_position;

        //TurnLeftAtCrossing turn_left;
        //TurnRightAtCrossing turn_right;
};