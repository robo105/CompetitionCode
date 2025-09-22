#pragma once
#include <frc2/command/SubsystemBase.h>

class OI : public frc2::SubsystemBase
{
    public:
        double GetRightX(void);
        double GetRightY(void);
        double GetLeftX(void);
        double GetLeftY(void);
        double GetRightZ(void);
        double GetLeftZ(void);
        
        bool GetButton(int Button);
        bool GetButtonPressed(int Button);

    private:
        #define DRIVE_USB_PORT  0

        #define J_LEFT_X    0
        #define J_LEFT_Y    1
        #define J_LEFT_Z    2

        #define J_RIGHT_X    3  //2
        #define J_RIGHT_Y   4   //3
        #define J_RIGHT_Z   5

        #define BTN_B   2
        #define BTN_A   1
        #define BTN_X   3
        #define BTN_Y   4

        #define BTN_LB  5
        #define BTN_RB  6
        
        /*#define BTN_RIGHT   12
        #define BTN_LEFT    13
        #define BTN_UP      14
        #define BTN_DOWN    15*/
};