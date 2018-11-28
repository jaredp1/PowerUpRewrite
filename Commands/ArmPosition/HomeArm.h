/******************************************************************************
	Description:	Defines the HomeArm command.

	Command:		HomeArm

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#ifndef HomeArm_h
#define HomeArm_h

#include <WPILib.h>
///////////////////////////////////////////////////////////////////////////////


class HomeArm : public Command {
public:
	HomeArm();
	~HomeArm();
	void Initialize();
	bool IsFinished();
};
///////////////////////////////////////////////////////////////////////////////
#endif
