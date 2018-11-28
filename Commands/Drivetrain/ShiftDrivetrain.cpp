
#include <WPILib.h>
#include "ShiftDrivetrain.h"
#include "../../RobotMain.h"
///////////////////////////////////////////////////////////////////////////////


ShiftDrivetrain::ShiftDrivetrain() : Command("ShiftDrivetrain")
{
	Requires(&CRobotMain::m_Drivetrain);
}

ShiftDrivetrain::~ShiftDrivetrain() {}

void ShiftDrivetrain::Initialize()
{
	CRobotMain::m_Drivetrain.Shift(); // @suppress("Ambiguous problem")
}
///////////////////////////////////////////////////////////////////////////////
