/****************************************************************************
	Description:	Defines the OI class.

	Classes:		OI

	Project:		2018 PowerUp Robot Codes.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
****************************************************************************/
#ifndef OI_h
#define OI_h
#pragma once

#include <WPILib.h>
enum XboxButtons {eButtonA = 1, eButtonB, eButtonX, eButtonY, eButtonLB, eButtonRB, eBack, eStart, eButtonLS, eButtonRS};
enum TriggerAxis {eLeftTrigger = 2, eRightTrigger};
/////////////////////////////////////////////////////////////////////////////


class OI
{
public:
    OI();
    ~OI();
	Joystick* GetController();

private:
	Joystick* m_pDriveController;
	JoystickButton* m_pShiftDrivetrain;
///	Joystick* m_pAuxController;
};
/////////////////////////////////////////////////////////////////////////////
#endif
