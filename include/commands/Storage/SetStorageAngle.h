#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/Storage.h"
#include "subsystems/CommandHandler.h"

class SetStorageAngle: public frc2::CommandHelper<frc2::CommandBase, SetStorageAngle>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit SetStorageAngle(Storage* store, CommandHandler* cmd_h,double angle);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  Storage* m_storage;
  CommandHandler* m_cmd_h;
  double m_angle;

  double actPosition=0;

  double helpPosition=0;
  double endPosition=0;

  bool enable = false;
};