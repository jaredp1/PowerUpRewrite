/******************************************************************************
	Description:	Implements the JogArm command.

	Command:		JogArm

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <WPILib.h>
#include "JogArm.h"
#include "../../RobotMain.h"
///////////////////////////////////////////////////////////////////////////////


JogArm::JogArm(bool bUpDirection) : Command("JogArm")
{
	Requires(&CRobotMain::m_ArmPosition);
	m_bUpDirection = bUpDirection;
}

JogArm::~JogArm() {}

void JogArm::Initialize()
{
	CRobotMain::m_ArmPosition.ArmJog(m_bUpDirection);
}

bool JogArm::IsFinished()
{
	return CRobotMain::m_ArmPosition.IsReady();
}
///////////////////////////////////////////////////////////////////////////////
