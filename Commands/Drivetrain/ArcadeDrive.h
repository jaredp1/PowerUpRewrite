/******************************************************************************
	Description:	Defines the ArcadeDrive command.

	Command:		ArcadeDrive

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#ifndef ArcadeDrive_h
#define ArcadeDrive_h

#include <WPILib.h>
///////////////////////////////////////////////////////////////////////////////


class ArcadeDrive : public Command {
public:
	ArcadeDrive();
	~ArcadeDrive();
	void Execute();
	bool IsFinished()	{	return false;	};
	void End();

private:
	XboxController* m_pController;
};
///////////////////////////////////////////////////////////////////////////////
#endif
