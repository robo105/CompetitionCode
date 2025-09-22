#include "subsystems/Sensors.h"


frc::AnalogInput IR_Right{constant::IRSensors::RIGHT};
frc::AnalogInput IR_Left{constant::IRSensors::LEFT};

  //AHRS navX{frc::SPI::Port::kMXP};

studica::Cobra cobra{};

frc::Ultrasonic US_Left{constant::USSensors::LEFT_TRIG, constant::USSensors::LEFT_ECHO};
frc::Ultrasonic US_Right{constant::USSensors::RIGHT_TRIG, constant::USSensors::RIGHT_ECHO};

Sensors::Sensors()
{
    US_Left.SetAutomaticMode(true);
    US_Right.SetAutomaticMode(true);
}

int count_Sensors = 0;

#define COUNT_IR 5

double Sensors::GetIRLeftDistance()
{
    /*static double value = 0;
    static double valueOld=0;

    if(IR_LeftCount>COUNT_IR)
    {
        IR_LeftCount=0;
        value=IR_LeftDistance_help/COUNT_IR;
        IR_LeftDistance_help=0;
    }
    else
    {
        IR_LeftCount++;
        IR_LeftDistance_help+=(pow(IR_Left.GetAverageVoltage(), -1.2045) * 27.726);
    }*/

    const int RunningAverageCount = 16;               // Anzahl der in den Laufenden-Mittelwert aufgenommenen Messungen
    
    static double RunningAverageBuffer[RunningAverageCount];
    static int NextRunningAverage;

    double RawDistance = (pow(IR_Left.GetAverageVoltage(), -1.2045) * 27.726);
 
    RunningAverageBuffer[NextRunningAverage++] = RawDistance;
    if (NextRunningAverage >= aktuelleAnzahl)
    {
        NextRunningAverage = 0; 
    }
    float RunningAverageDistance = 0;
    for(int i=0; i< aktuelleAnzahl; ++i)
    {
        RunningAverageDistance += RunningAverageBuffer[i];
    }
    RunningAverageDistance /= aktuelleAnzahl;

    //double RunningAverageDistance = calculateAverage(RunningAverageBuffer,&NextRunningAverage,(pow(IR_Left.GetAverageVoltage(), -1.2045) * 27.726));

    /*value = valueOld*0.9+(pow(IR_Left.GetAverageVoltage(), -1.2045) * 27.726)*0.1;
    valueOld = value;*/

    if(RunningAverageDistance > 80)
    {
        return 80.0;
    }
    else if(RunningAverageDistance < 7)
    {
        return 7.0;
    }
    else
    {
        return RunningAverageDistance;
    }
}

double Sensors::GetIRRightDistance()
{

    /*double value = 
    value-=2;*/
    /*static double value=0;
    static double valueOld=0;

    if(IR_RightCount>COUNT_IR)
    {
        IR_RightCount=0;
        value=IR_RightDistance_help/COUNT_IR;
        IR_RightDistance_help=0;
    }
    else
    {
        IR_RightCount++;
        IR_RightDistance_help+=(pow(IR_Right.GetAverageVoltage(), -1.2045) * 27.726)-1;
    }*/

    const int RunningAverageCount = 16;               // Anzahl der in den Laufenden-Mettelwert aufgenommenen Messungen
    static double RunningAverageBuffer[RunningAverageCount];
    static int NextRunningAverage;

    double RawDistance = (pow(IR_Right.GetAverageVoltage(), -1.2045) * 27.726)-1;
 
    RunningAverageBuffer[NextRunningAverage++] = RawDistance;
    if (NextRunningAverage >= aktuelleAnzahl)
    {
        NextRunningAverage = 0; 
    }
    float RunningAverageDistance = 0;
    for(int i=0; i< aktuelleAnzahl; ++i)
    {
        RunningAverageDistance += RunningAverageBuffer[i];
    }
    RunningAverageDistance /= aktuelleAnzahl;
    
    /*value = valueOld*0.9+((pow(IR_Right.GetAverageVoltage(), -1.2045) * 27.726)-1)*0.1;
    valueOld = value;*/

    //double RunningAverageDistance = calculateAverage(RunningAverageBuffer,&NextRunningAverage,(pow(IR_Right.GetAverageVoltage(), -1.2045) * 27.726)-1);

    if(RunningAverageDistance > 80)
    {
        return 80.0;
    }
    else if(RunningAverageDistance < 7)
    {
        return 7.0;
    }
    else
    {
        return RunningAverageDistance;
    }
}

bool Sensors::IRDistanceSimilar()
{
    double IRDistance = IR_LeftDistance-IR_RightDistance;

    if(IRDistance > -1 && IRDistance < 1)
    {
        return true;
    }

    return false;
}

double Sensors::GetUSLeftDistance()
{
    static double value=0;
    static double valueOld=0;

    /*if(countUS_left>CountUS)
    {
        countUS_left=0;
        value=US_LeftDistanceHelp/CountUS;
        US_LeftDistanceHelp=0;
    }
    else
    {
        countUS_left++;
        US_LeftDistanceHelp+=US_Left.GetRangeMM();
    }*/

    const int RunningAverageCount = 16;               // Anzahl der in den Laufenden-Mettelwert aufgenommenen Messungen
    static double RunningAverageBuffer[RunningAverageCount];
    static int NextRunningAverage;

    double RawDistance = US_Left.GetRangeMM();
 
    RunningAverageBuffer[NextRunningAverage++] = RawDistance;
    if (NextRunningAverage >= aktuelleAnzahlUS)
    {
        NextRunningAverage = 0; 
    }
    float RunningAverageDistance = 0;
    for(int i=0; i< aktuelleAnzahlUS; ++i)
    {
        RunningAverageDistance += RunningAverageBuffer[i];
    }
    RunningAverageDistance /= aktuelleAnzahlUS;
    //double RunningAverageDistance = calculateAverage(RunningAverageBuffer,&NextRunningAverage,US_Left.GetRangeMM());

    // newvalue, oldValue
    // value = (oldValue * 7 + newvalue + 7)/8
    // oldValue = value;

    return RunningAverageDistance;

    /*value = valueOld*0.9+US_Left.GetRangeMM()*0.1;
    valueOld = value;*/
}

double Sensors::GetUSRightDistance()
{
    /*static double value=0;
    static double valueOld=0;*/

    /*if(countUS_right>CountUS)
    {
        countUS_right=0;
        value=US_RightDistanceHelp/CountUS;
        US_RightDistanceHelp=0;
    }
    else
    {
        countUS_right++;
        US_RightDistanceHelp+=US_Right.GetRangeMM();
    }*/

    const int RunningAverageCount = 16;               // Anzahl der in den Laufenden-Mettelwert aufgenommenen Messungen
    static double RunningAverageBuffer[RunningAverageCount];
    static int NextRunningAverage;

    //double RunningAverageDistance = calculateAverage(RunningAverageBuffer,&NextRunningAverage,US_Right.GetRangeMM());

    double RawDistance = US_Right.GetRangeMM();
 
    RunningAverageBuffer[NextRunningAverage++] = RawDistance;
    if (NextRunningAverage >= aktuelleAnzahlUS)
    {
        NextRunningAverage = 0; 
    }
    float RunningAverageDistance = 0;
    for(int i=0; i< aktuelleAnzahlUS; ++i)
    {
        RunningAverageDistance += RunningAverageBuffer[i];
    }
    RunningAverageDistance /= aktuelleAnzahlUS;

    // newvalue, oldValue
    // value = (oldValue * 7 + newvalue + 7)/8
    // oldValue = value;

    /*value = valueOld*0.9+US_Right.GetRangeMM()*0.1;
    valueOld = value;*/

    //return value;

    return RunningAverageDistance;
}

double Sensors::IRRightDistance()
{
    return IR_RightDistance;
}

double Sensors::IRLeftDistance()
{
    return IR_LeftDistance;
}

double Sensors::USRightDistance()
{
    return US_RightDistance;
}

double Sensors::USLeftDistance()
{
    return US_LeftDistance;
}

void Sensors::SetLineDirection(bool right, bool Line)
{
    if(right==true)
    {
        if(Line==true)
        {
            Line_Right_detected=true;
        }
        else
        {
            Line_Right_detected=false;
        }
    }
    else
    {
        if(Line==true)
        {
            Line_Left_detected=true;
        }
        else
        {
            Line_Left_detected=false;
        }
    }
}

int Sensors::GetLineDirection()
{
    if(Line_Right_detected==true&&Line_Left_detected==true)
    {
        return 3;
    }
    else if(Line_Right_detected==true&&Line_Left_detected==false)
    {
        return 2;
    }
    else if(Line_Right_detected==false&&Line_Left_detected==true)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

double countSensors_test = 0;

void Sensors::Periodic()
{
    count_Sensors++;
    US_LeftDistance=GetUSLeftDistance();
    US_RightDistance=GetUSRightDistance();

    IR_LeftDistance=GetIRLeftDistance();
    IR_RightDistance=GetIRRightDistance();

    //calculateCobra();
    CobraValue[0]=GetCobraValue(0);
    CobraValue[1]=GetCobraValue(1);
    CobraValue[2]=GetCobraValue(2);
    CobraValue[3]=GetCobraValue(3);

    if(global::CameraEnabled==true)
    {
        //CountUS=1;
        aktuelleAnzahl=4;
        aktuelleAnzahlUS=4;
    }
    else
    {
        aktuelleAnzahl=16;
        aktuelleAnzahlUS=16;
        //CountUS=3;
    }

    if(global::SearchForLine==true)
    {
        aktuelleAnzahlCobra=4;
    }
    else
    {
        aktuelleAnzahlCobra=4;
    }

    global::IR_Left_Distance=IR_LeftDistance;
    global::IR_Right_Distance=IR_RightDistance;
    global::US_Left_Distance=US_LeftDistance;
    global::US_Right_Distance=US_RightDistance;

    global::test_global+=1;

    if(constant::Debug::SENSORS)
    {
        frc::SmartDashboard::PutNumber("SensorsCount",count_Sensors);
        frc::SmartDashboard::PutNumber("Sensors Ultrasonic Distance Left", US_LeftDistance);
        frc::SmartDashboard::PutNumber("Sensors Ultrasonic Distance Right", US_RightDistance);
        frc::SmartDashboard::PutNumber("Sensors Infrarot Distance Left", IR_LeftDistance);
        frc::SmartDashboard::PutNumber("Sensors Infrarot Distance Right", IR_RightDistance);
        /*frc::SmartDashboard::PutNumber("Cobra 0", CobraValue[0]);
        frc::SmartDashboard::PutNumber("Cobra 1", CobraValue[1]);
        frc::SmartDashboard::PutNumber("Cobra 2", CobraValue[2]);
        frc::SmartDashboard::PutNumber("Cobra 3", CobraValue[3]);*/
        frc::SmartDashboard::PutNumber("Cobra 0", cobra.GetRawValue(0));
        frc::SmartDashboard::PutNumber("Cobra 1", cobra.GetRawValue(1));
        frc::SmartDashboard::PutNumber("Cobra 2", cobra.GetRawValue(2));
        frc::SmartDashboard::PutNumber("Cobra 3", cobra.GetRawValue(3));
    }
}

int countCobra = 0;
double Cobra[4] = {0};

#define COUNT_COBRA 4

double Sensors::GetCobraValue(int channel)
{
    const int RunningAverageCount = 30;               // Anzahl der in den Laufenden-Mettelwert aufgenommenen Messungen
    static double RunningAverageBuffer[RunningAverageCount][4];
    static int NextRunningAverage[4];

    //double RunningAverageDistance = calculateAverage(RunningAverageBuffer,&NextRunningAverage,US_Right.GetRangeMM());

    double RawDistance = cobra.GetRawValue(channel);
    frc::SmartDashboard::PutNumber("Cobra Value",RawDistance);
 
    RunningAverageBuffer[NextRunningAverage[channel]++][channel] = RawDistance;
    if (NextRunningAverage[channel] >= aktuelleAnzahlCobra)
    {
        NextRunningAverage[channel] = 0; 
    }
    float RunningAverageDistance = 0;
    for(int i=0; i< aktuelleAnzahlCobra; ++i)
    {
        RunningAverageDistance += RunningAverageBuffer[i][channel];
    }
    
    return RunningAverageDistance /= aktuelleAnzahlCobra;
}

void Sensors::calculateCobra()
{
    if(countCobra<COUNT_COBRA)
    {
        for(int i=0;i < 4;i++)
        {
            Cobra[i]+=cobra.GetRawValue(i);
        }

        countCobra++;
    }
    else
    {
        countCobra=0;
        CobraValue[0]=Cobra[0]/COUNT_COBRA;
        CobraValue[1]=Cobra[1]/COUNT_COBRA;
        CobraValue[2]=Cobra[2]/COUNT_COBRA;
        CobraValue[3]=Cobra[3]/COUNT_COBRA;

        for(int i=0;i<4;i++)
        {
            Cobra[i]=0;
        }
    }
}
    
float Sensors::GetCobra(int channel)
{
    return CobraValue[channel];
}

