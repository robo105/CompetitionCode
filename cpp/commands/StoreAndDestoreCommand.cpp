#include "commands/StoreAndDestoreCommand.h"
#include "commands/StoreCommand.h"
#include "commands/Storage/SetStorePosition.h"
#include "commands/Storage/SetGreifzange.h"
#include "commands/Storage/SetGreifarm.h"
#include "commands/Storage/InitElevator.h"
#include "commands/Storage/SetElevatorToTop.h"
#include "commands/Storage/SetStorageAngle.h"
#include "commands/Storage/SetElevator.h"

#include "commands/DestoreCommand.h"

#include "commands/Camera/TakePictureQRCode_Line.h"

#include "commands/Drive/DriveToPosition.h"
#include "commands/Drive/InitDrive.h"
#include "commands/Drive/FollowWall.h"
#include "commands/Drive/FollowLine.h"
#include "commands/Drive/DriveWithPID.h"
#include "commands/Drive/PositionBeforeCubeCalculate.h"
#include "commands/Drive/PositionBeforeCube.h"
#include "commands/Camera/EnableCamera.h"
#include "commands/Drive/PositionBeforeLine.h"
#include "commands/Drive/DriveToLine.h"
#include "commands/Drive/DriveUntilCube.h"

#include "commands/HigherCommands/TurnLeftAtCrossing.h"
#include "commands/HigherCommands/TurnRightAtCrossing.h"
#include "commands/HigherCommands/ReadQRCodeInFront.h"

#include "commands/Camera/TakePictureQRCode_Line.h"

#include "commands/Drive/DriveBetweenWalls.h"

#include <frc2/command/ParallelRaceGroup.h>

#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"
#include "frc2/command/ConditionalCommand.h"

#include "commands/HigherCommands/TurnRightAtCrossing.h"
#include "commands/HigherCommands/TurnLeftAtCrossing.h"

#include "commands/Drive/TurnToAngle.h"
#include "commands/Drive/TurnToAngleCommand.h"
#include "commands/FindCube.h"

#include "commands/TestCommand.h"
#include "commands/TestCommand2.h"

#include "commands/Drive/SaveAngle.h"

#include "commands/Drive/DriveUntilWall.h"
#include "commands/Drive/TurnToWall.h"

#include "commands/NavigationTask.h"

#include "commands/Camera/PictureQRCodeSideways.h"
#include "commands/Camera/SearchForColor.h"

#include "commands/StorageTask.h"
#include "commands/Camera/PictureQRCode.h"

bool test()
{ 
    return true;
}

frc2::WaitCommand wait(10.0_s);
frc2::WaitCommand wait3(1.0_s);
frc2::Command* p_cmd;
frc2::Command* p_cmd2;

StoreAndDestoreCommand::StoreAndDestoreCommand(Storage* store, Sensors* sensor, DriveBase* drive, Camera* camera, CommandHandler* cmd_h)
{
    m_storage = store;
    m_drive = drive;
    m_sensors = sensor;
    m_camera = camera;
    m_cmd_h = cmd_h;

    Camera mcamera = *m_camera;
    frc2::WaitCommand wait2(10.0_s);
    p_cmd = &wait;  
    p_cmd2 = &wait3;  

    AddRequirements({store,sensor,drive, camera,m_cmd_h});


    AddCommands(

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::GERADE),

            SetGreifzange(m_storage,m_cmd_h,false),

            InitElevator(m_storage,m_cmd_h),

            SetElevator(m_storage,m_cmd_h,2500),

            InitDrive(m_drive,m_cmd_h,2),

            SetStorageAngle(m_storage,m_cmd_h,0),

            SetStorePosition(m_storage,m_cmd_h,0),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN)

            //PictureQRCode(m_drive,m_camera,m_storage,m_cmd_h)

            //StorageTask(m_storage,m_sensors,m_drive,m_camera,m_cmd_h)

            //NavigationTask(m_storage,m_sensors,m_drive,m_camera,m_cmd_h)

            /*InitElevator(m_storage,m_cmd_h),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::MINIMUM),

            FollowLine(m_drive,m_sensors,m_cmd_h),

            SearchForColor(m_drive,m_camera,m_storage,m_cmd_h,0,60,0)*/

            //PictureQRCodeSideways(m_drive,m_sensors,m_camera,m_storage,m_cmd_h,-60,0,0,false)

            /*EnableCamera(m_camera,m_cmd_h,false),

            frc2::WaitCommand(0.2_s),

            InitDrive(m_drive,m_cmd_h,2),

            //FollowWall(m_drive,m_sensors,false,0,-1)
            InitElevator(m_storage,m_cmd_h),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::GERADE),

            SetGreifzange(m_storage,m_cmd_h,false),

            frc2::WaitCommand(0.2_s),

            SetElevatorToTop(m_storage,m_cmd_h,false),

            frc2::WaitCommand(0.2_s),

            SetStorePosition(m_storage,m_cmd_h,0),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            SetElevatorToTop(m_storage,m_cmd_h,false),*/
            
            /*SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            SetElevatorToTop(m_storage,m_cmd_h,true),*/

            /*DriveToLine(m_drive,m_sensors,m_cmd_h,0,50,0),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h)*/

            //TestCommand2(m_storage,m_sensors,m_drive,m_camera,m_cmd_h)

            //FollowWall(m_drive,m_sensors,m_cmd_h,true,400,constant::Sensor_IDs::IR_L,true,150)

            //SaveAngle(m_drive,true),

            //DriveUntilWall(m_drive,m_sensors,m_cmd_h,80,0,0,constant::Sensor_IDs::US_R)
            
            //TurnToAngleCommand(m_drive,180)*/

            /*EnableCamera(m_camera,false),

            FollowWall(m_drive,m_sensors,true,0),

            DriveBetweenWalls(m_drive,m_sensors),

            FollowWall(m_drive,m_sensors,true,0)*/

            //TestCommand(m_storage,m_sensors,m_drive,m_camera)

            /*FindCube(m_storage,m_sensors,m_drive,m_camera,false,0),

            frc2::WaitCommand(1.0_s),

            DriveToPosition(m_drive,-300,0,0),

            frc2::WaitCommand(1.0_s),

            FindCube(m_storage,m_sensors,m_drive,m_camera,false,1)*/
            
            //TurnToWall(m_drive,m_sensors,m_cmd_h)

            /*InitDrive(m_drive,1),

            TurnToAngle(m_drive,0,35),

            frc2::WaitCommand(1.0_s),

            TurnToAngle(m_drive,constant::STARTING_ANGLE)*/

            //CheckforCrossing(m_drive, m_sensors,m_camera,m_storage,&TurnLeftAtCrossing(m_sensors,m_drive)),

            //DriveBetweenWalls(m_drive,m_sensors),

            //InitDrive(m_drive,2),

            //DriveToPosition(m_drive,0,1000,0)

            //CheckforCrossing(m_drive,m_sensors,m_camera,m_storage,TurnLeftAtCrossing(m_sensors,m_drive),TurnRightAtCrossing(m_sensors,m_drive)),

            //frc2::WaitCommand(1.0_s)

            /*SetGreifarm(m_storage,constant::Greifarm::GERADE),

            //CheckDirectionCrossing(m_drive, true),

            frc2::ConditionalCommand(DriveToPosition(m_drive,50,0,0),DriveToPosition(m_drive,50,0,0),test),

            frc2::WaitCommand(1.0_s),

            SetElevatorToTop(m_storage,m_cmd_h,false),*/

            //EnableCamera(m_camera,true),

            //frc2::

            //TODO: Code für Würfelaufheben 
            /*EnableCamera(m_camera,false),

            frc2::WaitCommand(0.2_s),

            InitDrive(m_drive,2),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,constant::Greifarm::GERADE),

            frc2::WaitCommand(0.2_s),

            SetElevatorToTop(m_storage,m_cmd_h,false),,

            frc2::WaitCommand(0.2_s),

            SetStorePosition(m_storage,0),

            frc2::WaitCommand(0.2_s),

            SetElevator(m_storage,-400),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,148), //149

            frc2::WaitCommand(0.2_s),

            EnableCamera(m_camera,true),

            frc2::WaitCommand(0.2_s),

            DriveUntilCube(m_drive,m_camera,false),

            frc2::WaitCommand(0.2_s),

            InitDrive(m_drive,1),

            TurnToAngle(m_drive,constant::STARTING_ANGLE,20),

            InitDrive(m_drive,2),

            frc2::WaitCommand(0.2_s),

            //PositionBeforeCube(m_drive,m_camera),
            PositionBeforeCubeCalculate(m_drive,m_camera,m_sensors),

            frc2::WaitCommand(0.2_s),

            EnableCamera(m_camera,false),

            frc2::WaitCommand(0.2_s),

            //DriveToPosition(m_drive,m_drive->Position_x,0,0)
            PositionBeforeCube(m_drive),

            //frc2::WaitCommand(0.2_s),
            //PositionBeforeCubeCalculate(m_drive,m_camera,m_sensors),
            //frc2::WaitCommand(0.2_s),
            //EnableCamera(m_camera,false),
            //frc2::WaitCommand(0.2_s),
            //DriveToPosition(m_drive,m_drive->Position_x,0,0)
            //PositionBeforeCube(m_drive),

            //InitDrive(m_drive,true),
            //StoreCommand(m_storage,m_sensors,m_drive),

            //frc2::WaitCommand(1.0_s),

            //PositionBeforeCube(m_drive,m_camera),

            //InitDrive(m_drive,true),
            //StoreCommand(m_storage,m_sensors,m_drive),

            frc2::WaitCommand(0.2_s),

            //EnableCamera(m_camera,false),

            SetGreifarm(m_storage,constant::Greifarm::GERADE),

            frc2::WaitCommand(1.0_s),

            SetElevatorToTop(m_storage,m_cmd_h,false),,

            frc2::WaitCommand(0.2_s),

            SetElevator(m_storage,-1000),

            frc2::WaitCommand(0.2_s),

            SetGreifzange(m_storage,false),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,constant::Greifarm::OBEN),

            //PositionBeforeCube(m_drive,m_camera),
            //PositionBeforeLine(m_drive,m_sensors),
            DriveToLine(m_drive,m_sensors,0,50,0),

            frc2::WaitCommand(1.0_s),

            PositionBeforeLine(m_drive,m_sensors),

            //FollowWall(m_drive, m_sensors, true, 5000),
            //FollowLine(m_drive,m_sensors),
            //InitDrive(m_drive, true),

            frc2::WaitCommand(0.2_s),

            StoreCommand(m_storage,m_sensors,m_drive,0)*/
            //TODO: Ende Code für Würfelaufheben

            /*EnableCamera(m_camera,true),

            InitDrive(m_drive,2),

            frc2::WaitCommand(1.0_s),

            PositionBeforeCubeCalculate(m_drive,m_camera,m_sensors),

            frc2::WaitCommand(1.0_s),

            EnableCamera(m_camera,false),

            frc2::WaitCommand(1.0_s),

            //DriveToPosition(m_drive,m_drive->Position_x,0,0)
            PositionBeforeCube(m_drive)*/
            //DriveToPosition(m_drive,0,m_drive->GetPositionX(),0)

            //DriveToPosition(m_drive, 0,200,0)

            //frc2::WaitCommand(3.0_s),

            // TODO: Follow Line und abbiegen
            
            /*EnableCamera(m_camera,false),

            InitDrive(m_drive,2),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,constant::Greifarm::GERADE),

            frc2::WaitCommand(0.2_s),

            SetElevatorToTop(m_storage,m_cmd_h,false),,

            frc2::WaitCommand(0.2_s),

            DriveToLine(m_drive,m_sensors,0,50,0),

            frc2::WaitCommand(0.2_s),

            PositionBeforeLine(m_drive,m_sensors),

            //InitDrive(m_drive,2),

            frc2::WaitCommand(1.0_s),

            //frc2::WaitCommand(1.0_s),

            SetElevator(m_storage,constant::Elevator::POSITON_QR_CODE),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,constant::Greifarm::GERADE),

            frc2::WaitCommand(0.2_s),
            
            EnableCamera(m_camera,true),

            frc2::WaitCommand(0.2_s),
            
            TakePictureForQRCode_Line(m_camera,true),

            frc2::WaitCommand(0.2_s),

            EnableCamera(m_camera,false),

            frc2::WaitCommand(0.2_s),

            SetElevatorToTop(m_storage,true),

            frc2::WaitCommand(0.2_s),

            SetGreifarm(m_storage,constant::Greifarm::MINIMUM),

            frc2::WaitCommand(0.2_s),

            //SetGreifarm(m_storage,constant::Greifarm::OBEN),

            

            EnableCamera(m_camera,true),

            frc2::WaitCommand(0.2_s),

            TakePictureForQRCode_Line(m_camera,true),

            frc2::WaitCommand(0.2_s),

            EnableCamera(m_camera,false),

            frc2::WaitCommand(0.2_s),

            FollowLine(m_drive,m_sensors),

            frc2::WaitCommand(0.2_s),

            //DriveToPosition(m_drive,0,0,16),  //16
            //frc2::ConditionalCommand(DriveToPosition(m_drive,0,0,16),DriveToPosition(m_drive,0,0,-16),[&mcamera] { return mcamera.drive_Right(); }),
            frc2::ConditionalCommand(

                frc2::ConditionalCommand(
                    ReadQRCodeInFront(m_storage,m_camera,m_drive,m_sensors), // beide richtig
                    TurnRightAtCrossing(m_sensors,m_drive), // nur rechts
                    [&mcamera] { return mcamera.drive_Left(); }
                ),
                
                frc2::ConditionalCommand(
                    TurnLeftAtCrossing(m_sensors,m_drive),    // nur links
                    DriveToPosition(m_drive,0,0,0),   // keiner richtig
                    [&mcamera] { return mcamera.drive_Left(); }
                ),

                [&mcamera] { return mcamera.drive_Right(); }
            ),

            frc2::WaitCommand(1.0_s)*/
            // TODO: Ende Kreuzung abbiegen

            //DriveToPosition(m_drive,0,-100,0),

            //frc2::WaitCommand(1.0_s),

            //DriveToPosition(m_drive,100,0,0),

            //frc2::WaitCommand(1.0_s),

            //DriveToPosition(m_drive,0,100,0)

            //frc2::WaitCommand(1.0_s)

            /*DriveToLine(m_drive,m_sensors,-50,0,0),

            //DriveToPosition(m_drive,0,50,0),

            frc2::WaitCommand(0.2_s),

            FollowLine(m_drive,m_sensors)*/




            /*DriveToPosition(m_drive,0,20,0)

            frc2::WaitCommand(0.2_s),

            TakePictureForQRCode_Line(m_sensors,false),

            frc2::WaitCommand(0.2_s),

            DriveToPosition(m_drive,0,40,0),

            frc2::WaitCommand(0.2_s),

            TakePictureForQRCode_Line(m_sensors,true),

            frc2::WaitCommand(0.2_s),

            DriveToPosition(m_drive,0,-20,0),

            frc2::WaitCommand(0.2_s),

            CheckforCrossing(m_drive,m_sensors,m_camera),

            frc2::WaitCommand(0.2_s),

            DriveToPosition(m_drive,0,0,m_sensors->Line_Position_w),

            frc2::WaitCommand(0.2_s)*/

            //DestoreCommand(m_storage,m_sensors,m_drive)

            //PositionBeforeCube(m_drive, m_camera),

            //frc2::WaitCommand(2.0_s),

            //DriveWithPID(drive, sensor, 0.0, 200.0, 0.0, 0.0, -1, -1)

            /*InitDrive(m_drive),

            frc2::WaitCommand(2.0_s),

            DriveToPosition(m_drive,300,300,0),

            frc2::WaitCommand(2.0_s),

            DriveToPosition(m_drive,-300,-300,0)*/

            /*frc2::WaitCommand(2.0_s),

            DriveToPosition(m_drive,m_sensors,300,0,0),

            frc2::WaitCommand(2.0_s),

            DriveToPosition(m_drive,m_sensors,0,-300,0),

            frc2::WaitCommand(2.0_s),

            DriveToPosition(m_drive,m_sensors,-300,0,0)*/

            //EnableCamera(m_camera,false),

            //StoreCommand(m_storage,m_sensors,m_drive),

            //frc2::WaitCommand(5.0_s),

            //DestoreCommand(m_storage,m_sensors,m_drive)

            //EnableCamera(m_camera,true)
        );
}