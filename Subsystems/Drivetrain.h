/******************************************************************************
	Description:	Defines the Robot Drivetrain Subsystem.

	Subsystem:		Drivetrain

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#ifndef Drivetrain_h
#define Drivetrain_h
#pragma once

#include <WPILib.h>
#include <ctre/Phoenix.h>
// Note, if AHRS gives include errors, simply edit the include in AHRS.h. It's the onyl way, I think.
#include <AHRS.h>
#include "../IOMap.h"
#include "CANPosition.h"
///////////////////////////////////////////////////////////////////////////////


class Drivetrain : public Subsystem {
public:
	Drivetrain();
	~Drivetrain();
	void InitDefaultCommand();
	void Drive(double dSpeed, double dRotation);
	void ManualDrive(double dLeft, double dRight);
	void Shift();
	void Shift(bool bHighGear);
	int  GetLeftEncoderCount();
	int  GetRightEncoderCount();
	double GetAngle();

private:
	Solenoid	 *m_pDriveSolenoid;
	CCANPosition *m_pLeftDrive;
	WPI_TalonSRX *m_pLeftDrive2;
	WPI_TalonSRX *m_pLeftDrive3;

	CCANPosition *m_pRightDrive;
	WPI_TalonSRX *m_pRightDrive2;
	WPI_TalonSRX *m_pRightDrive3;

	DifferentialDrive* m_pRobotDrive;

	AHRS* m_pGyro;
};
///////////////////////////////////////////////////////////////////////////////
#endif
