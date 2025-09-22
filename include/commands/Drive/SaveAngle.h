#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/CommandHandler.h"

class SaveAngle: public frc2::CommandHelper<frc2::CommandBase, SaveAngle>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit SaveAngle(DriveBase* drive,CommandHandler* cmd_h, bool reset, bool overwrite = false);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  CommandHandler* m_cmd_h;
  bool m_reset;
  bool m_overwrite;
};