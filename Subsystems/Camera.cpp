/****************************************************************************
	Description:	Implements the Camera subsystem.

	Subsystem:		Camera

	Project:		2018 PowerUp Robot Code.

	Copyright 2018 First Team 3284 - Camdenton LASER Robotics.
****************************************************************************/
#include <WPILib.h>
#include <CameraServer.h>
#include "Subsystems/Camera.h"
/////////////////////////////////////////////////////////////////////////////


/****************************************************************************
	Description:	Camera Constructor.

	Arguments:		None

	Derived From:	Nothing
****************************************************************************/
Camera::Camera() : Subsystem("Camera")
{
	m_FrontCamera 		= cs::UsbCamera("Front Camera", 0);
	m_RearCamera  		= cs::UsbCamera("Rear Camera", 1);
	m_CameraSink		= CameraServer::GetInstance()->GetVideo(m_RearCamera);
	m_CameraSource		= CameraServer::GetInstance()->PutVideo("Current View", nImageWidth, nImageHeight);
	m_Image				= cv::Mat();

	// Set up the front camera.
	m_FrontCamera.SetResolution(nImageWidth, nImageHeight);
	m_FrontCamera.SetFPS(nCameraFPS);
	m_FrontCamera.SetExposureAuto();

	// Set up the rear camera.
	m_RearCamera.SetResolution(nImageWidth, nImageHeight);
	m_RearCamera.SetFPS(nCameraFPS);
	m_RearCamera.SetExposureAuto();

	m_bIsFrontCamera = false;
}

void Camera::Tick()
{
		// Get latest frame.
		m_CameraSink.GrabFrame(m_Image);
		// Send the current frame to the SmartDashboard.
		m_CameraSource.PutFrame(m_Image);
}

void Camera::SwitchCamera()
{
	// Toggle the camera variable.
	m_bIsFrontCamera = !m_bIsFrontCamera;

	if (m_bIsFrontCamera)
	{
		// Set the new source for the CameraSink as the front camera.
		m_CameraSink.SetSource(m_FrontCamera);
	}
	else
	{
		// Set the new source for the CameraSink as the rear camera.
		m_CameraSink.SetSource(m_RearCamera);
	}
}
