/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>
#include <frc/DigitalOutput.h>
#include "Constants.h"
#include "studica/TitanQuad.h"
#include "studica/TitanQuadEncoder.h"
#include "AHRS.h"
#include <math.h>

#include "subsystems/Sensors.h"
#include "subsystems/Storage.h"


class DriveBase : public frc2::SubsystemBase {
 public:
  DriveBase();
  void Periodic() override;
  double GetFrontLeftEncoder(void);
  double GetFrontRightEncoder(void);
  double GetBackEncoder(void);

  double GetFrontLeftEncoderRaw(void);
  double GetFrontRightEncoderRaw(void);
  double GetBackEncoderRaw(void);

  void ResetEncoders(void);
  void SetSpeed(int motor, double speed);
  void HolonomicDrive(double xSpeed, double ySpeed, double wSpeed, bool enable_ow = false);
  void HolonomicDriveWithoutOptimize(double xSpeed, double ySpeed, double wSpeed);

  double GetXDistance(void);
  double GetXDistanceRaw(void);

  double GetYDistance(void);
  double GetYDistanceRaw(void);
  double GetYEncoder(void);

  double GetWDistance(void);
  double GetWDistanceRaw(void);

  bool GetInverseMatrix();

  int GetFrontLeftRPM();
  int GetFrontRightRPM();
  int GetBackRPM();

  void DriveToPosition(double x, double y, double w);

  void SetOmptimizeLevel(int level);

  /*void SetFrontLeftSpeed(double speed);
  void SetFrontRightSpeed(double speed);
  void SetBackSpeed(double speed);

  void OptimizeFrontLeftSpeed();
  void OptimizeFrontRightSpeed();
  void OptimizeBackSpeed();*/

  void SetFrontLeftSpeed(double speed, bool enable_ow = false);
  void SetFrontRightSpeed(double speed, bool enable_ow = false);
  void SetBackSpeed(double speed, bool enable_ow = false);

  void SetPositionX(double x);
  double GetPositionX();

  float GetYaw();
  float GetYDisplacementIMU();
  void ResetDisplacement();
  void SetHandleIMU();
  double GetStartingAngle();  
  void ResetIMU();

  void HandelSpeeds();

 private:
  double mat[3][3]={0};
  double inv_mat[3][3]={0};
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  studica::TitanQuad MotorLeft{constant::TITAN_ID, constant::DriveTrainIDs::FRONT_LEFT};
  studica::TitanQuad MotorRight{constant::TITAN_ID, constant::DriveTrainIDs::FRONT_RIGHT};
  studica::TitanQuad MotorBack{constant::TITAN_ID, constant::DriveTrainIDs::BACK};

  AHRS navX{frc::SPI::Port::kMXP};

  studica::TitanQuadEncoder EncoderLeft{MotorLeft, constant::DriveTrainIDs::FRONT_LEFT, constant::Encoder::DIST_PER_TICK};
  studica::TitanQuadEncoder EncoderRight{MotorRight, constant::DriveTrainIDs::FRONT_RIGHT, constant::Encoder::DIST_PER_TICK};
  studica::TitanQuadEncoder EncoderBack{MotorBack, constant::DriveTrainIDs::BACK, constant::Encoder::DIST_PER_TICK};

  void OptimizeFrontLeftSpeed();
  void OptimizeFrontRightSpeed();
  void OptimizeBackSpeed();

  void OptimizeFrontLeftSpeedPControl();
  void OptimizeFrontRightSpeedPControl();
  void OptimizeBackSpeedPControl();

  void SetSpeedRight(double speed, bool enable_ow = false);
  void SetSpeedLeft(double speed, bool enable_ow = false);
  void SetSpeedBack(double speed, bool enable_ow = false);

  void HandelDriveToPosition();
  void HandleIMU();
  void HandleDistanceToSmall();
  
  double CalculateIMU(double speed);

  double SpeedAimLeft=0;
  double SpeedAimRight=0;
  double SpeedAimBack=0;

  double SpeedSetLeft=0;
  double SpeedSetRight=0;
  double SpeedSetBack=0;

  bool EnableBack=false;
  bool EnableLeft=false;
  bool EnableRight=false;

  double Position_x = 0;
  double Position_y = 0;

  bool noSpeed=true;
  double startingAngle=0;

  bool DistanceToSmall=false;
  bool DistanceToSmall_Last=false;
  double DistanceToSmallSensor = constant::Sensor_IDs::NONE;

  bool EnableMotorsOW=false;
};
