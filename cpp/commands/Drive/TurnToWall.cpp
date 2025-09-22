#include "commands/Drive/TurnToWall.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

TurnToWall::TurnToWall(DriveBase* drive,Sensors* sensor,CommandHandler* cmd_h)
{
    AddRequirements({drive});
    m_drive = drive;
    m_cmd_h = cmd_h;
    m_sensor = sensor;

}

#define SPEED_TURN_WALL 15

void TurnToWall::Initialize()
{
    m_cmd_h->AddCommand("TurnToWall");

    IRLeft_help=0;
    IRRight_help=0;

    IRLeft=0;
    IRRight=0;
  
    CountIR = 0;  

   if(m_sensor->IRLeftDistance()>m_sensor->IRRightDistance())
   {
       turn_direction=true;
       m_drive->SetFrontLeftSpeed(SPEED_TURN_WALL);
       m_drive->SetFrontRightSpeed(SPEED_TURN_WALL);
       m_drive->SetBackSpeed(SPEED_TURN_WALL);
   }
   else if(m_sensor->IRLeftDistance()<m_sensor->IRRightDistance())
   {
       turn_direction=false;
       m_drive->SetFrontLeftSpeed(-SPEED_TURN_WALL);
       m_drive->SetFrontRightSpeed(-SPEED_TURN_WALL);
       m_drive->SetBackSpeed(-SPEED_TURN_WALL);
   }

    m_drive->SetOmptimizeLevel(1);
}

void TurnToWall::Execute()
{   
    /*if(CountIR>MAXIR)
    {
        IRRight=IRRight_help/MAXIR;
        IRLeft=IRLeft_help/MAXIR;

        IRLeft_help=0;
        IRRight_help=0;
        CountIR=0;
    }
    else
    {
        CountIR++;
        IRLeft_help+=m_sensor->IRLeftDistance();
        IRRight_help+=m_sensor->IRRightDistance();
    }*/
    IRLeft=m_sensor->IRLeftDistance();
    IRRight=m_sensor->IRRightDistance();
    
    if(IRLeft<IRRight&&turn_direction==true)
    {
        if(Multi>0.25)
            Multi-=0.05;

        m_drive->SetFrontLeftSpeed(-(SPEED_TURN_WALL*Multi));
        m_drive->SetFrontRightSpeed(-(SPEED_TURN_WALL*Multi));
        m_drive->SetBackSpeed(-(SPEED_TURN_WALL*Multi));

        turn_direction=false;
    }
    else if(IRLeft>IRRight&&turn_direction==false)
    {        
        if(Multi>0.25)
            Multi-=0.05;

        m_drive->SetFrontLeftSpeed(SPEED_TURN_WALL*Multi);
        m_drive->SetFrontRightSpeed(SPEED_TURN_WALL*Multi);
        m_drive->SetBackSpeed(SPEED_TURN_WALL*Multi);

        turn_direction=true;
    }

    //frc::SmartDashboard::PutNumber("TurnWall IRRight",IRRight);
    //frc::SmartDashboard::PutNumber("TurnWall IRLeft",IRLeft);

    //count++;
    
}

void TurnToWall::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("TurnToWall");
    m_drive->HolonomicDrive(0,0,0);
}

bool TurnToWall::IsFinished()
{
    if(IRRight-IRLeft>-0.025&&IRRight-IRLeft<0.025&&(IRRight!=0||IRLeft!=0))
    {
        return true;
    }
    return false;
}