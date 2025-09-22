#include <frc2/command/ParallelRaceGroup.h>

#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"
#include "frc2/command/ConditionalCommand.h"

#include "commands/StorageTask.h"

#include "commands/Drive/FollowWall.h"
#include "commands/Drive/TurnToAngleCommand.h"
#include "commands/Drive/DriveUntilWall.h"
#include "commands/Camera/PictureQRCode.h"
#include "commands/Storage/SetElevatorToTop.h"
#include "commands/Drive/DriveToLine.h"
#include "commands/Drive/FollowLine.h"

#include "commands/HigherCommands/DriveRightWay.h"
#include "commands/HigherCommands/DriveLeftWay.h"

#include "commands/Camera/SearchForColor.h"
#include "commands/Storage/SetGreifarm.h"
#include "commands/Drive/DriveToPosition.h"
#include "commands/Camera/EnableCamera.h"

#include "commands/FindCubeOben.h"
#include "commands/Drive/PositionBeforeLine.h"
#include "commands/HigherCommands/GrabCube.h"
#include "commands/Drive/InitDrive.h"

#include "commands/HigherCommands/TakeRedCube.h"
#include "commands/HigherCommands/TakeBlueCube.h"
#include "commands/HigherCommands/TakeYellowCube.h"

#include "commands/DestoreCommand.h"
#include "commands/Camera/ChangeColorDetectionRed.h"

StorageTask::StorageTask(Storage* store, Sensors* sensor, DriveBase* drive, Camera* camera, CommandHandler* cmd_h)
{
    m_storage = store;
    m_drive = drive;
    m_sensors = sensor;
    m_camera = camera;
    m_cmd_h = cmd_h;

    Camera mcamera = *m_camera;

    AddRequirements({store,sensor,drive, camera,m_cmd_h});


    AddCommands(

            ChangeColorDetectionRed(m_camera,m_cmd_h,0),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,-70,0,0,constant::Sensor_IDs::US_L,150),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R,220),

            TurnToAngleCommand(m_drive,m_cmd_h,90),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R,450),

            EnableCamera(m_camera,m_cmd_h,false),

            PictureQRCode(m_drive,m_camera,m_storage,m_cmd_h),

            EnableCamera(m_camera,m_cmd_h,false),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

            TurnToAngleCommand(m_drive,m_cmd_h,180),

            // Würfel 1

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,-70,0,0,constant::Sensor_IDs::US_L,150),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R),

            DriveToLine(m_drive,m_sensors,m_cmd_h,60,0,0),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,60,0,constant::Sensor_IDs::IR_R,260),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::MINIMUM),

            SearchForColor(m_drive,m_camera,m_storage,m_cmd_h,0,0,0),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),
            
            frc2::ConditionalCommand(                                                                   // Würfel 1 Nr. 5
                GrabCube(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,constant::Lagerung::HANDLE_STORAGE,true,constant::DISTANCE_TO_CUBE), // wenn richtige Farbe erkannt wurde soll der Würfel aufgehoben werden
                InitDrive(m_drive,m_cmd_h,2), // wennn nicht dann nichts tun
                [&mcamera] { return mcamera.IsDetectedColorSearched(); }
            ),

            // Würfel 2

            DriveToPosition(m_drive,m_cmd_h,0,-850,0),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,90,0,0,constant::Sensor_IDs::US_R,150),

            // 10

            //DriveUntilWall(m_drive,m_sensors,m_cmd_h,-70,0,0,constant::Sensor_IDs::US_L,150),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R),

            DriveToLine(m_drive,m_sensors,m_cmd_h,-60,0,0),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,60,0,constant::Sensor_IDs::IR_R,260),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::MINIMUM),

            SearchForColor(m_drive,m_camera,m_storage,m_cmd_h,0,0,0),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),
            
            frc2::ConditionalCommand(                                                                   // Würfel 2 Nr. 1
                GrabCube(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,constant::Lagerung::HANDLE_STORAGE,true,constant::DISTANCE_TO_CUBE), // wenn richtige Farbe erkannt wurde soll der Würfel aufgehoben werden
                InitDrive(m_drive,m_cmd_h,2), // wennn nicht dann nichts tun
                [&mcamera] { return mcamera.IsDetectedColorSearched(); }
            ),

            ChangeColorDetectionRed(m_camera,m_cmd_h,1),

            TurnToAngleCommand(m_drive,m_cmd_h,0),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,-60,0,0,constant::Sensor_IDs::US_L,150),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R,260),

            // Würfel 3 Nr. 2

            DriveToLine(m_drive,m_sensors,m_cmd_h,60,0,0),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,60,0,constant::Sensor_IDs::IR_R,260),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::MINIMUM),

            SearchForColor(m_drive,m_camera,m_storage,m_cmd_h,0,0,0),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),
            
            frc2::ConditionalCommand(                                                                   // Würfel 2 Nr. 1
                GrabCube(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,constant::Lagerung::HANDLE_STORAGE,true,constant::DISTANCE_TO_CUBE), // wenn richtige Farbe erkannt wurde soll der Würfel aufgehoben werden
                InitDrive(m_drive,m_cmd_h,2), // wennn nicht dann nichts tun
                [&mcamera] { return mcamera.IsDetectedColorSearched(); }
            ),

            // Würfel 4 Nr. 3

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,70,0,0,constant::Sensor_IDs::US_L,500),

            DriveToLine(m_drive,m_sensors,m_cmd_h,60,0,0),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,60,0,constant::Sensor_IDs::IR_R,260),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::MINIMUM),

            SearchForColor(m_drive,m_camera,m_storage,m_cmd_h,0,0,0),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),
            
            frc2::ConditionalCommand(                                                                   // Würfel 2 Nr. 1
                GrabCube(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,constant::Lagerung::HANDLE_STORAGE,true,constant::DISTANCE_TO_CUBE), // wenn richtige Farbe erkannt wurde soll der Würfel aufgehoben werden
                InitDrive(m_drive,m_cmd_h,2), // wennn nicht dann nichts tun
                [&mcamera] { return mcamera.IsDetectedColorSearched(); }
            ),

            // Würfel 5 Nr. 4

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,70,0,0,constant::Sensor_IDs::US_L,750),

            DriveToLine(m_drive,m_sensors,m_cmd_h,60,0,0),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,60,0,constant::Sensor_IDs::IR_R,260),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::MINIMUM),

            SearchForColor(m_drive,m_camera,m_storage,m_cmd_h,0,0,0),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),
            
            frc2::ConditionalCommand(                                                                   // Würfel 2 Nr. 1
                GrabCube(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,constant::Lagerung::HANDLE_STORAGE,true,constant::DISTANCE_TO_CUBE), // wenn richtige Farbe erkannt wurde soll der Würfel aufgehoben werden
                InitDrive(m_drive,m_cmd_h,2), // wennn nicht dann nichts tun
                [&mcamera] { return mcamera.IsDetectedColorSearched(); }
            ),

            // Übergang

            TurnToAngleCommand(m_drive,m_cmd_h,90),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R),

            // Würfel 6 Nr. 6

            //DriveUntilWall(m_drive,m_sensors,m_cmd_h,70,0,0,constant::Sensor_IDs::US_L,750),

            DriveToLine(m_drive,m_sensors,m_cmd_h,-60,0,0),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,60,0,constant::Sensor_IDs::IR_R,260),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::MINIMUM),

            SearchForColor(m_drive,m_camera,m_storage,m_cmd_h,0,0,0),

            SetElevatorToTop(m_storage,m_cmd_h,true),

            SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),
            
            frc2::ConditionalCommand(                                                                   // Würfel 2 Nr. 1
                GrabCube(m_storage,m_camera,m_drive,m_sensors,m_cmd_h,constant::Lagerung::HANDLE_STORAGE,true,constant::DISTANCE_TO_CUBE), // wenn richtige Farbe erkannt wurde soll der Würfel aufgehoben werden
                InitDrive(m_drive,m_cmd_h,2), // wennn nicht dann nichts tun
                [&mcamera] { return mcamera.IsDetectedColorSearched(); }
            ),


            // Entscheidung aufgrund von Farbe


            frc2::ConditionalCommand(

                TakeRedCube(m_storage,m_camera,m_drive,m_sensors,m_cmd_h),
                
                frc2::ConditionalCommand(
                    TakeBlueCube(m_storage,m_camera,m_drive,m_sensors,m_cmd_h),    
                    TakeYellowCube(m_storage,m_camera,m_drive,m_sensors,m_cmd_h),
                    [&mcamera] { return mcamera.IsSearchedColorBlue(); }
                ),

                [&mcamera] { return mcamera.IsSearchedColorRed(); }
            ),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,70,42,0,constant::Sensor_IDs::US_R,300),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,60,0,0,constant::Sensor_IDs::US_R,150),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R),

            DriveToLine(m_drive,m_sensors,m_cmd_h,-60,0,0),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h),

            DestoreCommand(m_storage,m_sensors,m_drive,m_cmd_h,0),

            TurnToAngleCommand(m_drive,m_cmd_h,-90),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,-60,0,0,constant::Sensor_IDs::US_L),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,0,70,0,constant::Sensor_IDs::IR_R),

            DriveToLine(m_drive,m_sensors,m_cmd_h,60,0,0),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h),

            DestoreCommand(m_storage,m_sensors,m_drive,m_cmd_h,0),

            TurnToAngleCommand(m_drive,m_cmd_h,90),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,60,0,0,constant::Sensor_IDs::US_R),

            FollowWall(m_drive,m_sensors,m_cmd_h,true,260,constant::Sensor_IDs::IR_R),

            DriveToLine(m_drive,m_sensors,m_cmd_h,-60,0,0),

            PositionBeforeLine(m_drive,m_sensors,m_cmd_h),

            DestoreCommand(m_storage,m_sensors,m_drive,m_cmd_h,0),

            TurnToAngleCommand(m_drive,m_cmd_h,-90),

            DriveUntilWall(m_drive,m_sensors,m_cmd_h,60,0,0,constant::Sensor_IDs::US_R),

            FollowWall(m_drive,m_sensors,m_cmd_h,true,0,-1),

            DriveToPosition(m_drive,m_cmd_h,0,200,0),

            TurnToAngleCommand(m_drive,m_cmd_h,0),

            DriveToPosition(m_drive,m_cmd_h,0,200,0)
            
        );
}