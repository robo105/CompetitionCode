#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class DriveToLine: public frc2::CommandHelper<frc2::CommandBase, DriveToLine>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit DriveToLine(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, double x, double y, double w, bool WatchAllTime = true);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  CommandHandler* m_cmd_h;
  Sensors* m_sensors;

  double m_x;
  double m_y;
  double m_w;

  bool m_WatchAllTime;

  bool driveBack=true;


  //double m_position;
  //bool enable = 0;

  /*double actPosition=0;

  double helpPosition=0;
  double endPosition=0;*/

  //bool enable = false;
};