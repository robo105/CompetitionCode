#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/controller/PIDController.h>

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"
#include "RobotContainer.h"

class DriveWithPID : public frc2::CommandHelper<frc2::CommandBase, DriveWithPID>
{
    public:
        DriveWithPID(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, double setPointX, double setPointY, double setPointZ, double epsilonX, double epsilonY, double epsilonZ);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;
    
    private: 
        DriveBase* drive;
        Sensors* sensor;
        CommandHandler* m_cmd_h;

        double setPointX, setPointY, setPointZ;
        double epsilonX, epsilonY, epsilonZ;
        double kPx = 0.01;
        double kIx = 0.001;
        double kDx = 0.000000001;
        double kPy = 0.01;
        double kIy = 0.001;
        double kDy = 0.000000001;
        double kPz = 0.01;
        double kIz = 0.001;
        double kDz = 0.000000001;

        frc2::PIDController pidX{kPx, kIx, kDx};
        frc2::PIDController pidY{kPy, kIy, kDy};
        frc2::PIDController pidZ{kPz, kIz, kDz};
};