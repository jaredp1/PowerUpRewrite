/******************************************************************************
	Description:	Implements the AutoCenter command.

	Command:		AutoCenter

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <WPILib.h>
#include <RobotMain.h>
#include "AutoRight.h"
#include <Commands/ArmPosition/HomeArm.h>
#include <Commands/ArmPosition/MoveArm.h>
#include <Commands/Gripper/Eject.h>
#include <Commands/Auto/Subcommands/DrivetrainFollowPath.h>

AutoRight::AutoRight()
{
	// 1. Home Arm
	// 2. Decide where to go, drive to the Scale and raise arm to 80 degrees
	// 3. Eject
	// 4. Profit?
	AddSequential(new HomeArm());
	AddParallel(new MoveArm(80.0));
	if (DriverStation::GetInstance().GetGameSpecificMessage()[1] == 'R')
	{
		AddParallel(new DrivetrainFollowPath(ePathRightToScale));
	}
	else if (DriverStation::GetInstance().GetGameSpecificMessage()[1] == 'L')
	{
		AddParallel(new DrivetrainFollowPath(ePathRightToFarScale));
	}
	else
	{
		printf("Error occured determining Autonomous message. Bailing out...");
		return;
	}
	AddSequential(new Eject());
}


