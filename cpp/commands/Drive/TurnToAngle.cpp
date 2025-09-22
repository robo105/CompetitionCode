#include "commands/Drive/TurnToAngle.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

TurnToAngle::TurnToAngle(DriveBase* drive,CommandHandler* cmd_h, double angle, double speed, double range)
{
    AddRequirements({drive});
    m_drive = drive;
    m_angle = angle;
    m_cmd_h = cmd_h;

    m_speed = speed;
    m_range = range;
}

//#define SPEED_TURN 35

double GetGreaterAngle(double a, double b)
{
    double t;
    t = b - a;

    return (t - (((int)(t / 180)) * 360));
}

void TurnToAngle::Initialize()
{
    m_cmd_h->AddCommand("TurnToAngle");
    /*if(((m_angle<=360)&&(m_angle>=0))||m_angle==constant::STARTING_ANGLE)
    {*/
        /*if(m_angle!=constant::STARTING_ANGLE)
        {
            m_drive->SetHandleIMU();
        }
        else
        {*/
            //m_angle=m_drive->GetStartingAngle();
        //}
        //frc::SmartDashboard::PutNumber("uebergebener Winkel",m_angle);

        if(m_angle!=constant::STARTING_ANGLE)
        {
            angle_help=m_angle+m_drive->GetStartingAngle();
        }
        else
        {
            angle_help=global::savedAngle;
        }
        
        global::lastAngle = angle_help;
        //m_angle-=180;
        
        if(angle_help>360)
        {
            angle_help-360;
        }

        //m_drive->SetHandleIMU();
        m_drive->SetOmptimizeLevel(1);

        //frc::SmartDashboard::PutNumber("aktueller Winkel",m_drive->GetYaw());


        if(GetGreaterAngle(m_drive->GetYaw(),angle_help)>0)
        {
            //frc::SmartDashboard::PutNumber("Winkel zu groß",angle_help);
            m_drive->SetFrontLeftSpeed(m_speed);
            m_drive->SetFrontRightSpeed(m_speed);
            m_drive->SetBackSpeed(m_speed);
            //m_drive->HolonomicDrive(0,0,60);

            turn_direction=true;
        }
        else if(GetGreaterAngle(m_drive->GetYaw(),angle_help)<0)
        {
            //frc::SmartDashboard::PutNumber("Winkel zu klein",angle_help);
            //m_drive->HolonomicDrive(0,0,-60);
            m_drive->SetFrontLeftSpeed(-m_speed);
            m_drive->SetFrontRightSpeed(-m_speed);
            m_drive->SetBackSpeed(-m_speed);

            turn_direction=false;
        }
    //}
}

void TurnToAngle::Execute()
{   
    if((GetGreaterAngle(m_drive->GetYaw(),angle_help)>0)&&turn_direction==false)
    {
        frc::SmartDashboard::PutNumber("Winkel zu groß",GetGreaterAngle(m_drive->GetYaw(),angle_help));

        if(Multi>0.35)
            Multi-=0.05;

        m_drive->SetFrontLeftSpeed(m_speed*Multi);
        m_drive->SetFrontRightSpeed(m_speed*Multi);
        m_drive->SetBackSpeed(m_speed*Multi);

        /*m_drive->SetFrontLeftSpeed(-(m_speed*Multi));
        m_drive->SetFrontRightSpeed(-(m_speed*Multi));
        m_drive->SetBackSpeed(-(m_speed*Multi));*/

        turn_direction=true;
        //m_drive->HolonomicDrive(0,0,60);
    }
    else if((GetGreaterAngle(m_drive->GetYaw(),angle_help)<0)&&turn_direction==true)
    {
        frc::SmartDashboard::PutNumber("Winkel zu klein",GetGreaterAngle(m_drive->GetYaw(),angle_help));
        
        if(Multi>0.35)
            Multi-=0.05;

        m_drive->SetFrontLeftSpeed(-(m_speed*Multi));
        m_drive->SetFrontRightSpeed(-(m_speed*Multi));
        m_drive->SetBackSpeed(-(m_speed*Multi));

        /*m_drive->SetFrontLeftSpeed(m_speed*Multi);
        m_drive->SetFrontRightSpeed(m_speed*Multi);
        m_drive->SetBackSpeed(m_speed*Multi);*/

        turn_direction=false;
        //m_drive->HolonomicDrive(0,0,-60);
    }

    count++;
    frc::SmartDashboard::PutNumber("countTurn",count);

    frc::SmartDashboard::PutNumber("Winkel aktuell",m_drive->GetYaw());
    frc::SmartDashboard::PutNumber("Winkel gesetzt",angle_help);
    /*frc::SmartDashboard::PutNumber("Winkel Differenz",GetGreaterAngle(m_drive->GetYaw(),angle_help));*/
}

void TurnToAngle::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("TurnToAngle");
    m_drive->HolonomicDrive(0,0,0);
}

bool TurnToAngle::IsFinished()
{
    if((GetGreaterAngle(m_drive->GetYaw(),angle_help)<m_range)&&(GetGreaterAngle(m_drive->GetYaw(),angle_help)>-m_range))
    {
        return true;
    }
    return false;
}