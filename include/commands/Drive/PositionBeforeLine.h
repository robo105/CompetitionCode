#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class PositionBeforeLine: public frc2::CommandHelper<frc2::CommandBase, PositionBeforeLine>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit PositionBeforeLine(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  Sensors* m_sensor;
  CommandHandler* m_cmd_h;

  int count = 0;

};