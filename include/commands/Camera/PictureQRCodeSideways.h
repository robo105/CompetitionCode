#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Camera.h"
#include "subsystems/DriveBase.h"
#include "subsystems/Storage.h"
#include "subsystems/CommandHandler.h"
#include "subsystems/Sensors.h"

class PictureQRCodeSideways : public frc2::CommandHelper<frc2::CommandBase, PictureQRCodeSideways>
{
    public:
        PictureQRCodeSideways(DriveBase* drive,Sensors* sensor, Camera* camera, Storage* storage, CommandHandler* cmd_h, double x, double y, double w, bool QRCodeProoved = true);
        void Initialize() override;
        void Execute() override;
        void End(bool interrupted) override;
        bool IsFinished() override;

    private:
        Camera* m_camera;
        DriveBase* m_drive;
        Storage* m_storage;
        CommandHandler* m_cmd_h;
        Sensors* m_sensor;
        
        double m_x;
        double m_y;
        double m_w;

        bool m_QRCodeProoved;

        bool direction1 = true;

        const int Length=400;
        int CountAttempts = 0;
};