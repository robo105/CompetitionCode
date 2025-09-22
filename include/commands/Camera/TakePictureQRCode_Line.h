#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Camera.h"
#include "subsystems/CommandHandler.h"

class TakePictureQRCode_Line : public frc2::CommandHelper<frc2::CommandBase, TakePictureQRCode_Line>
{
    public:
        TakePictureQRCode_Line(Camera* camera,CommandHandler* cmd_h, bool direction);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;

    private:
        Camera* m_camera;
        CommandHandler* m_cmd_h;
        bool m_direction;
};