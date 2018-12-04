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
	m_pDriveController = new Joystick(0);
	m_pAuxController   = new Joystick(1);

	// Create buttons.
	m_pShiftDrivetrain = new JoystickButton(m_pDriveController, eButtonLS);
	m_pOpenIntake = new JoystickButton(m_pDriveController, eButtonRB);
	m_pMoveArmToScale = new JoystickButton(m_pDriveController, eButtonY);
	m_pChangeCamera = new JoystickButton(m_pDriveController, eButtonA);
	m_pFrontPickup = new JoystickButton(m_pAuxController, eButtonA);
	m_pBackPickup = new JoystickButton(m_pAuxController, eButtonB);
///	POV m_HomeArm(m_pAuxController, ePOVLeft);
///	POV m_ManualUp(m_pAuxController, ePOVUp);
///	POV m_ManualDown(m_pAuxController, ePOVDown);

	// Drive controller buttons.
	m_pShiftDrivetrain->WhenPressed(new ShiftDrivetrain());
	m_pOpenIntake->WhenPressed(new Intake());
	m_pMoveArmToScale->WhenPressed(new MoveArm(75.0));
	m_pChangeCamera->WhenPressed(new ChangeCamera());

	// Second controller buttons.
///	m_HomeArm.WhenActive(new HomeArm());
///	m_ManualUp.WhenActive(new JogArm(true));
///	m_ManualDown.WhenActive(new JogArm(false));
	m_pBackPickup->WhenPressed(new MoveArm(180.0));
	m_pFrontPickup->WhenPressed(new MoveArm(0.0));

}

OI::~OI()
{
	delete m_pDriveController;
///	delete m_pAuxController;

	m_pDriveController	= nullptr;
///	m_pAuxController	= nullptr;
}

Joystick* OI::GetController()
{
	return m_pDriveController;
}
/////////////////////////////////////////////////////////////////////////////
