/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>

#include "commands/ExampleCommand.h"
#include "commands/StoreAndDestoreCommand.h"
#include "commands/TestCommand.h"
#include "subsystems/ExampleSubsystem.h"
#include "commands/TestDrive.h"
#include "controller/OI.h"
#include "subsystems/DriveBase.h"
#include "subsystems/Storage.h"
#include "subsystems/Sensors.h"
#include "subsystems/Camera.h"
#include "subsystems/CommandHandler.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */

class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();
  frc2::Command* GetTeleopCommand();

 private:
  // The robot's subsystems and commands are defined here...
  DriveBase drive;
  OI m_oi;
  Storage storage;
  Sensors sensor;
  Camera camera;
  CommandHandler cmd_h;
  
  ExampleSubsystem m_subsystem;
  //ExampleCommand m_autonomousCommand;
  StoreAndDestoreCommand m_autonomousCommand;
  //TestCommand m_autonomousCommand;
  
  TestDrive m_teleopCommand;

  void ConfigureButtonBindings();
};
