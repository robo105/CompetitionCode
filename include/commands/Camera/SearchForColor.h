#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Camera.h"
#include "subsystems/DriveBase.h"
#include "subsystems/Storage.h"
#include "subsystems/CommandHandler.h"

class SearchForColor : public frc2::CommandHelper<frc2::CommandBase, SearchForColor>
{
    public:
        SearchForColor(DriveBase* drive, Camera* camera, Storage* storage, CommandHandler* cmd_h, double x, double y, double w);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;

    private:
        Camera* m_camera;
        DriveBase* m_drive;
        Storage* m_storage;
        CommandHandler* m_cmd_h;
        
        double m_x;
        double m_y;
        double m_w;
};