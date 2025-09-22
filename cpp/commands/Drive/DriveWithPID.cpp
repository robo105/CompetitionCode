#include "commands/Drive/DriveWithPID.h"

DriveWithPID::DriveWithPID(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, double setPointX, double setPointY, double setPointZ, double epsilonX, double epsilonY, double epsilonZ) : drive{drive}, setPointX{setPointX}, setPointY{setPointY}, setPointZ{setPointZ}, epsilonX{epsilonX}, epsilonY{epsilonY}, epsilonZ{epsilonZ} 
{
    AddRequirements({drive, sensor, cmd_h});
}

/**
 * Runs once when command is started
 */
void DriveWithPID::Initialize()
{
    m_cmd_h->AddCommand("DriveWithPID");
    pidX.SetTolerance(epsilonX);
    pidY.SetTolerance(epsilonY);
    pidZ.SetTolerance(epsilonZ);
    drive->ResetEncoders();
}

/**
 * Called continously until command is ended
 */
void DriveWithPID::Execute()
{
    /*drive->HolonomicDrive(0.0,
    std::clamp(pidY.Calculate(drive->GetYDistance(), setPointY), -0.5, 0.5),
    std::clamp(pidY.Calculate(sensor->GetYaw(), setPointZ), -0.5, 0.5));*/
    drive->HolonomicDriveWithoutOptimize(0.0,
    std::clamp(pidY.Calculate(drive->GetYDistanceRaw(), setPointY), -0.8, 0.8),
    0.0);
    //frc::SmartDashboard::PutNumber("Distance Y Encoder",drive->GetYDistance());
}

/**
 * Called when the command is told to end or is interrupted
 */
void DriveWithPID::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("DriveWithPID");
    drive->HolonomicDriveWithoutOptimize(0.0, 0.0, 0.0);
    //pidY.AtSetpoint()
}

/**
 * Creates an isFinished condition if needed
 */
bool DriveWithPID::IsFinished()
{
    if(pidY.AtSetpoint())
    {
        drive->HolonomicDriveWithoutOptimize(0.0, 0.0, 0.0);
        End(false);
        return true;
    }
    return false;
}