#include "commands/Drive/PositionBeforeCubeCalculate.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

PositionBeforeCubeCalculate::PositionBeforeCubeCalculate(DriveBase* drive, Camera* camera, Sensors* sensor,CommandHandler* cmd_h, bool vonOben)
{
    AddRequirements({drive, camera});
    m_drive = drive;
    m_camera = camera;
    m_sensor = sensor;
    m_vonOben = vonOben;
    m_cmd_h = cmd_h;

}

double Speedx = 0;
double SpeedxVorher = 0;

double Distance = 0;

void PositionBeforeCubeCalculate::Initialize()
{
    //m_drive->SetOmptimizeLevel(2);
    //m_drive->HolonomicDrive(0,0,0);
    m_cmd_h->AddCommand("PositionBeforeCubeCalculate");
    Distance = m_camera->GetDiferenceToCube();
    DistanceFront = m_sensor->IRLeftDistance();
    
    double Distance_help = 0;

    if(Distance!=1000)
    {
        
        if(m_vonOben==false)
        {
            for(int i=0;i<3;i++)
            {
                Distance_help+=0.3342387483*Distance + 9.1508219046;
                m_camera->SearchforCube(); // Funktion gegen TakePictureForQRCode getauscht
                Distance = m_camera->GetDiferenceToCube(); // Funktion hinzugefügt
            }
        }
        else
        {
            for(int i=0;i<3;i++)
            {
                Distance_help+=(0.2074122431*Distance)*0.95;// + 17.1066325968;
                m_camera->SearchforCube(); // Funktion gegen TakePictureForQRCode getauscht
                Distance = m_camera->GetDiferenceToCube(); // Funktion hinzugefügt
            }
        }
        
        Distance=Distance_help/3;

        if(Distance < 17 && Distance > -17)
        {
            Distance = 0;
        }
        //Distance = 0.3342387483*Distance + 9.1508219046;
        //Distance = 0.601915959*Distance - 0.0458380785 + ((-2.83*m_camera->GetCubeHigh() + 889.57)/10); // 52
        m_drive->SetPositionX(Distance);
        //m_drive->Position_y = DistanceFront;

    }

    //frc::SmartDashboard::PutNumber("Diference Cube Calculated",m_drive->GetPositionX());
    //m_drive->HolonomicDrive(Speedx,0,0);
}

void PositionBeforeCubeCalculate::Execute()
{    
    /*Distance = m_camera->GetDiferenceToCube();

    if(m_camera->FarbeErkannt()==true&&Distance!=1000)
    {
        if(Distance>0)
        {
            Speedx=-30;
        }
        else if(Distance<0)
        {
            Speedx=30;
        }
    }

    if(Distance==1000)
    {
        Speedx=0;
    }

    frc::SmartDashboard::PutNumber("Differenz zu Würfel",Distance);
    frc::SmartDashboard::PutNumber("Speed X Würfel",Speedx);

    if(SpeedxVorher!=Speedx)
    {
        m_drive->HolonomicDrive(Speedx,0,0);
    }

    SpeedxVorher = Speedx;*/
}

void PositionBeforeCubeCalculate::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("PositionBeforeCubeCalculate");
    //m_drive->HolonomicDrive(0,0,0);
}

bool PositionBeforeCubeCalculate::IsFinished()
{
    /*if(Distance>-150&&Distance<150)
    {
        End(false);
        return true;
    }*/
    return true;
}