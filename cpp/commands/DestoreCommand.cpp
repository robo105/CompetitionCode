#include "commands/DestoreCommand.h"
#include "commands/Storage/SetStorePosition.h"
#include "commands/Storage/SetGreifzange.h"
#include "commands/Storage/SetGreifarm.h"
#include "commands/Storage/InitElevator.h"
#include "commands/Storage/SetElevatorToTop.h"
#include "commands/Storage/SetStorageAngle.h"
#include "commands/Storage/SetElevator.h"

#include "commands/Drive/DriveToCube.h"

#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"

DestoreCommand::DestoreCommand(Storage* store, Sensors* sensor, DriveBase* drive,CommandHandler* cmd_h, int position)
{
    m_storage = store;
    m_drive = drive;
    m_sensors = sensor;
    m_cmd_h = cmd_h;
    m_position = position;

    AddRequirements({store,sensor,drive,m_cmd_h});


    AddCommands(

        SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::GERADE),

        SetElevatorToTop(m_storage,m_cmd_h,false),

        SetStorePosition(m_storage,m_cmd_h,m_position),

        frc2::WaitCommand(0.2_s),

        SetGreifzange(m_storage,m_cmd_h, false),
        
        frc2::WaitCommand(0.2_s),

        SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

        frc2::WaitCommand(0.2_s),

        SetElevator(m_storage,m_cmd_h,constant::Elevator::POSITION_GRAB_CUBE),

        frc2::WaitCommand(0.2_s),

        SetGreifzange(m_storage,m_cmd_h, true),

        frc2::WaitCommand(0.2_s),

        SetElevatorToTop(m_storage,m_cmd_h,true),

        frc2::WaitCommand(0.2_s),

        SetGreifarm(m_storage,m_cmd_h, constant::Greifarm::GERADE),

        frc2::WaitCommand(0.2_s),

        SetElevatorToTop(m_storage,m_cmd_h,false),

        frc2::WaitCommand(0.2_s),

        SetGreifzange(m_storage,m_cmd_h,false),

        SetGreifarm(m_storage,m_cmd_h,constant::Greifarm::OBEN),

        SetElevatorToTop(m_storage, m_cmd_h,true)
        
        );
}

