/******************************************************************************
	Description:	Defines the ChangeCamera command.

	Command:		ChangeCamera

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#ifndef ChangeCamera_h
#define ChangeCamera_h
#pragma once

#include <WPILib.h>
///////////////////////////////////////////////////////////////////////////////


class ChangeCamera : public Command
{
public:
	ChangeCamera();
	~ChangeCamera();
	void Initialize();
	bool IsFinished()	{	return true;	};
	void End();
};

///////////////////////////////////////////////////////////////////////////////
#endif
