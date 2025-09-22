#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/Storage.h"
#include "subsystems/CommandHandler.h"

class InitElevator: public frc2::CommandHelper<frc2::CommandBase, InitElevator>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit InitElevator(Storage* store,CommandHandler* cmd_h);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  Storage* m_storage;
  CommandHandler* m_cmd_h;
  double m_position;
  //bool enable = 0;

  /*double actPosition=0;

  double helpPosition=0;
  double endPosition=0;*/

  //bool enable = false;
};