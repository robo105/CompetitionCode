#include <frc/Timer.h>
#include <units/units.h>
#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"
#include "frc2/command/WaitCommand.h"
#include "frc2/command/ConditionalCommand.h"

#include "commands/HigherCommands/ReadQRCodeInFront.h"

#include "commands/Camera/TakePictureQRCode_Line.h"
#include "commands/HigherCommands/TurnLeftAtCrossing.h"
#include "commands/HigherCommands/TurnRightAtCrossing.h"
#include "commands/Camera/EnableCamera.h"
#include "commands/Storage/SetElevator.h"
#include "commands/Storage/SetGreifarm.h"

#include "commands/HigherCommands/TurnLeftAtCrossing.h"
#include "commands/HigherCommands/TurnRightAtCrossing.h"



ReadQRCodeInFront::ReadQRCodeInFront(Storage* storage, Camera* camera, DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h)
{
    m_camera = camera;
    m_storage = storage;
    m_drive = drive;
    m_sensor = sensor;
    m_cmd_h = cmd_h;

    Camera mcamera = *m_camera;

    //turn_left = TurnLeftAtCrossing(m_sensor, m_drive);

    AddRequirements({storage,camera, drive, sensor, m_cmd_h});


    AddCommands(

            

            frc2::ConditionalCommand(
                TurnRightAtCrossing(m_sensor,m_drive,m_cmd_h), // rechts
                TurnLeftAtCrossing(m_sensor,m_drive,m_cmd_h), // links
                [&mcamera] { return mcamera.drive_direction_right(); }
            ),
            //CheckforCrossing(m_drive, m_sensor,m_camera,m_storage,TurnLeftAtCrossing(m_sensor,m_drive),TurnRightAtCrossing(m_sensor,m_drive)),

            frc2::WaitCommand(0.2_s),

            EnableCamera(m_camera,m_cmd_h,false),

            frc2::WaitCommand(1.0_s)
        
        );
}

