#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Camera.h"
#include "subsystems/Sensors.h"
#include "subsystems/Storage.h"
#include "subsystems/CommandHandler.h"

class DriveUntilCube: public frc2::CommandHelper<frc2::CommandBase, DriveUntilCube>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit DriveUntilCube(DriveBase* drive,Sensors* sensor, Camera* camera, Storage* m_storage, CommandHandler* cmd_h,bool direction_right);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  CommandHandler* m_cmd_h;
  Camera* m_camera;
  Sensors* m_sensor;
  Storage* m_storage;
  bool m_direction_right;

  double SpeedY = 0;
};