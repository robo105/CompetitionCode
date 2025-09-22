#include "commands/Drive/PositionBeforeLine.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

PositionBeforeLine::PositionBeforeLine(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h)
{
    AddRequirements({drive, sensor});
    m_drive = drive;
    m_sensor = sensor;
    m_cmd_h = cmd_h;
}

double Speedx_Line = 0;
double Speedx_Line_a = 0;
double SpeedxVorher_Line = 0;

double Distance0 = 0;
double Distance1 = 0;
double Distance2 = 0;
double Distance3 = 0;

void PositionBeforeLine::Initialize()
{
    m_cmd_h->AddCommand("PositionBeforeLine");
    count = 0;
    m_drive->SetOmptimizeLevel(2);
    //m_drive->SetHandleIMU();
    global::savedAngle=m_drive->GetYaw();
    m_drive->HolonomicDrive(0,0,0);
    //Distance = m_camera->GetDiferenceToCube();
    Distance0 = m_sensor->GetCobra(0);
    Distance1 = m_sensor->GetCobra(1);
    Distance2 = m_sensor->GetCobra(2);
    Distance3 = m_sensor->GetCobra(3);

    if((Distance1>constant::VALUE_LINE&&Distance2<constant::VALUE_LINE)||(Distance0 > constant::VALUE_LINE))
    {
        Speedx_Line = -40;
    }
    else if((Distance1<constant::VALUE_LINE&&Distance2>constant::VALUE_LINE) || (Distance3 > constant::VALUE_LINE))
    {
        Speedx_Line = 40;
    }

    Speedx_Line_a = Speedx_Line;
    m_drive->HolonomicDrive(Speedx_Line,0,0);
}

double Speedx_Line_v = 0;

void PositionBeforeLine::Execute()
{   
    Distance0 = m_sensor->GetCobra(0);
    Distance1 = m_sensor->GetCobra(1);
    Distance2 = m_sensor->GetCobra(2);
    Distance3 = m_sensor->GetCobra(3);

    if((Distance1>constant::VALUE_LINE&&Distance2<constant::VALUE_LINE)||(Distance0 > constant::VALUE_LINE))
    {
        Speedx_Line = -40;
        if(count>=10)
        {
            Speedx_Line = -25;
        }
        count++;
    }
    else if((Distance1<constant::VALUE_LINE&&Distance2>constant::VALUE_LINE) || (Distance3 > constant::VALUE_LINE))
    {
        Speedx_Line = 40;
        if(count>=10)
        {
            Speedx_Line = 25;
        }
        count++;
    }
    else
    {
        Speedx_Line = -Speedx_Line_a;
    }
    
    if(Speedx_Line!=Speedx_Line_v)
    {
        m_drive->HolonomicDrive(Speedx_Line,0,0);
    }
    
    Speedx_Line_v = Speedx_Line;
    //Distance = m_camera->GetDiferenceToCube();

    /*if(m_camera->FarbeErkannt()==true&&Distance!=1000)
    {
        if(Distance>10)
        {
            if(Distance<80)
            {
                Speedx=-50;
            }
            else
            {
                Speedx=-50;
            }
        }
        else if(Distance<10)
        {
            if(Distance>-80)
            {
                Speedx=50;
            }
            else
            {
                Speedx=50;
            }
        }
        else
        {
            Speedx=0;
        }
    }*/

    /*if(Distance==1000)
    {
        Speedx=0;
    }*/

    //frc::SmartDashboard::PutNumber("Differenz zu Würfel",Distance);
    //frc::SmartDashboard::PutNumber("Speed X Würfel",Speedx);

    /*if(SpeedxVorher!=Speedx)
    {
        m_drive->HolonomicDrive(Speedx,0,0);
    }*/

    //SpeedxVorher = Speedx;
    m_drive->HolonomicDrive(Speedx_Line,0,0);
    frc::SmartDashboard::PutNumber("Position Line Cobra0",Distance0);
    frc::SmartDashboard::PutNumber("Position Line Cobra1",Distance1);
    frc::SmartDashboard::PutNumber("Position Line Cobra2",Distance2);
    frc::SmartDashboard::PutNumber("Position Line Cobra3",Distance3);
    
}

void PositionBeforeLine::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("PositionBeforeLine");
    m_drive->HolonomicDrive(0,0,0);
}

bool PositionBeforeLine::IsFinished()
{
    if(Distance1>constant::VALUE_LINE && Distance2>constant::VALUE_LINE)
    {
        End(false);
        return true;
    }
    return false;
}