#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Camera.h"
#include "subsystems/DriveBase.h"
#include "subsystems/Storage.h"
#include "subsystems/CommandHandler.h"

class PictureQRCode : public frc2::CommandHelper<frc2::CommandBase, PictureQRCode>
{
    public:
        PictureQRCode(DriveBase* drive, Camera* camera, Storage* storage, CommandHandler* cmd_h);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;

    private:
        Camera* m_camera;
        DriveBase* m_drive;
        Storage* m_storage;
        CommandHandler* m_cmd_h;
        bool m_direction;
        double count;
};