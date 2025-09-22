/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/SubsystemBase.h>
#include <frc2/command/CommandScheduler.h>
#include "frc/AnalogInput.h"
#include "frc/DigitalOutput.h"
#include <cmath>
#include "studica/TitanQuad.h"
#include "studica/TitanQuadEncoder.h"
//#include "AHRS.h"
#include "studica/Servo.h"

//frc::AnalogInput sharp{0};
//studica::Servo servo{2};
#include "frc/Joystick.h"
//frc::Joystick drivePad(0);
#include "frc/Ultrasonic.h"
#include "subsystems/DriveBase.h"

//frc::DigitalOutput abc{8};

//Constructors
//frc::Ultrasonic sonar{8, 9};  
//frc::Ultrasonic sonarRight{10, 11};

/*double getDistanceIR(void)
{
    return (pow(sharp.GetAverageVoltage(), -1.2045)) * 27.726;
}*/

/*double getDistanceUS(void)
{
    //return sonar.GetRangeInches();
    // or can use
    return sonar.GetRangeMM();
}*/

void setAngle(int angle)
{
  //servo.SetAngle(angle);
}

/*double GetJoystick(void)
{
    //double joy = drivePad.GetRawAxis(1);
    //if(fabs(joy) < 0.05)
      //  return 0.0;
    //else
        return joy;
}*/

//double test = 0;
//double Speed = 0;
//studica::TitanQuad motor1{42, 1};
//studica::TitanQuad motor2{42, 2};
//studica::TitanQuad motor3{42, 3};

//Constructor

/**
 * Sets the speed of a motor
 * <p>
 * @param speed range -1 to 1 (0 stop)
 */
/*void Example::SetMotorSpeed(double speed)
{
    motor.Set(speed);
}*/

void Robot::RobotInit() {
  //frc::SmartDashboard::PutNumber("Speed",test);
  
  //sonar.SetAutomaticMode(true);
  //sonar.SetEnabled(true);
  //Constructor
  

  //Use this function to set the servo angle
   //Range 0° - 300°
  //wpi::outs() << "example\n" << endl;
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
  //test++;
  //frc::SmartDashboard::PutNumber("Test3",Speed);
  //frc::SmartDashboard::PutNumber("Joystick",GetJoystick());
  //frc::SmartDashboard::PutNumber("IR",getDistanceIR());

  //sonar.Ping();
  /*frc::SmartDashboard::PutNumber("US Left enabled",sonar.IsEnabled());
  frc::SmartDashboard::PutNumber("US Left",sonar.GetRangeMM());
  frc::SmartDashboard::PutNumber("US Right",sonarRight.GetRangeMM());
  frc::SmartDashboard::PutNumber("US Left Inches",sonar.GetRangeInches());*/
  //abc.Set(true);
  frc::SmartDashboard::UpdateValues();
  
  //Speed = frc::SmartDashboard::GetNumber("Speed",0);
  //Example::SetMotorSpeed(1);
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }

  global::StoragePlace=0;
  global::SearchForLine=false;
}

/*double angle = 0;

double count=0;*/

void Robot::AutonomousPeriodic() {
  //frc::SmartDashboard::PutNumber("Motor", motor1.GetControllerTemp());
  //motor1.Set(1.0);
  //motor2.Set(1.0);
  //motor3.Set(1.0);
  /*count++;
  if(count>50)
  {
    count=0;
    if(angle<300)
    {
      setAngle(angle);
      angle+=10;
    }
  }*/
  
  
}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }

  m_teleopCommand = m_container.GetTeleopCommand();

  if (m_teleopCommand != nullptr) {
    m_teleopCommand->Schedule();
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {
  //setAngle(0);
  //motor1.Set(-1.0);
  //motor2.Set(-1.0);
  //motor3.Set(-1.0);
  //setAngle(0);
  //angle=0;
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {
  //setAngle(300);
  //motor.Set(0.5);
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
