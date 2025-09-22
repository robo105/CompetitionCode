#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class DriveToCube: public frc2::CommandHelper<frc2::CommandBase, DriveToCube>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit DriveToCube(DriveBase* drive, Sensors* sensor, CommandHandler* cmd_h, double distanceToCube = constant::DISTANCE_TO_CUBE);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  CommandHandler* m_cmd_h;
  Sensors* m_sensors;
  double m_distanceToCube;
  //double m_position;
  //bool enable = 0;

  /*double actPosition=0;

  double helpPosition=0;
  double endPosition=0;*/

  //bool enable = false;
};