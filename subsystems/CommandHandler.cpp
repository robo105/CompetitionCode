/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CommandHandler.h"
#include <cmath>

CommandHandler::CommandHandler() {
    /*for(int i=0;i<SIZE;i++)
    {
        Commands[i]="";
        //Commands[i].number=-1;
    }*/
}

void CommandHandler::SortCommands()
{
    
}

void CommandHandler::AddCommand(std::string name)
{
    /*for(int i=0;i<SIZE;i++)
    {
        if(Commands[i]=="NONE")
        {
            Commands[i]=name;

            break;
        }
    }*/
}

void CommandHandler::DeleteCommand(std::string name)
{
    /*for(int i=0;i<SIZE;i++)
    {
        if(Commands[i]==name)
        {
            Commands[i]="NONE";
        }
    }*/
}

void CommandHandler::PrintActiveCommands()
{
    //frc::SmartDashboard::PutStringArray("Active Commands",Commands);
}

void CommandHandler::Periodic() {
  PrintActiveCommands();
}
