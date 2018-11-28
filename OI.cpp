/******************************************************************************
	Description:	2018 PowerUp Robot controller interface.

	Classes:		OI

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#include <WPILib.h>
#include "OI.h"
///#include "Control/POV.h"
#include "Commands/Drivetrain/ShiftDrivetrain.h"
#include "Commands/Gripper/Intake.h"
#include "Commands/ArmPosition/MoveArm.h"
#include "Commands/ArmPosition/HomeArm.h"
#include "Commands/ArmPosition/JogArm.h"
#include "Commands/ChangeCamera.h"
///////////////////////////////////////////////////////////////////////////////

OI::OI()
{
	m_pDriveController = new XboxController(0);
	m_pAuxController   = new XboxController(1);

	// Create buttons.
	JoystickButton m_ShiftDrivetrain(m_pDriveController, eButtonLS);
	JoystickButton m_OpenIntake(m_pDriveController, eButtonRB);
	JoystickButton m_MoveArmToScale(m_pDriveController, eButtonY);
	JoystickButton m_ChangeCamera(m_pDriveController, eButtonA);
	JoystickButton m_FrontPickup(m_pAuxController, eButtonA);
	JoystickButton m_BackPickup(m_pAuxController, eButtonB);
///	POV m_HomeArm(m_pAuxController, ePOVLeft);
///	POV m_ManualUp(m_pAuxController, ePOVUp);
///	POV m_ManualDown(m_pAuxController, ePOVDown);

	// Drive controller buttons.
	m_ShiftDrivetrain.WhenPressed(new ShiftDrivetrain());
	m_OpenIntake.WhenPressed(new Intake());
	m_MoveArmToScale.WhenPressed(new MoveArm(75.0));
	m_ChangeCamera.WhenPressed(new ChangeCamera());

	// Second controller buttons.
///	m_HomeArm.WhenActive(new HomeArm());
///	m_ManualUp.WhenActive(new JogArm(true));
///	m_ManualDown.WhenActive(new JogArm(false));
	m_BackPickup.WhenPressed(new MoveArm(180.0));
	m_FrontPickup.WhenPressed(new MoveArm(0.0));

}

OI::~OI()
{
	delete m_pDriveController;
	delete m_pAuxController;

	m_pDriveController	= nullptr;
	m_pAuxController	= nullptr;
}

XboxController* OI::GetController()
{
	return m_pDriveController;
}
/////////////////////////////////////////////////////////////////////////////
