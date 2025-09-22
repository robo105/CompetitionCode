/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TestDrive.h"
//#include "commands/TestCommand.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Storage.h"
#include "subsystems/Sensors.h"
#include "subsystems/Camera.h"
#include "controller/OI.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/TimedRobot.h>
#include "frc/shuffleboard/Shuffleboard.h"

#include "frc2/command/Subsystem.h"
#include "frc2/command/CommandScheduler.h"

#include "frc2/command/RunCommand.h"
#include "frc2/command/InstantCommand.h"

#include "frc/SerialPort.h"

frc::SerialPort UART(115200,frc::SerialPort::Port::kUSB1,8);

TestDrive::TestDrive(DriveBase* drive, OI* oi, Storage* storage, Sensors* sensors, Camera* camera, CommandHandler* cmd_h) //: m_subsystem{subsystem} 
{
    AddRequirements({drive, oi, storage, sensors, camera,m_cmd_h});
    m_drive = drive;
    m_oi = oi;
    m_storage = storage;
    m_sensors = sensors;
    m_camera = camera;
    m_cmd_h = cmd_h;
}


void TestDrive::Initialize() {
    //frc2::Trigger::Trigger(pickDice());
    //frc2::Trigger::Trigger()

    //frc2::Trigger trigger;
    
    //frc2::CommandScheduler::Schedule(&pick);
   /*m_drive->SetOmptimizeLevel(0);
   m_cmd_h->AddCommand("TestDrive");*/

   char bufferLength=0x00;
   char bufferType=0x02;
   //char abc[10];
   char abc;
   int count=0;

   UART.SetReadBufferSize(20);
   UART.SetTimeout(5);
   UART.SetWriteBufferMode(frc::SerialPort::WriteBufferMode::kFlushOnAccess);
   UART.DisableTermination();

   
   //UART.Read(bufferPointer,150);

   /*while(UART.Read(&abc,1)>0)
   {
       count++;
       frc::SmartDashboard::PutNumber("UART Read",count);
   }*/
   
   //UART.Read(abc,8);

   //frc::SmartDashboard::PutString("UART test",abc);
}

double count_TestDrive = 0;
double count_TestDrive_last = 0;
bool resetEncoders = false;
int position = 0;
int positionServo = 0;

double TestInput = 0;

double countButtonY = 0;

double countLagerung = 0;

double countStor=0;
double AngleStor = 0;

bool CameraEnabled = false;

double speed_test = 0;

void TestDrive::Execute()
{
    count_TestDrive++;

    /*frc::Shuffleboard::GetTab("SmartDashboard")
     .Add("Pi", TestInput);*/

    countStor++;
    if(countStor>50)
    {
        countStor=0;
        if(AngleStor<300)
        {
        //m_storage->SetStorageAngle(AngleStor);
        AngleStor+=10;
        }
    }

    /*nt::GenericEntry test* = frc::Shuffleboard::GetTab("SmartDashboard")
    .Add("TestInput", TestInput)
    .WithWidget(frc::BuiltInWidgets::kNumberSlider) // specify the widget here
    .GetEntry();*/


    /*frc::SmartDashboard::PutNumber("CountTestDrive", count_TestDrive);
    frc::SmartDashboard::PutNumber("Right X", m_oi->GetRightX());
    frc::SmartDashboard::PutNumber("Right Y", m_oi->GetRightY());
    frc::SmartDashboard::PutNumber("Left X",m_oi->GetLeftX());
    frc::SmartDashboard::PutNumber("Left Y",m_oi->GetLeftY());
    frc::SmartDashboard::PutNumber("Left Z",m_oi->GetLeftZ());
    frc::SmartDashboard::PutNumber("Right Z",m_oi->GetRightZ());*/

    //frc::SmartDashboard::PutNumber("Yaw",m_sensors->GetYaw());

    frc::SmartDashboard::PutNumber("RPM Front Left",m_drive->GetFrontLeftRPM());
    frc::SmartDashboard::PutNumber("RPM Front Right",m_drive->GetFrontRightRPM());
    frc::SmartDashboard::PutNumber("RPM Back",m_drive->GetBackRPM());
     

    //m_drive->HolonomicDrive(-(m_oi->GetLeftX()),m_oi->GetLeftY(),m_oi->GetRightX());
    //m_drive->SetHandleIMU();
    global::savedAngle=m_drive->GetYaw();

    m_drive->HolonomicDriveWithoutOptimize(m_oi->GetLeftX(),m_oi->GetLeftY(),m_oi->GetRightX());

    //m_drive->ActivateOmptimize(true);
    
    
    //frc::SmartDashboard::PutNumber("J Left",m_oi->GetLeftX());
    frc::SmartDashboard::PutNumber("RPM Left",m_drive->GetFrontLeftRPM());
    frc::SmartDashboard::PutNumber("RPM Right",m_drive->GetFrontRightRPM());
    frc::SmartDashboard::PutNumber("RPM Back",m_drive->GetBackRPM());

    m_storage->SetSpeedElevator(m_oi->GetRightY());

    //frc::SmartDashboard::PutNumber("Encoder Elevator",m_storage->GetElevatorEncoder());
    //m_drive->SetSpeed(0,1.0);
    //m_drive->SetSpeed(1,1.0);
    //m_drive->SetSpeed(2,1.0);
    /*frc::SmartDashboard::GetBoolean("ResetEncoder",resetEncoders);
    frc::SmartDashboard::PutBoolean("ResetEncoder_test",resetEncoders);
    frc::SmartDashboard::PutNumber("ResetEncoders last Presses", count_TestDrive_last);*/
    if(resetEncoders==true)
    {
        count_TestDrive_last = count_TestDrive;
        m_drive->ResetEncoders();
    }

    if(m_oi->GetButtonPressed(BTN_B))
    {
        if(position<constant::Lagerung::MAX_LAGERUNG)
        {
            position++;
            
        }

        /*speed_test++;
        m_drive->SetFrontLeftSpeed(speed_test);
        m_drive->SetFrontRightSpeed(speed_test);
        m_drive->SetBackSpeed(speed_test);*/
        //m_storage->SetStorageAngle(0);
    }

    if(m_oi->GetButtonPressed(BTN_A))
    {
        if(position>0)
        {
            position--;
        }

        /*speed_test--;
        m_drive->SetFrontLeftSpeed(speed_test);
        m_drive->SetFrontRightSpeed(speed_test);
        m_drive->SetBackSpeed(speed_test);*/
        //m_storage->SetStorageAngle(300);
    }

    frc::SmartDashboard::PutNumber("speed_test",speed_test);

    /*if(m_oi->GetButtonPressed(BTN_X))
    {
        //BUG: Command lässt sich nicht ausführen
        //frc::SmartDashboard::PutString("TestString",abcd);
        m_drive->ResetEncoders();
        //frc2::CommandScheduler::GetInstance().Schedule(&test);
    }*/

    frc::SmartDashboard::PutNumber("Y Displacement",m_drive->GetYDisplacementIMU());

    if(m_oi->GetButtonPressed(BTN_Y))
    {
        //m_drive->DriveToPosition(100.0,0,0);
        //m_drive->SetFrontLeftSpeed(50.0);
        //m_drive->SetFrontRightSpeed(50.0);
        //m_drive->SetBackSpeed(50.0);
        /*frc::SmartDashboard::PutNumber("Color Cube found",m_camera->GetDetectedColor());

        m_drive->ResetEncoders();
        m_drive->ResetIMU();
        m_drive->SetHandleIMU();
        m_drive->ResetDisplacement();
        //m_drive->HolonomicDrive(50,0,0);
        countButtonY++;
        frc::SmartDashboard::PutNumber("Count Button Y",countButtonY);*/
        /*m_drive->SetOmptimizeLevel(1);
        m_drive->HolonomicDrive(0,25,0);*/

        char buffer[2]={0x00,0x02};

        UART.Write(buffer,2);
    }

    if(m_oi->GetButtonPressed(BTN_X))
    {

        //m_drive->HolonomicDrive(0,0,0);

        //m_drive->SetOmptimizeLevel(0);
        //m_drive->DriveToPosition(100.0,0,0);
        /*m_drive->SetFrontLeftSpeed(0.0);
        m_drive->SetFrontRightSpeed(0.0);
        m_drive->SetBackSpeed(0.0);
        countButtonY++;
        frc::SmartDashboard::PutNumber("Count Button Y",countButtonY);*/
        //m_drive->HolonomicDrive(0,0,0);
        //CameraEnabled=!CameraEnabled;

        

        //m_camera->TakeSinglePicture();
        //TakeSinglePicture();

        /*for (int color = 0;color < 3; color++)
        {
            SetColorDetection(color);
        
            ProcessSinglePicture();
            if(Color_detected==true)
            {
                detectedColor = color;
                break;
            }
        }*/
        //m_camera->TakePictureForQRCode();
        //m_camera->SearchforCube();
        //m_camera->TakeSinglePicture();
        //m_camera->EnableCamera(CameraEnabled);
        
        int numberOfBytes = UART.GetBytesReceived();
        frc::SmartDashboard::PutNumber("Bytes received",numberOfBytes);

        uint8_t bufferRead2[200];
        char bufferRead[200];
        //char* bufferPointer = bufferRead;

        UART.Read(bufferRead,numberOfBytes);
        for(int i=0;i<200;i++)
        {
            bufferRead2[i] = bufferRead[i];
        }
        fstream file;

        file.open("/home/pi/Desktop/UART", ios_base::out | ios_base::app);

        file << bufferRead2;
        //frc::SmartDashboard::PutNumberArray("UART received",)

        
    }

    //m_storage->SetStorageAngle(0);

    frc::SmartDashboard::PutNumber("Matrix X Distance Raw",m_drive->GetXDistanceRaw());
    frc::SmartDashboard::PutNumber("Matrix Y Distance Raw",m_drive->GetYDistanceRaw());
    frc::SmartDashboard::PutNumber("Matrix Y Distance",m_drive->GetYDistance());
    frc::SmartDashboard::PutNumber("Matrix W Distance Raw",m_drive->GetWDistanceRaw());

    //frc::SmartDashboard::PutNumber("Position",position);
    //frc::SmartDashboard::GetNumber("PositionServo",positionServo);
    //frc::SmartDashboard::PutNumber("PositionServo_Test",positionServo);
    m_storage->SetStoragePosition(position);
    //m_storage->SetServo(position);

    countLagerung++;
    
    //m_storage->SetStorageAngle(countLagerung);

    //frc::SmartDashboard::PutNumber("Servo Greifzange",m_storage->GetAngleGreifzange());

    if(m_oi->GetButtonPressed(BTN_LB))
    {
        m_storage->SetGreifzange(false);
        //m_storage->SetServo(100.0);
    }

    //m_storage->SetStorageAngle(0);

    if(m_oi->GetButtonPressed(BTN_RB))
    {
        m_storage->SetGreifzange(true);
    }

    /*if(m_storage->GetAngleGreifarm()<constant::Greifarm::OBEN && m_storage->GetAngleGreifarm()>constant::Greifarm::UNTEN)
    {
        m_storage->SetGreifarm((m_storage->GetAngleGreifarm())+(m_oi->GetRightZ()+1)-(m_oi->GetRightZ()+1));
    }
    else */if(m_storage->GetAngleGreifarm()<constant::Greifarm::OBEN && (m_oi->GetRightZ()+1) > 0.05)
    {
        frc::SmartDashboard::PutNumber("Greifarm addieren",(m_storage->GetAngleGreifarm())+(m_oi->GetRightZ()+1));
        m_storage->SetGreifarm((m_storage->GetAngleGreifarm())+(m_oi->GetRightZ()+1));
        //m_storage->SetServo(((m_storage->GetAngleGreifzange())+(m_oi->GetRightZ()+1)));
    }
    else if(m_storage->GetAngleGreifarm()>constant::Greifarm::MINIMUM && (m_oi->GetLeftZ()+1) > 0.05)
    {
        frc::SmartDashboard::PutNumber("Greifarm subtrahieren",(m_storage->GetAngleGreifarm())-(m_oi->GetLeftZ()+1));
        m_storage->SetGreifarm((m_storage->GetAngleGreifarm())-(m_oi->GetLeftZ()+1));
        //m_storage->SetServo(((m_storage->GetAngleGreifzange())-(m_oi->GetLeftZ()+1)));
    }

    //pickDice.OnTrue()

    /*frc::SmartDashboard::PutNumber("Distance IS Front", m_sensors->GetIRFRontDistance());
    frc::SmartDashboard::PutNumber("Distance IS Back", m_sensors->GetIRBackDistance());

    frc::SmartDashboard::PutNumber("Distance US Left",m_sensors->GetUSLeftDistance());
    frc::SmartDashboard::PutNumber("Distance US Right",m_sensors->GetUSRightDistance());*/

    /*frc::SmartDashboard::PutNumber("Cobra0",m_sensors->GetCobra(0));
    frc::SmartDashboard::PutNumber("Cobra1",m_sensors->GetCobra(1));
    frc::SmartDashboard::PutNumber("Cobra2",m_sensors->GetCobra(2));
    frc::SmartDashboard::PutNumber("Cobra3",m_sensors->GetCobra(3));

    frc::SmartDashboard::PutNumber("Limit Switch Oben",m_storage->GetLimitSwitch(true));
    frc::SmartDashboard::PutNumber("Limit Switch Unten",m_storage->GetLimitSwitch(false));

    frc::SmartDashboard::PutNumber("Servo Winkel Lagerung",m_storage->GetAngleLagerung());
    frc::SmartDashboard::PutNumber("Servo Winkel Greifarm",m_storage->GetAngleGreifarm());
    frc::SmartDashboard::PutNumber("Servo Winkel Greifzange",m_storage->GetAngleGreifzange());*/
    frc::SmartDashboard::UpdateValues();
}


void TestDrive::End(bool interrupted)
{
    m_cmd_h->DeleteCommand("TestDrive");
}

bool TestDrive::IsFinished()
{
    return false;
}