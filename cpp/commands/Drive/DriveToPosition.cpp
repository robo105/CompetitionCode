#include "commands/Drive/DriveToPosition.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"
#include "Constants.h"

DriveToPosition::DriveToPosition(DriveBase* drive,CommandHandler* cmd_h, double x, double y, double w, double speed)
{
    AddRequirements({drive});
    m_drive = drive;
    m_cmd_h = cmd_h;
    m_speed = speed;

    m_x=x/constant::Encoder::DIST_PER_TICK;
    m_y=y/constant::Encoder::DIST_PER_TICK;
    m_w=w/constant::Encoder::DIST_PER_TICK;

    //frc::SmartDashboard::PutNumber("Drive to Position x",m_x);
}



/*int GetGreatest(double a, double b, double c)
{
  if(a>b&&a>c)
  {
    return 0;
  }
  else if(b>a&&b>c)
  {
    return 1;
  }

    return 2;
}*/

bool DriveToPosition::GetInverseMatrix()
{
  m_mat[0][0]=0;
  m_mat[0][1]=1;
  m_mat[0][2]=constant::DIAMETER;

  m_mat[1][0]=-sin(60*(M_PI/180));
  m_mat[1][1]=-0.5;
  m_mat[1][2]=constant::DIAMETER;

  m_mat[2][0]=sin(60*(M_PI/180));
  m_mat[2][1]=-0.5;
  m_mat[2][2]=constant::DIAMETER;

  double d = 0;

  for(int i = 0; i < 3; i++)
    d = d + (m_mat[0][i] * (m_mat[1][(i+1)%3] * m_mat[2][(i+2)%3] - m_mat[1][(i+2)%3] * m_mat[2][(i+1)%3]));
    
  if(d>0)
  {
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
        {
          m_inv_mat[i][j]=((m_mat[(j+1)%3][(i+1)%3] * m_mat[(j+2)%3][(i+2)%3]) - (m_mat[(j+1)%3][(i+2)%3] * m_mat[(j+2)%3][(i+1)%3]))/ d;
        }
     }
     return true;
  }
  return false;
}



void DriveToPosition::Initialize()
{
    m_cmd_h->AddCommand("DriveToPosition");
    GetInverseMatrix();
    //m_drive->SetHandleIMU();
    global::savedAngle=m_drive->GetYaw();
    //m_drive->ResetEncoders();
    StartFrontLeft=m_drive->GetFrontLeftEncoderRaw();
    StartFrontRight=m_drive->GetFrontRightEncoderRaw();
    StartBack=m_drive->GetBackEncoderRaw();

    DistanceBack = m_mat[0][0]*m_x+m_mat[0][1]*m_y+m_mat[0][2]*m_w;
    DistanceRight = m_mat[1][0]*m_x+m_mat[1][1]*m_y+m_mat[1][2]*m_w;
    DistanceLeft = m_mat[2][0]*m_x+m_mat[2][1]*m_y+m_mat[2][2]*m_w;

    bool Left = abs(DistanceLeft)>=abs(DistanceRight) && abs(DistanceLeft)>=abs(DistanceBack);
    bool Right = abs(DistanceRight)>=abs(DistanceLeft) && abs(DistanceRight)>=abs(DistanceBack);
    bool Back = abs(DistanceBack)>=abs(DistanceRight) && abs(DistanceBack)>=abs(DistanceLeft);

    double Groesste = 0;

    if(Left==true)
    {
        Groesste = abs(DistanceLeft);
    }
    else if(Right==true)
    {
        Groesste = abs(DistanceRight);
    }
    else
    {
        Groesste = abs(DistanceBack);
    }

    //TODO : eventuell vereinfachen

    if(Groesste != 0)
    {
        SpeedMultiLeft = abs(DistanceLeft)/Groesste;
        SpeedMultiRight = abs(DistanceRight)/Groesste;
        SpeedMultiBack = abs(DistanceBack)/Groesste;
    }
    else
    {
        SpeedMultiLeft = 0;
        SpeedMultiRight = 0;
        SpeedMultiBack = 0;
    }

    if(DistanceRight>=0)
    {
        m_drive->SetFrontRightSpeed(m_speed*SpeedMultiRight);
    }
    else
    {
        m_drive->SetFrontRightSpeed(-m_speed*SpeedMultiRight);
    }

    if(DistanceLeft>=0)
    {
        m_drive->SetFrontLeftSpeed(m_speed*SpeedMultiLeft);
    }
    else
    {
        m_drive->SetFrontLeftSpeed(-m_speed*SpeedMultiLeft);
    }

    if(DistanceBack>=0)
    {
        m_drive->SetBackSpeed(m_speed*SpeedMultiBack);
    }
    else
    {
        m_drive->SetBackSpeed(-m_speed*SpeedMultiBack);
    }

    //DriveToTarget=true;

    //m_drive->ResetEncoders();

    /*DistanceDistanceBack = EncoderBack.GetRaw()*constant::Encoder::DIST_PER_TICK;
    DistanceDistanceRight = EncoderRight.GetRaw()*constant::Encoder::DIST_PER_TICK;
    DistanceDistanceLeft = EncoderLeft.GetRaw()*constant::Encoder::DIST_PER_TICK;*/
    /*DistanceBack += StartBack;
    DistanceLeft += StartFrontLeft;
    DistanceRight += StartFrontRight;*/
    EndBack = DistanceBack+StartBack;
    EndLeft = DistanceLeft+StartFrontLeft;
    EndRight = DistanceRight+StartFrontRight;

    /*frc::SmartDashboard::PutNumber("Distance aim Left",DistanceLeft);
    frc::SmartDashboard::PutNumber("Distance aim Right",DistanceRight);
    frc::SmartDashboard::PutNumber("Distance aim Back",DistanceBack);

    frc::SmartDashboard::PutNumber("Distance Cube Position",m_drive->GetPositionX());*/
}

void DriveToPosition::Execute()
{
    /*frc::SmartDashboard::PutNumber("Encoder Left",abs(m_drive->GetFrontLeftEncoderRaw()));
    frc::SmartDashboard::PutNumber("Encoder Right",abs(m_drive->GetFrontRightEncoderRaw()));
    frc::SmartDashboard::PutNumber("Encoder Back",abs(m_drive->GetBackEncoderRaw()));*/

    countDriveToPositionTest++;
    //frc::SmartDashboard::PutNumber("Count DriveToPosition x",countDriveToPositionTest);
}

void DriveToPosition::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("DriveToPosition");
    m_drive->HolonomicDrive(0,0,0);
}

bool DriveToPosition::IsFinished()
{
    //if((abs(m_drive->GetBackEncoderRaw()))>abs(DistanceBack)&&DistanceBack!=0)
    if((DistanceLeft > 0 && m_drive->GetFrontLeftEncoderRaw() > EndLeft) || (DistanceLeft < 0 && m_drive->GetFrontLeftEncoderRaw() < EndLeft))
    {
        /*m_drive->SetBackSpeed(0);
        m_drive->SetFrontLeftSpeed(0);
        m_drive->SetFrontRightSpeed(0);*/
        //DriveToTarget=false;

        //ResetEncoders();

        //frc::SmartDashboard::PutNumber("EncoderLeft Raw Distance",(m_drive->GetFrontLeftEncoderRaw()));

        End(false);
        return true;
    }

    //if((abs(m_drive->GetFrontLeftEncoderRaw()))>abs(DistanceLeft)&&DistanceLeft!=0)
    if((DistanceRight > 0 && m_drive->GetFrontRightEncoderRaw() > EndRight) || (DistanceRight < 0 && m_drive->GetFrontRightEncoderRaw() < EndRight))
    {
        /*m_drive->SetBackSpeed(0);
        m_drive->SetFrontLeftSpeed(0);
        m_drive->SetFrontRightSpeed(0);*/

        //DriveToTarget=false;

        //ResetEncoders();

        //frc::SmartDashboard::PutNumber("EncoderRight Raw Distance",(m_drive->GetFrontRightEncoderRaw()));

        End(false);
        return true;
    }

    //if((abs(m_drive->GetFrontRightEncoderRaw()))>abs(DistanceRight)&&DistanceRight!=0)
    if((DistanceBack > 0 && m_drive->GetBackEncoderRaw() > EndBack) || (DistanceBack < 0 && m_drive->GetBackEncoderRaw() < EndBack))
    {
        /*m_drive->SetBackSpeed(0);
        m_drive->SetFrontLeftSpeed(0);
        m_drive->SetFrontRightSpeed(0);*/

        //DriveToTarget=false;

        //ResetEncoders();

        //frc::SmartDashboard::PutNumber("EncoderBack Raw Distance",(m_drive->GetBackEncoderRaw()));

        End(false);
        return true;
    }
    return false;
}