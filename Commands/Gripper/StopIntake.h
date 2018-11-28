/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#ifndef StopIntake_h
#define StopIntake_h
#pragma once

#include <WPILib.h>
///////////////////////////////////////////////////////////////////////////////


class StopIntake : public Command
{
public:
	StopIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
private:
	double m_dStartTime;
	const double kIntakeTimeout = 2.0;
};
///////////////////////////////////////////////////////////////////////////////
#endif
