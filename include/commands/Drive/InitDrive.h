#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/CommandHandler.h"

class InitDrive: public frc2::CommandHelper<frc2::CommandBase, InitDrive>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit InitDrive(DriveBase* drive,CommandHandler* cmd_h, int optimize_level);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  CommandHandler* m_cmd_h;
  int m_optimize;

};