#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"
#include "frc2/command/ConditionalCommand.h"

#include "commands/HigherCommands/DriveRightWay.h"

#include "commands/Drive/DriveToLine.h"
#include "commands/Drive/DriveUntilWall.h"
#include "commands/Drive/TurnToAngleCommand.h"
#include "commands/Camera/PictureQRCodeSideways.h"
#include "commands/Drive/DriveToPosition.h"

#include "commands/Drive/FollowLine.h"
#include "commands/Camera/EnableCamera.h"


DriveRightWay::DriveRightWay(Storage* storage, Camera* camera, DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h)
{
    m_camera = camera;
    m_storage = storage;
    m_drive = drive;
    m_cmd_h = cmd_h;
    m_sensor = sensor;

    AddRequirements({storage,camera, drive, sensor, cmd_h});

    AddCommands(

            //DriveToLine(m_drive,m_sensor,m_cmd_h,0,70,0),

            //DriveUntilWall(m_drive,m_sensor,m_cmd_h,70,0,0,constant::Sensor_IDs::US_R),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R,300),

            TurnToAngleCommand(m_drive,m_cmd_h,90),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R,300),

            TurnToAngleCommand(m_drive,m_cmd_h,-90),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,60,0,0,constant::Sensor_IDs::IR_R,400),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,-60,0,constant::Sensor_IDs::IR_R,320),

            EnableCamera(m_camera,m_cmd_h,false),

            PictureQRCodeSideways(m_drive,m_sensor, m_camera,m_storage,m_cmd_h,60,0,0,false),

            EnableCamera(m_camera,m_cmd_h,false),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,70,0,0,constant::Sensor_IDs::US_R,150),

            //TurnToAngleCommand(m_drive,m_cmd_h,-90),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R),

            TurnToAngleCommand(m_drive,m_cmd_h,-135),

            //DriveToPosition(m_drive,m_cmd_h,-300,0,0),

            //DriveToPosition(m_drive,m_cmd_h,0,300,0),

            DriveToLine(m_drive,m_sensor,m_cmd_h,-60,0,0),

            FollowLine(m_drive,m_sensor,m_cmd_h),

            //DriveToPosition(m_drive,m_cmd_h,0,100,0),

                //FollowLine(m_drive,m_sensor,m_cmd_h)
            TurnToAngleCommand(m_drive,m_cmd_h,-90),

            DriveToLine(m_drive,m_sensor,m_cmd_h,60,0,0)
        );
}

