#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class FollowWall: public frc2::CommandHelper<frc2::CommandBase, FollowWall>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit FollowWall(DriveBase* drive, Sensors* sensor,CommandHandler* cmd_h, bool RightSide, double Distance, int SensorID, bool StopAtTwoWalls = false, double DistanceToWall = constant::DISTANCE_TO_WALL);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:

  double LimitValue(double value, double Bottom, double Top);

  DriveBase* m_drive;
  Sensors* m_sensors;
  CommandHandler* m_cmd_h;

  bool m_RightSide = false;
  double m_distance = 0;
  int m_SensorID = -1;

  bool m_StopAtTwoWalls = false;
  double m_DistanceToWall = 0;

  double actMeasure = 0;
  double lastMeasure = 0;

  bool opened = false;

  double speedBack=0;
  double lastSpeedBack=0;

  double startingDistance=0;

  double MeasuredDistance = 0;

  double LastDistance=0;
  double LastError=0;
  
  //double LastSpeedSet=0;
};