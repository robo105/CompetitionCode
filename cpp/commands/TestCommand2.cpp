#include "commands/TestCommand2.h"

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

#include "commands/Drive/DriveToLine.h"
#include "commands/Drive/PositionBeforeLine.h"
#include "commands/Storage/SetGreifarm.h"
#include "commands/Camera/EnableCamera.h"
#include "commands/Storage/SetElevator.h"
#include "commands/Camera/TakePictureQRCode_Line.h"
#include "commands/FindCube.h"
#include "commands/Drive/SaveAngle.h"
#include "commands/FindCubeOben.h"

#include "commands/Camera/PictureQRCode.h"
#include "commands/Storage/SetElevatorToTop.h"

#include "commands/Drive/TurnToAngleCommand.h"
#include "commands/Drive/TurnToWall.h"
#include "frc2/command/ConditionalCommand.h"

#include "commands/HigherCommands/FindCubeWithAngle.h"
#include "commands/HigherCommands/FindCubeWithDistance.h"

TestCommand2::TestCommand2(Storage* store, Sensors* sensor, DriveBase* drive, Camera* camera,CommandHandler* cmd_h)
{
    m_storage = store;
    m_drive = drive;
    m_sensors = sensor;
    m_camera = camera;
    m_cmd_h = cmd_h;

    Sensors msensors = *m_sensors;

    AddRequirements({store,sensor,drive,camera,m_cmd_h});


    AddCommands(
            SaveAngle(m_drive,m_cmd_h,true),

            frc2::WaitCommand(1.0_s),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            SetElevator(m_storage,m_cmd_h,constant::Elevator::POSITON_QR_CODE),

            frc2::WaitCommand(1.0_s),

            DriveToLine(m_drive,m_sensors,m_cmd_h,0,80,0,false),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h),

            DriveToPosition(m_drive,m_cmd_h,-300,0,0,50),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::GERADE),

            SetElevator(m_storage,m_cmd_h,constant::Elevator::POSITON_QR_CODE),

            frc2::WaitCommand(0.2_s),
            
            EnableCamera(m_camera,m_cmd_h,true),

            frc2::WaitCommand(0.2_s),
            
            //CheckforLine(m_camera,true),
            PictureQRCode(m_drive,m_camera, m_storage,m_cmd_h),

            frc2::WaitCommand(0.2_s),

            EnableCamera(m_camera,m_cmd_h,false),

            frc2::WaitCommand(0.2_s),

            TurnToAngleCommand(m_drive,m_cmd_h,-90),

            SaveAngle(m_drive,m_cmd_h,false),

            InitDrive(m_drive,m_cmd_h,2),

            EnableCamera(m_camera,m_cmd_h,false),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,80,0,0,constant::Sensor_IDs::US_R,150),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            InitDrive(m_drive,m_cmd_h,1),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            //DriveToPosition(m_drive,1100,0,0),

            // 380
            FindCubeWithAngle(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,-45,constant::Lagerung::HANDLE_STORAGE),  // Würfel 1

            EnableCamera(m_camera,m_cmd_h,false),

            SetGreifarm(m_storage,m_cmd_h, constant::Greifarm::OBEN),

            SaveAngle(m_drive,m_cmd_h,false),

            DriveToPosition(m_drive,m_cmd_h,0,200,0),

            InitDrive(m_drive,m_cmd_h,2),

            TurnToAngleCommand(m_drive,m_cmd_h,180),

            SaveAngle(m_drive,m_cmd_h,false),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,60,0,0,constant::Sensor_IDs::US_R,150),

            FindCubeWithDistance(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,constant::Lagerung::HANDLE_STORAGE,330),

            //FindCubeWithAngle(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,constant::STARTING_ANGLE,constant::Lagerung::HANDLE_STORAGE)

            //FindCube(m_storage,m_sensors,m_drive,m_camera,m_cmd_h,true,-1,constant::DISTANCE_TO_CUBE+6) // Würfel 2

            EnableCamera(m_camera,m_cmd_h,false),

            EnableCamera(m_camera,m_cmd_h,false),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            TurnToAngleCommand(m_drive,m_cmd_h,0),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            InitDrive(m_drive,m_cmd_h,1),

            FollowWall(m_drive,m_sensors,m_cmd_h,false,250,constant::Sensor_IDs::IR_L,false),

            TurnToAngleCommand(m_drive,m_cmd_h,45),

            //InitDrive(m_drive,1),

            FollowWall(m_drive,m_sensors,m_cmd_h,false,250,constant::Sensor_IDs::IR_L,false),

            TurnToAngleCommand(m_drive,m_cmd_h,90),

            SaveAngle(m_drive,m_cmd_h,false),

            FollowWall(m_drive,m_sensors,m_cmd_h,false,300,-1,false),

            //TurnToAngleCommand(m_drive,m_cmd_h,92),

            FollowWall(m_drive,m_sensors,m_cmd_h,false,0,-1,true),

            DriveToPosition(m_drive,m_cmd_h,100,0,0),

            InitDrive(m_drive,m_cmd_h,2),

            //SaveAngle(m_drive,m_cmd_h,false),

            FindCube(m_storage,m_sensors,m_drive,m_camera,m_cmd_h,false,1), // Würfel 3

            EnableCamera(m_camera,m_cmd_h,false),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            TurnToAngleCommand(m_drive,m_cmd_h,-90),

            InitDrive(m_drive,m_cmd_h,1),

            FollowWall(m_drive,m_sensors,m_cmd_h,false,0,-1),

            DriveToPosition(m_drive,m_cmd_h,200,0,0),

            InitDrive(m_drive,m_cmd_h,2),

            TurnToAngleCommand(m_drive,m_cmd_h,-135),

            DriveToPosition(m_drive,m_cmd_h,200,0,0),

            InitDrive(m_drive,m_cmd_h,1),

            FollowWall(m_drive,m_sensors,m_cmd_h,false,0,-1),

            DriveToPosition(m_drive,m_cmd_h,200,0,0),

            InitDrive(m_drive,m_cmd_h,2),

            TurnToAngleCommand(m_drive,m_cmd_h,180),

            SaveAngle(m_drive,m_cmd_h,false),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,80,0,constant::Sensor_IDs::IR_R,150),

            TurnToAngleCommand(m_drive,m_cmd_h,90),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,80,0,0,constant::Sensor_IDs::US_R,150),

            //DriveToPosition(m_drive,m_cmd_h,200,0,0)

            FollowWall(m_drive,m_sensors,m_cmd_h,true,610,constant::Sensor_IDs::US_L,true,130),

            //DriveUntilWall(m_drive,m_sensors,0,50,0,constant::Sensor_IDs::IR_F,750),
            FollowWall(m_drive,m_sensors,m_cmd_h,true,250,constant::Sensor_IDs::IR_L,false,130),

            TurnToAngleCommand(m_drive,m_cmd_h,-90),

            SaveAngle(m_drive,m_cmd_h,false),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,80,0,0,constant::Sensor_IDs::US_R,150),

            FindCubeWithAngle(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,-45,constant::Lagerung::HANDLE_STORAGE),

            EnableCamera(m_camera,m_cmd_h,false),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            TurnToAngleCommand(m_drive,m_cmd_h,-90),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,-80,0,0,constant::Sensor_IDs::US_L,150),

            DriveToLine(m_drive,m_sensors,m_cmd_h,0,80,0),

            DriveToPosition(m_drive,m_cmd_h,200,0,0),

            TurnToAngleCommand(m_drive,m_cmd_h,0)


            /*FollowWall(m_drive,m_sensors,m_cmd_h,true,230,constant::Sensor_IDs::IR_R,false,150),

            InitDrive(m_drive,m_cmd_h,2),

            TurnToAngleCommand(m_drive,m_cmd_h,-45),

            DriveToPosition(m_drive,m_cmd_h,0,120,0,40),

            TurnToWall(m_drive,m_sensors,m_cmd_h),

            SaveAngle(m_drive,m_cmd_h,false),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,50,0,constant::Sensor_IDs::IR_L),

            SaveAngle(m_drive,m_cmd_h,false),

            InitDrive(m_drive,m_cmd_h,2),

            FindCubeOben(m_storage,m_sensors,m_drive,m_camera,m_cmd_h,false,1)*/  // Würfel 4

            //FindCube(m_storage,m_sensors,m_drive,m_camera,m_cmd_h,true,1)

            //FollowWall()

            /*InitDrive(m_drive,2),

            SetElevatorToTop(m_storage,m_cmd_h,false),*/
            
        
        );
}