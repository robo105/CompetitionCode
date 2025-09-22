#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/Storage.h"
#include "subsystems/CommandHandler.h"

class SetStorePosition: public frc2::CommandHelper<frc2::CommandBase, SetStorePosition>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit SetStorePosition(Storage* store,CommandHandler* cmd_h, int position);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  Storage* m_storage;
  CommandHandler* m_cmd_h;
  int m_position;

  double actPosition=0;

  double helpPosition=0;
  double endPosition=0;

  bool enable = false;
};