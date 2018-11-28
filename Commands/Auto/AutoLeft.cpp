/******************************************************************************
	Description:	Implements the AutoCenter command.

	Command:		AutoCenter

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <WPILib.h>
#include <RobotMain.h>
#include "AutoLeft.h"
#include <Commands/ArmPosition/HomeArm.h>
#include <Commands/ArmPosition/MoveArm.h>
#include <Commands/Gripper/Eject.h>
#include <Commands/Auto/Subcommands/DrivetrainFollowPath.h>

AutoLeft::AutoLeft()
{
	// 1. Home Arm
	// 2. Decide where to go, drive to the Scale and raise arm to 80 degrees (this may need tweaking)
	// 3. Eject
	// 4. Profit?
	AddSequential(new HomeArm());
	AddParallel(new MoveArm(80.0));
	if (DriverStation::GetInstance().GetGameSpecificMessage()[1] == 'R')
	{
		AddParallel(new DrivetrainFollowPath(ePathLeftToFarScale));
	}
	else if (DriverStation::GetInstance().GetGameSpecificMessage()[1] == 'L')
	{
		AddParallel(new DrivetrainFollowPath(ePathLeftToScale));
	}
	else
	{
		printf("Error occured determining Autonomous message. Bailing out...");
		return;
	}
	AddSequential(new Eject());
}


