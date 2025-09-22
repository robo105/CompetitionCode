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
#include <math.h>


class CommandHandler : public frc2::SubsystemBase {
 public:
  CommandHandler();
  void Periodic() override;
  
  void AddCommand(std::string name);
  
  void DeleteCommand(std::string name);
  

 private:

  void SortCommands();
  void PrintActiveCommands();
  #define SIZE 10
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  /*struct CommandArray
  {
      std::string name;
      int number;
  };*/

  //std::string Commands[SIZE];
};
