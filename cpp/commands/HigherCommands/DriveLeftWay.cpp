#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"
#include "frc2/command/ConditionalCommand.h"

#include "commands/HigherCommands/DriveLeftWay.h"

#include "commands/Drive/DriveToLine.h"
#include "commands/Drive/DriveUntilWall.h"
#include "commands/Drive/TurnToAngleCommand.h"
#include "commands/Camera/PictureQRCodeSideways.h"
#include "commands/Drive/DriveToPosition.h"

#include "commands/Drive/FollowLine.h"
#include "commands/Drive/FollowWall.h"

#include "commands/Storage/SetGreifarm.h"
#include "commands/Camera/EnableCamera.h"


DriveLeftWay::DriveLeftWay(Storage* storage, Camera* camera, DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h)
{
    m_camera = camera;
    m_storage = storage;
    m_drive = drive;
    m_cmd_h = cmd_h;
    m_sensor = sensor;

    AddRequirements({storage,camera, drive, sensor, cmd_h});

    AddCommands(

                //DriveToLine(m_drive,m_sensor,m_cmd_h,0,70,0),

                TurnToAngleCommand(m_drive,m_cmd_h,45),

                DriveToLine(m_drive,m_sensor,m_cmd_h,60,0,0),

                FollowLine(m_drive,m_sensor,m_cmd_h),

                //DriveToPosition(m_drive,m_cmd_h,0,200,0),

                TurnToAngleCommand(m_drive,m_cmd_h,90),

                DriveUntilWall(m_drive,m_sensor,m_cmd_h,-70,0,0,constant::Sensor_IDs::US_L),

                DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R,150),

                TurnToAngleCommand(m_drive,m_cmd_h,-90),

                DriveUntilWall(m_drive,m_sensor,m_cmd_h,-60,0,0,constant::Sensor_IDs::IR_R,400),

                DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,-60,0,constant::Sensor_IDs::IR_R,320),

                EnableCamera(m_camera,m_cmd_h,false),

                PictureQRCodeSideways(m_drive,m_sensor,m_camera,m_storage,m_cmd_h,-60,0,0,false),

                EnableCamera(m_camera,m_cmd_h,false),

                SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

                DriveUntilWall(m_drive,m_sensor,m_cmd_h,-60,0,0,constant::Sensor_IDs::US_L,150),

                DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R,300),

                TurnToAngleCommand(m_drive,m_cmd_h,-45),

                DriveUntilWall(m_drive,m_sensor,m_cmd_h,-70,0,0,constant::Sensor_IDs::US_L,150),

                FollowWall(m_drive,m_sensor,m_cmd_h,false,0,constant::Sensor_IDs::NONE,false,150),

                DriveToLine(m_drive,m_sensor,m_cmd_h,0,60,0),

                TurnToAngleCommand(m_drive,m_cmd_h,-135),

                DriveToLine(m_drive,m_sensor,m_cmd_h,60,0,0),

                FollowLine(m_drive,m_sensor,m_cmd_h),

                //DriveToPosition(m_drive,m_cmd_h,0,100,0),

                //FollowLine(m_drive,m_sensor,m_cmd_h)
                TurnToAngleCommand(m_drive,m_cmd_h,-90),

                DriveToLine(m_drive,m_sensor,m_cmd_h,60,0,0)

        );
}

