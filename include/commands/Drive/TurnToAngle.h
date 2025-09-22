#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class TurnToAngle: public frc2::CommandHelper<frc2::CommandBase, TurnToAngle>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit TurnToAngle(DriveBase* drive,CommandHandler* cmd_h, double angle, double speed=50, double range = 1);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  CommandHandler* m_cmd_h;
  double m_angle;
  double m_range;
  double m_speed;

  double angle_help;

  bool turn_direction = false;

  int count = 0;

  double Multi = 1;

};