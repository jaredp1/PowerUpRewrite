/******************************************************************************
	Description:	Defines the Robot Arm Subsystem.

	Subsystem:		ArmPosition

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#ifndef ArmPosition_h
#define ArmPosition_h
#pragma once

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "../IOMap.h"
#include "CANPosition.h"
///////////////////////////////////////////////////////////////////////////////


class ArmPosition : public Subsystem {
public:
	ArmPosition();
	~ArmPosition();
	void Tick();
	void InitDefaultCommand();
	void SetSetpoint(double dSetpoint);
	double GetSetpoint();
	double GetActual();
	bool IsReady();
	void ArmHome();
	void ArmJog(bool bUpDirection);

private:
	Solenoid	 *m_pBrakeSolenoid;
	CCANPosition *m_pArmMotor;
	double m_dArmSetpoint;

	// Arm Position Constants.
	const double dArmPositionEncoderRevsPerDegree	= ((1.000 / 16) * (72 / 1.000) * (1.000 / 360));	// ((1 enc rev / 16 teeth)(72 teeth / 1 arm rev)(1 arm rev / 360°))
	const double dArmPositionHomingSpeedReverse		=	-0.500;		// Homing speed reverse (towards home switch).
	const double dArmPositionHomingSpeedForward		=	 0.150;		// Homing speed forward (off of home switch)
	const double dArmPositionMaxHomingTimeout		=	 6.000;		// Maximum time to home.
	const double dArmPositionMaxFindingTimeout		=	 6.000;		// Maximum time to find position.
	const double dArmPositionMaxSpeed				=    1.000;		// Maximum arm position output speed.
	const double dArmPositionMinSpeed				=   -1.000;		// Minimum arm position output speed.
	const double dArmPositionMaxDistance			=  180.000;		// Maximum arm position distance (180°).
	const double dArmPositionMinDistance			= 	-1.000;		// Minimum arm position distance (0°).
	const double dArmPositionTolerance				=    2.000;		// Arm Position tolerance in degrees.
	const double dArmPositionProportional			=	 1.800;		// Arm Position Proportional. (2.000)   /// 2.250
	const double dArmPositionIntegral				=	 0.000;		// Arm Position Integral.
	const double dArmPositionDerivative				=	 0.000;		// Arm Position Derivative.
	const double dArmPositionAccumIZone				=	15.000;		// Arm Position Accumulated Integral Zone.
	const double dArmPositionOpenLoopRampRate		=	 0.500;		// Open Loop Ramp Rate.
	const double dArmPositionClosedLoopRampRate		=	 0.500;		// Closed Loop Ramp Rate.
};
///////////////////////////////////////////////////////////////////////////////
#endif
