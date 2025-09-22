#include "frc2/command/CommandBase.h"
#include "frc2/command/CommandHelper.h"

#include "subsystems/DriveBase.h"
#include "subsystems/Sensors.h"
#include "subsystems/CommandHandler.h"

class PositionBeforeCube: public frc2::CommandHelper<frc2::CommandBase, PositionBeforeCube>
{
    public:
    /**
     * Creates a new ExampleCommand.
     *
     * @param subsystem The subsystem used by this command.
     */
    explicit PositionBeforeCube(DriveBase* drive,CommandHandler* cmd_h);

    void Initialize() override;
    void Execute() override;
    void End(bool interrupted) override;
    bool IsFinished() override;

  private:

  bool GetInverseMatrix();


  DriveBase* m_drive;
  Sensors* m_sensors;
  CommandHandler* m_cmd_h;

  double m_x=0;
  double m_y=0;
  double m_w=0;

  double m_mat[3][3]={0};
  double m_inv_mat[3][3]={0};

  double countDriveToPositionTest = 0;

  double DistanceLeft=0, DistanceRight=0, DistanceBack =0;
  double SpeedMultiLeft=0, SpeedMultiRight=0, SpeedMultiBack =0;

  double StartBack = 0, StartFrontLeft=0, StartFrontRight=0;

  int EndBack = 0, EndLeft = 0, EndRight = 0;
};