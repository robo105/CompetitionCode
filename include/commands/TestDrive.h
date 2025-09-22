/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "frc2/command/SelectCommand.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Storage.h"
#include "controller/OI.h"
#include "subsystems/Sensors.h"
#include "subsystems/Camera.h"
#include "subsystems/CommandHandler.h"


/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class TestDrive: public frc2::CommandHelper<frc2::CommandBase, TestDrive>
{
  public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit TestDrive(DriveBase* drive, OI* oi, Storage* storage, Sensors* sensors,Camera* camera, CommandHandler* cmd_h);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
    //void PositionLine();

    DriveBase* m_drive;
    Storage* m_storage;
    OI* m_oi;
    Sensors* m_sensors;
    Camera* m_camera;
    CommandHandler* m_cmd_h;
};


