#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"
#include "frc2/command/ConditionalCommand.h"

#include "commands/HigherCommands/TakeBlueCube.h"

#include "commands/Drive/DriveToLine.h"
#include "commands/Drive/DriveUntilWall.h"
#include "commands/Drive/TurnToAngleCommand.h"
#include "commands/Camera/PictureQRCodeSideways.h"
#include "commands/Drive/DriveToPosition.h"

#include "commands/Drive/FollowLine.h"
#include "commands/Drive/FollowWall.h"

#include "commands/Storage/SetGreifarm.h"
#include "commands/Camera/EnableCamera.h"

#include "commands/Drive/InitDrive.h"
#include "commands/Drive/PositionBeforeLine.h"
#include "commands/Camera/SearchForColor.h"
#include "commands/HigherCommands/GrabCube.h"

#include "commands/Storage/SetElevatorToTop.h"


TakeBlueCube::TakeBlueCube(Storage* storage, Camera* camera, DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h)
{
    m_camera = camera;
    m_storage = storage;
    m_drive = drive;
    m_cmd_h = cmd_h;
    m_sensor = sensor;

    Camera mcamera = *m_camera;

    AddRequirements({storage,camera, drive, sensor, cmd_h});

    AddCommands(

            DriveToPosition(m_drive,m_cmd_h,-200,0,0),

            TurnToAngleCommand(m_drive,m_cmd_h,-90),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,70,0,constant::Sensor_IDs::US_L,400),

            DriveToPosition(m_drive,m_cmd_h,0,200,0),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,-60,0,0,constant::Sensor_IDs::US_L,150),

            FollowWall(m_drive,m_sensor,m_cmd_h,false,500,constant::Sensor_IDs::IR_R,false,700),

            DriveToLine(m_drive,m_sensor,m_cmd_h,-60,0,0),

            PositionBeforeLine(m_drive,m_sensor,m_cmd_h),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,0,60,0,constant::Sensor_IDs::IR_R,560),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            /*SearchForColor(m_drive,m_camera,m_storage,m_cmd_h,0,0,0),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::MINIMUM),*/
            
            frc2::ConditionalCommand(                                                                   // Würfel 2 Nr. 1
                GrabCube(m_storage,m_camera,m_drive,m_sensor,m_cmd_h,constant::Lagerung::HANDLE_STORAGE,true,560), // wenn richtige Farbe erkannt wurde soll der Würfel aufgehoben werden
                InitDrive(m_drive,m_cmd_h,2), // wennn nicht dann nichts tun
                [&mcamera] { return mcamera.IsDetectedColorSearched(); }
            ),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            TurnToAngleCommand(m_drive,m_cmd_h,90),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,60,0,0,constant::Sensor_IDs::US_R,150),

            FollowWall(m_drive,m_sensor,m_cmd_h,true,150,constant::Sensor_IDs::US_R,false,150),

            TurnToAngleCommand(m_drive,m_cmd_h,180),

            DriveUntilWall(m_drive,m_sensor,m_cmd_h,-70,0,0,constant::Sensor_IDs::US_L),

            DriveToLine(m_drive,m_sensor,m_cmd_h,0,60,0)
                
        );
}

