#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/Storage.h"
#include "subsystems/CommandHandler.h"

class ReleaseCube: public frc2::CommandHelper<frc2::CommandBase, ReleaseCube>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit ReleaseCube(Storage* store,CommandHandler* cmd_h);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  Storage* m_storage;
  CommandHandler* m_cmd_h;
  /*double actPosition=0;

  double helpPosition=0;
  double endPosition=0;*/

  //bool enable = false;
};