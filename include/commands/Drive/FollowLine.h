#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class FollowLine: public frc2::CommandHelper<frc2::CommandBase, FollowLine>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit FollowLine(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  Sensors* m_sensors;
  CommandHandler* m_cmd_h;

  bool opened = false;

  double speedBack=0;
  double lastSpeedBack=0;

  double lastMeasure[4]={0};
  double actMeasure[4]={0};
};