#include "commands/Drive/DriveUntilCube.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

DriveUntilCube::DriveUntilCube(DriveBase* drive,Sensors* sensor, Camera* camera,Storage* storage,CommandHandler* cmd_h,  bool direction_right)
{
    AddRequirements({drive, camera});
    m_drive = drive;
    m_camera = camera;
    m_sensor = sensor;
    m_storage = storage;
    m_cmd_h = cmd_h;
    m_direction_right = direction_right;
}

//double Speedx_Cube = 0;
//double SpeedxVorher_cube = 0;

//double Distance = 0;

int countUntilCube = 0;

void DriveUntilCube::Initialize()
{
    m_cmd_h->AddCommand("DriveUntilCube");
    m_drive->SetOmptimizeLevel(2);
    //m_drive->SetHandleIMU();
    global::savedAngle=m_drive->GetYaw();
    m_drive->HolonomicDrive(0,0,0);

    //Distance = m_camera->GetDiferenceToCube();

    if(m_direction_right==true)
    {
        m_drive->HolonomicDrive(80,0,0);
        SpeedY = 80;
    }
    else
    {
        //m_drive->HolonomicDrive(-40,0,0);
        m_drive->HolonomicDrive(-80,0,0);
        SpeedY = -80;
    }
}

void DriveUntilCube::Execute()
{    
    //frc::SmartDashboard::PutNumber("DriveUntilCube bool",m_direction_right);
    m_camera->SearchforCube();
    if(m_direction_right==true)
    {
        countUntilCube++;
        //if(m_first_try==true)
        if(m_sensor->USRightDistance()<200)
        {
            SpeedY = -60;
            if(m_storage->GetAngleGreifarm()>138)
            {
                m_storage->SetGreifarm(m_storage->GetAngleGreifarm()-1);
            }
        }
        else if(m_sensor->USLeftDistance()<200)
        {
            SpeedY = 60;

            if(m_storage->GetAngleGreifarm()>138)
            {
                m_storage->SetGreifarm(m_storage->GetAngleGreifarm()-1);
            }
        }
        //m_drive->HolonomicDrive(70,0,0);
    }
    else
    {
        countUntilCube--;

        if(m_sensor->USRightDistance()<200)
        {
            SpeedY = -60;
            if(m_storage->GetAngleGreifarm()>138)
            {
                m_storage->SetGreifarm(m_storage->GetAngleGreifarm()-1);
            }
        }
        else if(m_sensor->USLeftDistance()<200)
        {
            SpeedY = 60;
            if(m_storage->GetAngleGreifarm()>138)
            {
                m_storage->SetGreifarm(m_storage->GetAngleGreifarm()-1);
            }
        }
        //m_drive->HolonomicDrive(-40,0,0);
        //m_drive->HolonomicDrive(-70,0,0);
    }

    m_drive->HolonomicDrive(SpeedY,0,0);

    //frc::SmartDashboard::PutNumber("countDriveUntilCube",countUntilCube);
}

void DriveUntilCube::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("DriveUntilCube");
    m_drive->HolonomicDrive(0,0,0);
}

bool DriveUntilCube::IsFinished()
{
    //if(m_camera->FarbeErkannt()==true)
    if(m_camera->GetDiferenceToCube()<200&&m_camera->GetDiferenceToCube()>-200)
    {   
        End(false);
        return true;
    }
    return false;
}