#include "commands/FindCubeOben.h"

#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"
#include "frc2/command/ConditionalCommand.h"

#include "commands/Camera/EnableCamera.h"
#include "commands/Drive/InitDrive.h"
#include "commands/Storage/SetGreifarm.h"
#include "commands/Storage/InitElevator.h"
#include "commands/Storage/SetStorePosition.h"
#include "commands/Drive/DriveUntilCube.h"
#include "commands/Storage/SetElevator.h"
#include "commands/Drive/TurnToAngle.h"
#include "commands/Drive/PositionBeforeCubeCalculate.h"
#include "commands/Drive/PositionBeforeCube.h"
#include "commands/Drive/PositionBeforeLine.h"
#include "commands/StoreCommand.h"
#include "commands/Drive/DriveToLine.h"
#include "commands/Storage/SetGreifzange.h"

#include "commands/HigherCommands/GrabCube.h"
#include "commands/Storage/SetElevatorToTop.h"
#include "commands/Drive/TurnToAngleCommand.h"

FindCubeOben::FindCubeOben(Storage* store, Sensors* sensor, DriveBase* drive, Camera* camera,CommandHandler* cmd_h, bool search_right, int position, double distanceToWall)
{
    m_storage = store;
    m_drive = drive;
    m_sensors = sensor;
    m_camera = camera;
    m_cmd_h = cmd_h;

    m_search_right = search_right;
    m_position = position;
    m_distanceToWall = distanceToWall;

    Camera mcamera = *m_camera;

    AddRequirements({store,sensor,drive, camera,m_cmd_h});


    AddCommands(

            /*EnableCamera(m_camera,false),

            frc2::WaitCommand(0.2_s),

            InitDrive(m_drive,2),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,constant::Greifarm::GERADE),

            frc2::WaitCommand(0.2_s),

            SetElevatorToTop(m_storage,false),

            frc2::WaitCommand(0.2_s),

            SetStorePosition(m_storage,0),*/

            TurnToAngleCommand(m_drive,m_cmd_h,constant::STARTING_ANGLE),

            frc2::WaitCommand(0.2_s),

            //SetElevator(m_storage,-400),
            SetElevatorToTop(m_storage,m_cmd_h,true),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::MINIMUM), //149

            //frc2::WaitCommand(2.0_s),

            //SetElevator(m_storage,-400),

            frc2::WaitCommand(0.2_s),

            EnableCamera(m_camera,m_cmd_h,false),

            frc2::WaitCommand(0.2_s),

            DriveUntilCube(m_drive,m_sensors,m_camera,m_storage,m_cmd_h,m_search_right),

            frc2::WaitCommand(0.2_s),

            InitDrive(m_drive,m_cmd_h,2),

            frc2::WaitCommand(0.5_s),

            EnableCamera(m_camera,m_cmd_h,false),

            frc2::WaitCommand(0.5_s),

            TurnToAngleCommand(m_drive,m_cmd_h,constant::STARTING_ANGLE),

            //EnableCamera(m_camera,true),

            InitDrive(m_drive,m_cmd_h,2),

            frc2::WaitCommand(0.2_s),

            //GrabCube(m_storage,m_camera,m_drive,m_sensors,m_position,true)

            frc2::ConditionalCommand(
                GrabCube(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,m_position,true,m_distanceToWall), // wenn richtige Farbe erkannt wurde soll der Würfel aufgehoben werden
                InitDrive(m_drive,m_cmd_h,2), // wennn nicht dann nichts tun
                [&mcamera] { return mcamera.IsDetectedColorSearched(); }
            )
        
        );
}