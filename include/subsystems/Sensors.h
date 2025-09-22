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
//#include "AHRS.h"
#include "frc/AnalogInput.h"
#include "frc/Ultrasonic.h"
#include "studica/Cobra.h"
#include <math.h>


class Sensors : public frc2::SubsystemBase {
 public:
  Sensors();
  void Periodic() override;

  double IRRightDistance();
  double IRLeftDistance();

  double USRightDistance();
  double USLeftDistance();

  float GetCobra(int channel);

  int GetLineDirection();
  void SetLineDirection(bool right, bool Line);

  bool IRDistanceSimilar();
  
  //float GetYaw();

  double Line_Position_w;
  double Line_Position_x;


 private:

  double GetIRRightDistance();
  double GetIRLeftDistance();

  double GetUSLeftDistance();
  double GetUSRightDistance();

  void calculateCobra();

  double GetCobraValue(int i);

  double calculateAverage(double buffer[16],int* runningAverage, double newValue);
  //void InitIMU();
  
  //double getDistanceIR2(void);
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  
  //frc::AnalogInput IR_Back{0};
  //frc::AnalogInput IR_Back{constant::IRSensors::BACK};

  /*frc::Ultrasonic US_Left{constant::USSensors::LEFT_TRIG, constant::USSensors::LEFT_ECHO};
  frc::Ultrasonic US_Right{constant::USSensors::RIGHT_TRIG, constant::USSensors::RIGHT_ECHO};

  studica::Cobra cobra{};*/

  int aktuelleAnzahl=16;

  int aktuelleAnzahlUS=16;
  int aktuelleAnzahlCobra = 4;

  double US_LeftDistance = 0;
  double US_LeftDistanceHelp = 0;

  int countUS_left = 0;
  int countUS_right = 0;

  double US_RightDistance = 0;
  double US_RightDistanceHelp = 0;

  double IR_RightDistance = 0;
  double IR_LeftDistance = 0;

  double IR_LeftDistance_help=0;
  int IR_LeftCount=0;

  double IR_RightDistance_help=0;
  int IR_RightCount=0;

  double CobraValue[4] = {0};

  bool Line_Left_detected = false;
  bool Line_Right_detected = false;

  int CountUS = 3;
};
