/******************************************************************************
	Description:	Implements the ChangeCamera command.

	Command:		ChangeCamera

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <WPILib.h>
#include "ChangeCamera.h"
#include "../RobotMain.h"
///////////////////////////////////////////////////////////////////////////////


ChangeCamera::ChangeCamera() : Command("ChangeCamera")
{
	Requires(&CRobotMain::m_Camera);
}

ChangeCamera::~ChangeCamera() {}

void ChangeCamera::Initialize()
{
	CRobotMain::m_Camera.SwitchCamera();
}

// Called once after isFinished returns true
void ChangeCamera::End()
{

}
///////////////////////////////////////////////////////////////////////////////
