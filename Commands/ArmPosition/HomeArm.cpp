/******************************************************************************
	Description:	Implements the HomeArm command.

	Command:		HomeArm

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <WPILib.h>
#include "HomeArm.h"
#include "../../RobotMain.h"
///////////////////////////////////////////////////////////////////////////////


HomeArm::HomeArm() : Command("HomeArm")
{
	Requires(&CRobotMain::m_ArmPosition);
}

HomeArm::~HomeArm() {}

void HomeArm::Initialize()
{
	CRobotMain::m_ArmPosition.ArmHome();
}

bool HomeArm::IsFinished()
{
	return CRobotMain::m_ArmPosition.IsReady();
}
///////////////////////////////////////////////////////////////////////////////
