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
	AutoIdle m_AutoIdle;
	AutoCenter m_AutoCenter;
	AutoLeft m_AutoLeft;
	AutoRight m_AutoRight;

	Compressor *m_pCompressor;
	void RobotInit() override;
	void RobotPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
};
///////////////////////////////////////////////////////////////////////////////
#endif
