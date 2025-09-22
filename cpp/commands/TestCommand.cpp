#include "commands/TestCommand.h"

#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"


#include "commands/FindCube.h"
#include "commands/Drive/FollowWall.h"
#include "commands/Drive/TurnToAngle.h"
#include "commands/Drive/InitDrive.h"
#include "commands/Storage/InitElevator.h"
#include "commands/Drive/DriveToPosition.h"
#include "commands/Drive/DriveUntilWall.h"

TestCommand::TestCommand(Storage* store, Sensors* sensor, DriveBase* drive, Camera* camera,CommandHandler* cmd_h)
{
    m_storage = store;
    m_drive = drive;
    m_sensors = sensor;
    m_camera = camera;
    m_cmd_h = cmd_h;

    AddRequirements({store,sensor,drive,camera,m_cmd_h});


    AddCommands(

            /*InitDrive(m_drive,2),

            SetElevatorToTop(m_storage,m_cmd_h,false),*/
            FindCube(m_storage,m_sensors,m_drive,m_camera,m_cmd_h,false,0),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,-60,0,constant::Sensor_IDs::IR_L),

            TurnToAngle(m_drive,m_cmd_h,80),

            FollowWall(m_drive,m_sensors,m_cmd_h,false,1200,-1),

            TurnToAngle(m_drive,m_cmd_h,constant::STARTING_ANGLE),

            FindCube(m_storage,m_sensors,m_drive,m_camera,m_cmd_h,false,1)
        
        );
}