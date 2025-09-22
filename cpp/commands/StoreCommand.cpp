#include "commands/StoreCommand.h"
#include "commands/Storage/SetStorePosition.h"
#include "commands/Storage/SetGreifzange.h"
#include "commands/Storage/SetGreifarm.h"
#include "commands/Storage/InitElevator.h"
#include "commands/Storage/SetElevatorToTop.h"
#include "commands/Storage/SetStorageAngle.h"
#include "commands/Storage/SetElevator.h"

#include "commands/Drive/DriveToCube.h"
#include "commands/Drive/DriveToPosition.h"

#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"

#include "commands/Storage/ReleaseCube.h"

StoreCommand::StoreCommand(Storage* store, Sensors* sensor, DriveBase* drive,CommandHandler* cmd_h, int position, double distanceToCube)
{
    m_storage = store;
    m_drive = drive;
    m_sensors = sensor;
    m_cmd_h = cmd_h;

    m_position = position;
    m_distanceToCube = distanceToCube;

    AddRequirements({store,sensor,drive,m_cmd_h});


    AddCommands(

        DriveToCube(m_drive,m_sensors,m_cmd_h,m_distanceToCube),

        frc2::WaitCommand(0.2_s),

        //SetElevatorToTop(m_storage,m_cmd_h,false),
        
        SetElevator(m_storage,m_cmd_h,2500),

        //frc2::WaitCommand(0.2_s),

        //SetStorageAngle(m_storage,0),

        frc2::WaitCommand(0.2_s),

        SetStorePosition(m_storage,m_cmd_h,m_position),

        frc2::WaitCommand(0.2_s),

        SetGreifzange(m_storage,m_cmd_h,false),

        frc2::WaitCommand(0.2_s),

        SetGreifarm(m_storage,m_cmd_h, constant::Greifarm::GRAB_CUBE),

        frc2::WaitCommand(1.0_s),

        SetGreifzange(m_storage,m_cmd_h,true),

        frc2::WaitCommand(0.2_s),

        SetElevatorToTop(m_storage,m_cmd_h,true),

        frc2::WaitCommand(0.2_s),

        DriveToPosition(m_drive,m_cmd_h,-20,0,0),

        frc2::WaitCommand(0.2_s),

        SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

        frc2::WaitCommand(1.0_s),

        //SetElevator(m_storage,constant::Elevator::POSITION_GRAB_CUBE),
        
        //frc2::WaitCommand(1.0_s),
        ReleaseCube(m_storage,m_cmd_h),

        SetGreifzange(m_storage,m_cmd_h,false),

        frc2::WaitCommand(0.2_s),

        SetElevatorToTop(m_storage,m_cmd_h,true),
    
        frc2::WaitCommand(0.2_s),

        SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

        frc2::WaitCommand(1.0_s)
        );
}