
#include <WPILib.h>
#include "StopIntake.h"
#include "../../RobotMain.h"
///////////////////////////////////////////////////////////////////////////////


StopIntake::StopIntake() : Command("StopIntake")
{
	Requires(&CRobotMain::m_Gripper);
	m_dStartTime = 0.0;
}

/******************************************************************************
	Initialize:		Resets timer.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void StopIntake::Initialize()
{
	m_dStartTime = 0.0;
}

/******************************************************************************
	Execute:		Checks to find whether the cube is in the claw.
					Starts a timer to continue running the intake motors.

	Arguments:		None

	Returns:		Nothing

	Also thanks Justin from 5254.
******************************************************************************/
void StopIntake::Execute()
{
	// Once sensor is tripped...
	if (CRobotMain::m_Gripper.m_pCubeSensor->Get() == true)
	{
		// Close the claw, start the timer.
		CRobotMain::m_Gripper.Close();
		if (m_dStartTime == 0.0)
		{
			m_dStartTime = CRobotMain::m_Gripper.m_pTimer->Get();
		}
	}
	else
	{
		// If the sensor is no longer tripped, reset timer.
		m_dStartTime = 0.0;
	}
}

/******************************************************************************
	IsFinished:		Continue running execute until Sensor is tripped and
					the timer has expired.

	Arguments:		None

	Returns:		bool
******************************************************************************/
bool StopIntake::IsFinished()
{
	// Once timer expires and sensor is still tripped, finish command.
	if (CRobotMain::m_Gripper.m_pCubeSensor->Get() == true || CRobotMain::m_Gripper.m_pTimer->Get() - m_dStartTime >= kIntakeTimeout)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************
	End:			Stops intake once finished.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void StopIntake::End()
{
	// Completely stop intake.
	CRobotMain::m_Gripper.Stop();
}
///////////////////////////////////////////////////////////////////////////////
