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
	m_pAutoChooser 	= new SendableChooser<Command*>;
	m_pCompressor 	= new Compressor();
	m_pAutoIdle		= new AutoIdle();
	m_pAutoCenter	= new AutoCenter();
	m_pAutoLeft		= new AutoLeft();
	m_pAutoRight 	= new AutoRight();
}


CRobotMain::~CRobotMain()
{
	delete m_pAutoChooser;
	delete m_pAutoCommand;
	delete m_pCompressor;

	m_pAutoChooser = nullptr;
	m_pAutoCommand = nullptr;
	m_pCompressor = nullptr;

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
	SmartDashboard::PutData(m_pCompressor);

	// Instantiate the command used for the autonomous period
	m_pAutoChooser->AddDefault("Idle", m_pAutoIdle);
	m_pAutoChooser->AddObject("Center Auto", m_pAutoCenter);
	m_pAutoChooser->AddObject("Left Auto", m_pAutoLeft);
	m_pAutoChooser->AddObject("Right Auto", m_pAutoRight);
	SmartDashboard::PutData("Auto Mode", m_pAutoChooser);
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
	Scheduler::GetInstance()->RemoveAll();
	SmartDashboard::PutString("Teleop", "Autonomous Running");
	SmartDashboard::PutString("Autonomous", "Starting");
	m_pAutoCenter->Start();
}


/******************************************************************************
	AutonomousPeriodic:	Called based on TimedRobot's period any time
					the robot is in the Autonomous state.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::AutonomousPeriodic()
{
	// Call the ArmPosition Tick.
	m_ArmPosition.Tick();

	m_pCompressor->Start();

	// Run Autonomous.
	Scheduler::GetInstance()->Run();
}

/******************************************************************************
	TeleopInit:		Called once every time robot enters the Teleop state.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::TeleopInit()
{
	Scheduler::GetInstance()->RemoveAll();
	// Stop autonomous if it is currently running.
	if (m_pAutoCommand != nullptr) {
		m_pAutoCommand->Cancel();
	}
	SmartDashboard::PutString("Autonomous", "Teleop Running");
	SmartDashboard::PutString("Teleop",  "Starting");
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

	m_pCompressor->Start();

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
	m_pCompressor->Start();
}

/******************************************************************************
	DisabledPeriodic:	Called based on TimedRobot's period any time
					the robot is Disabled.

	Arguments:		None

	Returns:		Nothing
******************************************************************************/
void CRobotMain::DisabledInit()
{

}

void CRobotMain::DisabledPeriodic()
{

}
///////////////////////////////////////////////////////////////////////////////

START_ROBOT_CLASS(CRobotMain)
