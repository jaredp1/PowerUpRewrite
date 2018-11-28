/******************************************************************************
	Description:	Implements the TankDrive command.

	Command:		TankDrive

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <Commands/Drivetrain/ArcadeDrive.h>
#include <WPILib.h>
#include "../../RobotMain.h"
///////////////////////////////////////////////////////////////////////////////


ArcadeDrive::ArcadeDrive() : Command("ArcadeDrive")
{
	Requires(&CRobotMain::m_Drivetrain);
	m_pController = CRobotMain::m_OI.GetController();
}

ArcadeDrive::~ArcadeDrive()
{
	delete m_pController;
	m_pController = nullptr;
}

// Called repeatedly when this Command is scheduled to run
void ArcadeDrive::Execute()
{
	CRobotMain::m_Drivetrain.Drive(-m_pController->GetY(GenericHID::kLeftHand), -m_pController->GetX(GenericHID::kRightHand));
}

// Called once after isFinished returns true
void ArcadeDrive::End()
{
	CRobotMain::m_Drivetrain.Drive(0, 0);
}
///////////////////////////////////////////////////////////////////////////////
