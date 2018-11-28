/******************************************************************************
	Description:	Defines the Robot Gripper Subsystem.

	Subsystem:		Gripper

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#ifndef Gripper_h
#define Gripper_h
#pragma once

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "../IOMap.h"
///////////////////////////////////////////////////////////////////////////////


class Gripper : public Subsystem
{
public:
	Gripper();
	~Gripper();
	void OpenIntake();
	void StartIntake();
	void Close();
	void Stop();
	void Eject(bool bActivated);
	void Vacuum(bool bActivated);
	void NormalEject();
	DigitalInput *m_pCubeSensor;
	Timer 		 *m_pTimer;

private:
	Solenoid	 *m_pLeftSolenoid;
	Solenoid	 *m_pRightSolenoid;
	Solenoid	 *m_pEjectSolenoid;
	Solenoid	 *m_pPlungerVacuum;
	WPI_TalonSRX *m_pIntakeMotors;
	// Right motor will follow Left motor.
	WPI_TalonSRX *m_pRightIntake;
	const double kIntakeTimeout = 3.0;
};
///////////////////////////////////////////////////////////////////////////////
#endif
