#include "controller/OI.h"
#include "frc/Joystick.h"
#include <cmath>

frc::Joystick controller(DRIVE_USB_PORT);

double OI::GetRightX(void)
{
    return controller.GetRawAxis(J_RIGHT_X);
}

double OI::GetRightY(void)
{
    return controller.GetRawAxis(J_RIGHT_Y);
}

double OI::GetLeftX(void)
{
    return controller.GetRawAxis(J_LEFT_X);
}

double OI::GetLeftY(void)
{
    return controller.GetRawAxis(J_LEFT_Y);
}

double OI::GetRightZ(void)
{
    return controller.GetRawAxis(J_RIGHT_Z);
}

double OI::GetLeftZ(void)
{
    return controller.GetRawAxis(J_LEFT_Z);
}

bool OI::GetButton(int Button)
{
    return controller.GetRawButton(Button);
}

bool OI::GetButtonPressed(int Button)
{
    return controller.GetRawButtonPressed(Button);
}


/*
Analog:
Right X:    3
Right Y:    4
Left X :    0
Left Y :    1
Gas Rechts: 5
Gas Links:  2
*/