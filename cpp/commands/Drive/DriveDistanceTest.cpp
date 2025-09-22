#include "commands/Drive/DriveDistanceTest.h"
#include "commands/Drive/DriveWithPID.h"
#include <frc2/command/ParallelRaceGroup.h>
#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"

DriveDistanceTest::DriveDistanceTest(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h)
{
    AddCommands
    (
        frc2::WaitCommand(1.0_s),
        DriveWithPID(drive, sensor,cmd_h, 0.0, 2000, 0.0, 0.0, 10, 1.0).WithTimeout(15.0_s)
    );
}