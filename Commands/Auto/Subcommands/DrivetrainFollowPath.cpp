
#include "DrivetrainFollowPath.h"
#include <Commands/Drivetrain/ArcadeDrive.h>
#include <pathfinder.h>
#include <WPILib.h>
#include <RobotMain.h>
///////////////////////////////////////////////////////////////////////////////

// Things to note when generating paths, the clock for the RoboRIO runs
// at 20ms. This shouldn't change.

DrivetrainFollowPath::DrivetrainFollowPath(int nPathID) : Command("DrivetrainFollowPath")
{
	Requires(&CRobotMain::m_Drivetrain);
	m_bHasFinished = false;
	m_nPathID = nPathID;

	m_nLength = 0;

	SmartDashboard::PutString("Debug", "Constructing Path.");
}

/******************************************************************************
	Initialize:

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void DrivetrainFollowPath::Initialize()
{
	if (m_nPathID == ePathIdle)
	{
		// Just idling, exit.
		m_bHasFinished = true;
		SmartDashboard::PutString("Debug", "Idle path, this shouldn't be selected?");
		return;
	}

	// Allocate memory.
	FILE *fp;
	fp = nullptr;

	if (m_nPathID == ePathCenterToLeft)
	{
		fp = fopen("~/CenterToLeft-Left.csv", "r");
		m_nLength = pathfinder_deserialize_csv(fp, &m_LeftTrajectory);
		fclose(fp);
		fp = fopen("~/CenterToLeft-Right.csv", "r");
		pathfinder_deserialize_csv(fp, &m_RightTrajectory);
		fclose(fp);
		printf("CenterToLeft Selected.");
	}

	if (m_nPathID == ePathCenterToRight)
	{
		fp = fopen("~/CenterToRight-Left.csv", "r");
		m_nLength = pathfinder_deserialize_csv(fp, &m_LeftTrajectory);
		fclose(fp);
		fp = fopen("~/CenterToRight-Right.csv", "r");
		pathfinder_deserialize_csv(fp, &m_RightTrajectory);
		fclose(fp);
		printf("CenterToRight Selected.");

	}

	if (m_nPathID == ePathLeftToScale)
	{
		fp = fopen("~/LeftToScale-Left.csv", "r");
		m_nLength = pathfinder_deserialize_csv(fp, &m_LeftTrajectory);
		fclose(fp);
		fp = fopen("~/LeftToScale-Right.csv", "r");
		pathfinder_deserialize_csv(fp, &m_RightTrajectory);
		fclose(fp);
	}

	if (m_nPathID == ePathLeftToFarScale)
	{
		fp = fopen("~/LeftToFarScale-Left.csv", "r");
		m_nLength = pathfinder_deserialize_csv(fp, &m_LeftTrajectory);
		fclose(fp);
		fp = fopen("~/LeftToFarScale-Right.csv", "r");
		pathfinder_deserialize_csv(fp, &m_RightTrajectory);
		fclose(fp);
    }

	if (m_nPathID == ePathRightToScale)
	{
		fp = fopen("~/RightToScale-Left.csv", "r");
		m_nLength = pathfinder_deserialize_csv(fp, &m_LeftTrajectory);
		fclose(fp);
		fp = fopen("~/RightToScale-Right.csv", "r");
		pathfinder_deserialize_csv(fp, &m_RightTrajectory);
		fclose(fp);
	}

	if (m_nPathID == ePathRightToFarScale)
	{
		fp = fopen("~/RightToFarScale-Left.csv", "r");
		m_nLength = pathfinder_deserialize_csv(fp, &m_LeftTrajectory);
		fclose(fp);
		fp = fopen("~/RightToFarScale-Right.csv", "r");
		pathfinder_deserialize_csv(fp, &m_RightTrajectory);
		fclose(fp);
	}

	m_LeftFollower.last_error = 0;
	m_LeftFollower.segment = 0;
	m_LeftFollower.finished = 0;

	m_RightFollower.last_error = 0;
	m_RightFollower.segment = 0;
	m_RightFollower.finished = 0;

	m_LeftConfig =
	{
		CRobotMain::m_Drivetrain.GetLeftEncoderCount(), 	// Encoder starting point.
		4096, 								// Ticks per rev
		6.08, 								// Wheel Circumference
	    1.0, 0.0, 0.0, 1.0 / 15.5, 2.986   	// P, I, D, V, A
	};

	m_RightConfig =
	{
		CRobotMain::m_Drivetrain.GetRightEncoderCount(),	// Encoder starting point.
		4096, 								// Ticks per rev
		6.08, 								// Wheel Circumference
	    1.0, 0.0, 0.0, 1.0 / 15.5, 2.986   	// P, I, D, V, A
	};

	SmartDashboard::PutString("Debug", "Configured correctly I think");
	// Free the file, despite it (not actually) causing uninitialized warnings.
	free(fp);
}

/******************************************************************************
	Execute:

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void DrivetrainFollowPath::Execute()
{
	static int nCounter = 0;
	nCounter++;
	SmartDashboard::PutString("Debug", "Looping, counter boye is at " + nCounter);
	double dLeft = pathfinder_follow_encoder(m_LeftConfig, &m_LeftFollower, &m_LeftTrajectory, m_nLength, CRobotMain::m_Drivetrain.GetRightEncoderCount());
	double dRight = pathfinder_follow_encoder(m_RightConfig, &m_RightFollower, &m_RightTrajectory, m_nLength, CRobotMain::m_Drivetrain.GetRightEncoderCount());

	double dGyroHeading = CRobotMain::m_Drivetrain.GetAngle();
	double dDesiredHeading = r2d(m_LeftFollower.heading);

	double dError = dDesiredHeading - dGyroHeading;
	if (dError > 180)
	{
		dError = 180;
	}
	if (dError < -180)
	{
		dError = -180;
	}

	double dTurn = 0.8 * (-1.0/80.0) * dError;

	SmartDashboard::PutNumber("Left MP", dLeft);
	SmartDashboard::PutNumber("Right MP", dRight);

	CRobotMain::m_Drivetrain.ManualDrive(dLeft + dTurn, dRight - dTurn);

	if (nCounter >= m_nLength)
	{
		// Reached end of path. Exit.
		m_bHasFinished = true;
	}
}

/******************************************************************************
	IsFinished:

	Arguments:		None

	Returns:		bool
******************************************************************************/
bool DrivetrainFollowPath::IsFinished()
{
	return m_bHasFinished;
}

/******************************************************************************
	End:

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void DrivetrainFollowPath::End()
{

}
///////////////////////////////////////////////////////////////////////////////



