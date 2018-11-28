/******************************************************************************
	Description:	Defines the JogArm command.

	Command:		JogArm

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
******************************************************************************/
#ifndef JogArm_h
#define JogArm_h

#include <WPILib.h>
///////////////////////////////////////////////////////////////////////////////


class JogArm : public Command {
public:
	JogArm(bool bUpDirection);
	~JogArm();
	void Initialize();
	bool IsFinished();
private:
	bool m_bUpDirection;
};
///////////////////////////////////////////////////////////////////////////////
#endif
