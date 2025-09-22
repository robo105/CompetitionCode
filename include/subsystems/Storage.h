/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Constants.h"
#include "studica/TitanQuad.h"
#include "studica/TitanQuadEncoder.h"
//#include "AHRS.h"
#include "studica/Servo.h"
#include "frc/DigitalOutput.h"
#include <math.h>


class Storage : public frc2::SubsystemBase {
 public:
  Storage();
  void Periodic() override;
  double GetElevatorEncoder(void);
  void ResetElevatorEncoder(void);
  void SetSpeedElevator(double speed);
  void SetHigh(double high);

  void SetStoragePosition(int Position);
  void SetStorageAngle(double Angle);

  void SetGreifarm(double Position);
  void SetGreifzange(bool zu);
  void SetServo(double Position);
  double GetAngleGreifarm();
  double GetAngleGreifzange();
  double GetAngleLagerung();

  double GetLimitSwitch(bool oben);
  int GetFreeStorage();

  int GetElevatorRPM();

  double ElevatorPosition = 0;

 private:

  void HandleSpeedElevator();
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  studica::TitanQuad MotorElevator{constant::TITAN_ID, constant::StorageIDs::ELEVATOR};

  studica::TitanQuadEncoder EncoderElevator{MotorElevator, constant::StorageIDs::ELEVATOR, constant::Encoder::DIST_PER_TICK};

  studica::Servo Greifzange{constant::StorageIDs::GREIFZANGE};
  studica::Servo Greifarm {constant::StorageIDs::GREIFARM};

  double GreifarmWinkel = 0;
  double LagerungWinkel = 0;
  double GreifzangeWinkel = 0;

  double lastSpeed=0;

};
