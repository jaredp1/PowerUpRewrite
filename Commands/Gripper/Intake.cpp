
#include <WPILib.h>
#include "Intake.h"
#include "StopIntake.h"
#include "../../RobotMain.h"
///////////////////////////////////////////////////////////////////////////////


Intake::Intake() : CommandGroup("Intake")
{
	Requires(&CRobotMain::m_Gripper);
	// Execute after Intake starts.
	AddSequential(new StopIntake());
}

/******************************************************************************
	Initialize:		Starts intake.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void Intake::Initialize()
{
	CRobotMain::m_Gripper.StartIntake();
}
///////////////////////////////////////////////////////////////////////////////
