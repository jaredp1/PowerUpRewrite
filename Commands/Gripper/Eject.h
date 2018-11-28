/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#ifndef FireIntoScale_h
#define FireIntoScale_h
#pragma once

#include <WPILib.h>
///////////////////////////////////////////////////////////////////////////////


class Eject : public Command
{
public:
	Eject();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
private:
	Timer m_Timer;
	double m_dStartTime;
	bool m_bIsNormalEject;
	bool m_bHasFired;
	bool m_bIsReturning;
	bool m_bHasReturned;
	// Configuration and timing for Ejecting into scale.
	const double m_dEjectHighThreshold = 84.0;
	const double m_dEjectLowThreshold  = 56.5;
	const double m_dEjectDelay 		= 0.015;
	const double m_dReturnDelay		= 0.250;
	const double m_dClawCloseDelay 	= 1.500;
	const double m_dNormalEjectDelay= 1.500;
};
///////////////////////////////////////////////////////////////////////////////
#endif
