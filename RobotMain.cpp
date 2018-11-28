/******************************************************************************
	Description:	2018 PowerUp Robot Control Software.

	Classes:		CRobotMain

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <WPILib.h>
#include "RobotMain.h"

Drivetrain CRobotMain::m_Drivetrain;
Gripper CRobotMain::m_Gripper;
ArmPosition CRobotMain::m_ArmPosition;
Camera CRobotMain::m_Camera;
OI CRobotMain::m_OI;
///////////////////////////////////////////////////////////////////////////////


/******************************************************************************
	Description:	CRobotMain Constructor.

	Arguments:		None

	Derived From:	TimedRobot
******************************************************************************/
CRobotMain::CRobotMain() : TimedRobot()
{

}


CRobotMain::~CRobotMain()
{
	delete m_pAutoCommand;
	m_pAutoCommand = nullptr;
}
/******************************************************************************
	RobotInit:		Robot-wide initialization code which is called only once upon
					a power on reset.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::RobotInit()
{
	SmartDashboard::PutData(&m_Drivetrain);
	SmartDashboard::PutData(&m_Gripper);
	SmartDashboard::PutData(&m_ArmPosition);
	// Just to monitor the current draw of the compressor, I guess.
	SmartDashboard::PutData(&m_Compressor);

	// Instantiate the command used for the autonomous period
	m_pAutoChooser.AddDefault("Idle", &m_AutoIdle);
	m_pAutoChooser.AddObject("Center Auto", &m_AutoCenter);
	m_pAutoChooser.AddObject("Left Auto", &m_AutoLeft);
	m_pAutoChooser.AddObject("Right Auto", &m_AutoRight);
	SmartDashboard::PutData("Auto Mode", &m_pAutoChooser);
}

/******************************************************************************
	RobotPeriodic:	Called based on TimedRobot's period while the robot is on.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::RobotPeriodic()
{
	m_Camera.Tick();
	SmartDashboard::UpdateValues();
}

/******************************************************************************
	AutonomousInit:	Called once every time robot enters the autonomous
					state.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::AutonomousInit()
{
	m_pAutoCommand = m_pAutoChooser.GetSelected();
	printf("Starting Autonomous");
}


/******************************************************************************
	AutonomousPeriodic:	Called based on TimedRobot's period any time
					the robot is in the Autonomous state.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::AutonomousPeriodic()
{
	// Run autonomous.
	Scheduler::GetInstance()->Run();
}

/******************************************************************************
	TeleopInit:		Called once every time robot enters the Teleop state.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::TeleopInit()
{
	// Stop autonomous if it is currently running.
	if (m_pAutoCommand != nullptr) {
		m_pAutoCommand->Cancel();
	}
	printf("Starting Teleop");
}


/******************************************************************************
	TeleopPeriodic:	Called based on TimedRobot's period any time the robot
					is in the Teleop state.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::TeleopPeriodic()
{
	// Call the ArmPosition Tick.
	m_ArmPosition.Tick();

	m_Compressor.Start();

	// Run Teleop.
	Scheduler::GetInstance()->Run();
}

/******************************************************************************
	TestPeriodic:	Called based on TimedRobot's period any time the robot
					is in the Test state.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::TestPeriodic()
{
	m_Compressor.Start();
}

/******************************************************************************
	DisabledPeriodic:	Called based on TimedRobot's period any time
					the robot is Disabled.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::DisabledInit() {}
void CRobotMain::DisabledPeriodic()
{

}
///////////////////////////////////////////////////////////////////////////////

START_ROBOT_CLASS(CRobotMain)
