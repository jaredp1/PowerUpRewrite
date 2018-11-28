/****************************************************************************
	Description:	Defines the Camera subsystem.

	Subsystem:		Camera

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
****************************************************************************/
#ifndef Camera_h
#define Camera_h

#include <WPILib.h>
#include <CameraServer.h>
#include "opencv2/imgproc/imgproc.hpp"

// Camera Constants.
const int nImageWidth			=  320;	/// 160;	// Image width.
const int nImageHeight			=  240; /// 120;	// Image height.
const int nCameraFPS			=   20;	// Camera FPS.
/////////////////////////////////////////////////////////////////////////////


/****************************************************************************
	Description:	Camera Constructor.

	Arguments:		None

	Derived From:	Nothing
****************************************************************************/
class Camera : public Subsystem
{
public:
	Camera();
	void	Init();
	void 	Tick();
	void	SwitchCamera();

private:
	// Object pointers.
	cs::UsbCamera			m_FrontCamera;
	cs::UsbCamera			m_RearCamera;
	cs::CvSink				m_CameraSink;
	cs::CvSource			m_CameraSource;
	cv::Mat					m_Image;
	// Toggle the camera variable.
	bool m_bIsFrontCamera;
};
/////////////////////////////////////////////////////////////////////////////
#endif
