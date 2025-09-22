#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"
#include "frc2/command/ConditionalCommand.h"
#include "commands/HigherCommands/FindCubeWithAngle.h"

#include "commands/Drive/TurnToAngleCommand.h"
#include "commands/Drive/SaveAngle.h"
#include "commands/Drive/DriveUntilWall.h"
#include "commands/Drive/FollowWall.h"
#include "commands/Drive/InitDrive.h"
#include "commands/Drive/DriveToPosition.h"
#include "commands/Drive/TurnToWall.h"

#include "commands/FindCubeOben.h"


FindCubeWithAngle::FindCubeWithAngle(Storage* storage, Camera* camera, DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, double angle, int position)
{
    m_camera = camera;
    m_storage = storage;
    m_drive = drive;
    m_cmd_h = cmd_h;
    m_sensor = sensor;

    m_angle=angle;
    m_position = position;

    Sensors msensors = *m_sensor;

    AddRequirements({storage,camera, drive, sensor, cmd_h});

    AddCommands(

            FollowWall(m_drive,m_sensor,m_cmd_h,true,230,constant::Sensor_IDs::IR_R,false,150), //250,0

            InitDrive(m_drive,m_cmd_h,2),

            TurnToAngleCommand(m_drive,m_cmd_h,m_angle),

            DriveToPosition(m_drive,m_cmd_h,0,150,0,35),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,60,0,constant::Sensor_IDs::IR_R,260),

            TurnToAngleCommand(m_drive,m_cmd_h,m_angle),

            frc2::ConditionalCommand(
                    InitDrive(m_drive,m_cmd_h,2),
                    TurnToWall(m_drive,m_sensor,m_cmd_h),
                    [&msensors] { return msensors.IRDistanceSimilar(); }
            ),

            SaveAngle(m_drive,m_cmd_h,false),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R,260),

            InitDrive(m_drive,m_cmd_h,2),

            FindCubeOben(m_storage,m_sensor,m_drive,m_camera,m_cmd_h,false,m_position)
        
        );
}

