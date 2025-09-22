#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class TurnToWall: public frc2::CommandHelper<frc2::CommandBase, TurnToWall>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit TurnToWall(DriveBase* drive,Sensors* sensor, CommandHandler* cmd_h);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:
  DriveBase* m_drive;
  Sensors* m_sensor;
  CommandHandler* m_cmd_h;

  double IRLeft_help=0;
  double IRRight_help=0;

  double IRLeft=0;
  double IRRight=0;
  
  int CountIR = 0;
  int MAXIR = 1;

  bool turn_direction = false;

  //int count = 0;

  double Multi = 1;

};