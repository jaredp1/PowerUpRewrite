/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#ifndef MoveArm_h
#define MoveArm_h
#pragma once

#include <WPILib.h>
///////////////////////////////////////////////////////////////////////////////


class MoveArm : public Command {
public:
	MoveArm(double dSetpoint);
	~MoveArm();
	void Initialize();
	bool IsFinished();
private:
	double m_dSetpoint;
};
///////////////////////////////////////////////////////////////////////////////
#endif
