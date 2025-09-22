#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Camera.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class PositionBeforeCubeCalculate: public frc2::CommandHelper<frc2::CommandBase, PositionBeforeCubeCalculate>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit PositionBeforeCubeCalculate(DriveBase* drive, Camera* camera, Sensors* sensor,CommandHandler* cmd_h, bool vonOben);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  CommandHandler* m_cmd_h;
  Camera* m_camera;
  Sensors* m_sensor;

  double DistanceFront = 0;
  double Position_x = 0;
  double Position_y = 0;
  bool m_vonOben;

};