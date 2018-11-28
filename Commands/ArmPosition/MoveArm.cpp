
#include <WPILib.h>
#include "MoveArm.h"
#include "../../RobotMain.h"
///////////////////////////////////////////////////////////////////////////////


MoveArm::MoveArm(double dSetpoint) : Command("MoveArm")
{
	Requires(&CRobotMain::m_ArmPosition);
	m_dSetpoint = dSetpoint;
}

MoveArm::~MoveArm() {}

void MoveArm::Initialize()
{
	CRobotMain::m_ArmPosition.SetSetpoint(m_dSetpoint);
}

bool MoveArm::IsFinished()
{
	return CRobotMain::m_ArmPosition.IsReady();
}

///////////////////////////////////////////////////////////////////////////////
