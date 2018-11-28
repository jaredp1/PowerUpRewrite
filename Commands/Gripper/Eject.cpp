
#include "Eject.h"
#include <WPILib.h>
#include "../../RobotMain.h"
///////////////////////////////////////////////////////////////////////////////


Eject::Eject() : Command("Eject")
{
	Requires(&CRobotMain::m_Gripper);
	Requires(&CRobotMain::m_ArmPosition);
	m_dStartTime 	= 0.0;
	m_bIsNormalEject = false;
	m_bHasFired 	= false;
	m_bIsReturning 	= false;
	m_bHasReturned 	= false;
}

/******************************************************************************
	Initialize:		Open Intake, start timer.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void Eject::Initialize()
{
	// Check the threshold.
	if ((CRobotMain::m_ArmPosition.GetSetpoint() > m_dEjectLowThreshold) && (CRobotMain::m_ArmPosition.GetSetpoint() < m_dEjectHighThreshold))
	{
		// Start timer, open intake.
		m_bIsNormalEject = false;
		m_dStartTime = m_Timer.Get();
		CRobotMain::m_Gripper.OpenIntake();
	}
	else
	{
		// Not in threshold, normal Eject.
		m_bIsNormalEject = true;
		m_dStartTime = m_Timer.Get();
		CRobotMain::m_Gripper.NormalEject();
	}
}

/******************************************************************************
	Execute:

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void Eject::Execute()
{
	if (!m_bIsNormalEject)
	{
		// If hasn't fired and Eject time elapsed, fire
		if (!m_bHasFired && (m_Timer.Get() - m_dStartTime >= m_dEjectDelay))
		{
			CRobotMain::m_Gripper.Eject(true);
			m_bHasFired = true;
			m_dStartTime = m_Timer.Get();
		}
		// If has fired and Return time elapsed, return plunger, activate vacuum.
		if (m_bHasFired && (m_Timer.Get() - m_dStartTime >= m_dReturnDelay))
		{
			CRobotMain::m_Gripper.Eject(false);
			CRobotMain::m_Gripper.Vacuum(true);
			m_dStartTime = m_Timer.Get();
			m_bIsReturning = true;
		}
		// If has returned and Close time elapsed, close claw, stop vacuum.
		if (m_bHasFired && (m_Timer.Get() - m_dStartTime >= m_dClawCloseDelay))
		{
			CRobotMain::m_Gripper.Close();
			CRobotMain::m_Gripper.Vacuum(false);
			m_bHasReturned = true;
		}
	}
	else if (m_bIsNormalEject && m_dStartTime >= m_dNormalEjectDelay)
	{
			// Finished ejecting.
			m_bHasReturned = true;
	}
}

/******************************************************************************
	IsFinished:

	Arguments:		None

	Returns:		bool
******************************************************************************/
bool Eject::IsFinished()
{
	return m_bHasReturned;
}

/******************************************************************************
	End:

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void Eject::End()
{
	// Completely stop and reset intake.
	CRobotMain::m_Gripper.Stop();
}
///////////////////////////////////////////////////////////////////////////////
