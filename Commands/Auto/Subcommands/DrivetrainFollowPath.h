/*
 * DrivetrainFollowPath.h
 *
 *  Created on: Nov 26, 2018
 *      Author: Jared
 */

#ifndef DrivetrainFollowPath_h
#define DrivetrainFollowPath_h
#include <WPILib.h>
#include <pathfinder.h>

enum AutoPathIDs
{
	ePathIdle = 0,
	ePathCenterToLeft,
	ePathCenterToRight,
	ePathLeftToScale,
	ePathLeftToFarScale,
	ePathRightToScale,
	ePathRightToFarScale
};

class DrivetrainFollowPath : public Command
{
public:
	DrivetrainFollowPath(int nPathID = ePathIdle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();

private:
	void BuildPath();
	void Follow(double dSpeedLeft, double dSpeedRight);

	bool m_bHasFinished;
	int m_nPathID;
	int m_nLength;

	EncoderFollower m_LeftFollower;
	EncoderFollower m_RightFollower;

	EncoderConfig m_LeftConfig;
	EncoderConfig m_RightConfig;

	Segment m_LeftTrajectory;
	Segment m_RightTrajectory;

};



#endif
