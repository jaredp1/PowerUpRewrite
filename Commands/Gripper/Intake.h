/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#ifndef Intake_h
#define Intake_h
#pragma once

#include <WPILib.h>
///////////////////////////////////////////////////////////////////////////////


class Intake : public CommandGroup
{
public:
	Intake();
	void Initialize();
	bool IsFinished()		{	return true;	};
};
///////////////////////////////////////////////////////////////////////////////
#endif
