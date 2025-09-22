#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/Camera.h"
#include "subsystems/CommandHandler.h"

class EnableCamera: public frc2::CommandHelper<frc2::CommandBase, EnableCamera>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit EnableCamera(Camera* camera,CommandHandler* cmd_h, bool enable);

    void Initialize() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

  private:

  Camera* m_camera;
  CommandHandler* m_cmd_h;
  bool m_enable;
};