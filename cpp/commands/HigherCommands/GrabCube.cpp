#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"
#include "frc2/command/ConditionalCommand.h"

#include "commands/HigherCommands/GrabCube.h"



#include "commands/Camera/EnableCamera.h"
#include "commands/Drive/PositionBeforeCubeCalculate.h"
#include "commands/Drive/PositionBeforeCube.h"
#include "commands/Storage/SetGreifarm.h"
#include "commands/Storage/InitElevator.h"
#include "commands/Storage/SetElevator.h"
#include "commands/Storage/SetGreifzange.h"
#include "commands/Drive/PositionBeforeLine.h"
#include "commands/StoreCommand.h"
#include "commands/Drive/DriveToLine.h"
#include "commands/Drive/TurnToWall.h"
#include "commands/Drive/DriveToPosition.h"
#include "commands/Drive/TurnToAngleCommand.h"
#include "commands/Drive/SaveAngle.h"

GrabCube::GrabCube(Storage* storage, Camera* camera, DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, int position, bool vonOben, double distanceToCube)
{
    m_camera = camera;
    m_storage = storage;
    m_drive = drive;
    m_cmd_h = cmd_h;
    m_sensor = sensor;
    m_position = position;
    m_vonOben = vonOben;

    m_distanceToCube = distanceToCube;

    Camera mcamera = *m_camera;

    //turn_left = TurnLeftAtCrossing(m_sensor, m_drive);

    AddRequirements({storage,camera, drive, sensor, cmd_h});

    AddCommands(

            //TurnToAngleCommand(m_drive,m_cmd_h,constant::STARTING_ANGLE),

            /*PositionBeforeCubeCalculate(m_drive,m_camera,m_sensor,m_cmd_h,m_vonOben),

            frc2::WaitCommand(0.2_s),

            EnableCamera(m_camera,m_cmd_h,false),

            frc2::WaitCommand(0.2_s),

            PositionBeforeCube(m_drive,m_cmd_h),

            frc2::WaitCommand(0.2_s),*/

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            frc2::WaitCommand(1.0_s),

            //SetElevatorToTop(m_storage,false),

            frc2::WaitCommand(0.2_s),

            //SetElevator(m_storage,-1000),

            frc2::WaitCommand(0.2_s),

            SetGreifzange(m_storage,m_cmd_h,false),

            frc2::WaitCommand(0.2_s),

            //SetGreifarm(m_storage,constant::Greifarm::OBEN),

            //DriveToLine(m_drive,m_sensor,m_cmd_h,0,60,0,false),

            //DriveToPosition(m_drive,m_cmd_h,0,10,0,60),

            frc2::WaitCommand(1.0_s),

            EnableCamera(m_camera,m_cmd_h,false),

            //PositionBeforeLine(m_drive,m_sensor, m_cmd_h),

            //TurnToAngleCommand(m_drive,m_cmd_h,constant::STARTING_ANGLE),

            //TurnToWall(m_drive,m_sensor,m_cmd_h),

            //PositionBeforeLine(m_drive,m_sensor, m_cmd_h),

            frc2::WaitCommand(0.2_s),

            SaveAngle(m_drive,m_cmd_h,false,true),

            StoreCommand(m_storage,m_sensor,m_drive,m_cmd_h,m_position,m_distanceToCube)
        
        );
}

