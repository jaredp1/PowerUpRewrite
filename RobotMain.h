#ifndef CRobotMain_h
#define CRobotMain_h
#pragma once

#include <WPILib.h>
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Gripper.h"
#include "Subsystems/ArmPosition.h"
#include "Subsystems/Camera.h"
#include "Commands/Auto/AutoIdle.h"
#include "Commands/Auto/AutoCenter.h"
#include "Commands/Auto/AutoLeft.h"
#include "Commands/Auto/AutoRight.h"
#include "OI.h"
///////////////////////////////////////////////////////////////////////////////


class CRobotMain : public TimedRobot
{
public:
	CRobotMain();
	~CRobotMain();
	static Drivetrain m_Drivetrain;
	static Gripper m_Gripper;
	static ArmPosition m_ArmPosition;
	static Camera m_Camera;
	static OI m_OI;

private:
	// Autonomous Objects.
	Command* m_pAutoCommand = nullptr;
	SendableChooser<Command*> *m_pAutoChooser;

	// Autonomous Commands.
	AutoIdle 	*m_pAutoIdle;
	AutoCenter 	*m_pAutoCenter;
	AutoLeft 	*m_pAutoLeft;
	AutoRight 	*m_pAutoRight;

	Compressor *m_pCompressor;
	void RobotInit();
	void RobotPeriodic();
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void TestPeriodic();
	void DisabledInit();
	void DisabledPeriodic();
};
///////////////////////////////////////////////////////////////////////////////
#endif
