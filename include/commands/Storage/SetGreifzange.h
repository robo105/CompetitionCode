#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/Storage.h"
#include "subsystems/CommandHandler.h"

class SetGreifzange: public frc2::CommandHelper<frc2::CommandBase, SetGreifzange>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit SetGreifzange(Storage* store, CommandHandler* cmd_h,bool greifen);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  Storage* m_storage;
  CommandHandler* m_cmd_h;
  bool m_greifen;

  //bool enable = false;
};