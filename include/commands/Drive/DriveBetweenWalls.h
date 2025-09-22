#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class DriveBetweenWalls: public frc2::CommandHelper<frc2::CommandBase, DriveBetweenWalls>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit DriveBetweenWalls(DriveBase* drive, Sensors* sensor, CommandHandler* cmd_h);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  Sensors* m_sensors;
  CommandHandler* m_cmd_h;

  double actMeasure_r = 0;
  double lastMeasure_r = 0;

  double actMeasure_l = 0;
  double lastMeasure_l = 0;

  bool opened = false;

  double speedBack=0;
  double lastSpeedBack=0;

  int countLastMeasure = 0;
};