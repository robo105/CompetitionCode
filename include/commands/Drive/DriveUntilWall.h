#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class DriveUntilWall: public frc2::CommandHelper<frc2::CommandBase, DriveUntilWall>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit DriveUntilWall(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, double x, double y, double w, int Sensor_ID, double DistanceToWall = constant::DISTANCE_TO_WALL);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  CommandHandler* m_cmd_h;
  Sensors* m_sensors;

  double m_Distance;

  double m_x;
  double m_y;
  double m_w;

  int m_Sensor_ID;

  double Distance = 0;
  //double m_position;
  //bool enable = 0;

  /*double actPosition=0;

  double helpPosition=0;
  double endPosition=0;*/

  //bool enable = false;
};